//[mto.import ./model]
//[mto.import ../expr/dag]
//[mto.import no_stl/variant/stack_variant.impl:INSTANCIATE_STACK_VARIANT#]

//[mto-gen.begin]
#include "./model.h"
#include "./../expr/dag.h"
#include "no_stl/variant/stack_variant.impl.h"
namespace mto::math::ml::model::model {
namespace model = mto::math::ml::model::model;
namespace dag = mto::math::ml::expr::dag;
}
#include "cpp_tools/defines.h"
//[mto-gen.end]
//[mto]
namespace mto::math::ml::model::model {//[mto.module-begin]

using dag::dag_t;

namespace {

void perform_descent_step(
    vector_t<dag::var_value_t> &params,
    dag::dag_t const &dag,
    on_iteration_t const &on_iteration,
    real_t y, int32_t epoch, float rate) {

  let values = dag::eval(dag, params);
  let grads = dag::eval_bw_grad(dag, values, {{y.id, 1}});
  let loss = values[y.id];

  let retrieve_parameters_weights = [&]() -> vector_t<float> {
    vector_t<float> weights;
    for (let &p : params) {
      weights.push_back(p.value);
    }
    return weights;
  };

  on_iteration({epoch, rate, loss, retrieve_parameters_weights});
  for (auto &p : params) {
    p.value -= grads[p.id] * rate;
  }
}

void _fit(vector_t<sample_t> const &samples,
          bound_model_t const &bound_model,
          loss_func_t const &loss,
          vector_t<dag::var_value_t> &params,
          dag::dag_t const &dag,
          expr::ops_t const &ops,
          basic_scheduler_t const &scheduler,
          on_iteration_t const &on_iteration) {
  let y = loss(samples, bound_model, ops);
  for (auto e = 0; e < scheduler.max_epoch; ++e) {
    perform_descent_step(params, dag, on_iteration, y, e,
                         scheduler.learning_rate);
  }
}

void _fit(vector_t<sample_t> const &samples,
          bound_model_t const &bound_model,
          loss_func_t const &loss,
          vector_t<dag::var_value_t> &params,
          dag::dag_t const &dag,
          expr::ops_t const &ops,
          warmup_decay_scheduler_t const &scheduler,
          on_iteration_t const &on_iteration) {
  let y = loss(samples, bound_model, ops);

  auto rate = scheduler.init_learning_rate;
  auto e = 0;
  for (auto ew = 0; ew < scheduler.num_warmup_iterations; ++ew) {
    perform_descent_step(params, dag, on_iteration, y, e++, rate);
    rate *= scheduler.warmup_rate;
  }
  for (auto ed = 0; ed < scheduler.num_descent_iterations; ++ed) {
    perform_descent_step(params, dag, on_iteration, y, e++, rate);
    rate *= scheduler.decay_rate;
  }
}

void fit(vector_t<sample_t> const &samples,
         bound_model_t const &bound_model,
         loss_func_t const &loss,
         vector_t<dag::var_value_t> &params,
         dag::dag_t const &dag,
         expr::ops_t const &ops,
         any_scheduler_t const &scheduler,
         on_iteration_t const &on_iteration) {
  return scheduler.visit([&](let &s) {
    return _fit(samples, bound_model, loss, params, dag, ops, s, on_iteration);
  });
}

}

bound_model_t model_t::bind(vector_t<real_t> const &params) const {
  REQUIRES(params.size() == num_parameters);
  let bound_model = [=, this](cspan_t<real_t> x, expr::ops_t ops) -> vector_t<real_t> {
    return compute(params, x, ops);
  };
  return bound_model;
}

/**
 * Simple models
 */

model_t create_linear_model_1d() {
  let compute = [](cspan_t<real_t> params,
                   cspan_t<real_t> X,
                   expr::ops_t ops) -> vector_t<real_t> {
    REQUIRES(X.size() == 1);
    return {params[0] * X[0] + params[1]};
  };
  let get_init_parameters_values = []() -> vector_t<float> {
    return {0, 0};
  };

  return model_t{compute, get_init_parameters_values, 2, 1};
}

/**
 * model fitting
 */

vector_t<float>
fit_model(model_t const &model,
          loss_func_t const &loss,
          vector_t<float> const &init_params,
          vector_t<fsample_t> const &samples,
          any_scheduler_t const &scheduler,
          on_iteration_t const &on_iteration) {
  REQUIRES(model.num_parameters == init_params.size());

  auto dag = dag_t{};
  auto ops = expr::ops_t{&dag};

  vector_t<dag::var_value_t> params_values;
  vector_t<real_t> params;

  for (let &init_param : init_params) {
    let p = ops.real();
    params.push_back(p);
    params_values.push_back({p.id, init_param});
  }
  let bound_model = model.bind(params);

  vector_t<sample_t> expr_samples;
  for (let &sample : samples) {
    vector_t<real_t> X;
    for (let &x : sample.X) {
      X.push_back(ops(x));
    }
    vector_t<real_t> Y;
    for (let &y : sample.Y) {
      Y.push_back(ops(y));
    }
    expr_samples.push_back({X, Y});
  }

  fit(expr_samples, bound_model, loss, params_values, dag, ops,
      scheduler, on_iteration);
  vector_t<float> _params_values;
  for (let &value : params_values) {
    _params_values.push_back(value.value);
  }
  return _params_values;
}

predictor_t
build_predictor(model_t const &model,
                vector_t<float> const &params_values) {
  REQUIRES(params_values.size() == model.num_parameters);
  auto eval_dag = dag_t{};
  auto ops = expr::ops_t{&eval_dag};

  vector_t<real_t> params;
  for (let &param_value : params_values) {
    params.push_back(ops(param_value));
  }

  auto X = vector_t<real_t>{};
  for (auto i_x = 0u; i_x < model.num_inputs; ++i_x) {
    X.push_back(ops.real());
  }

  auto Y = model.compute(params, X, ops);

  let num_inputs = model.num_inputs;
  return [X, num_inputs, eval_dag, Y](vector_t<float> const &X_values) -> vector_t<float> {
    REQUIRES(X.size() == num_inputs);
    REQUIRES(X.size() == X.size());
    vector_t<dag::var_value_t> X_vars;
    for (auto i_x = 0u; i_x < num_inputs; ++i_x) {
      X_vars.push_back({X[i_x].id, X_values[i_x]});
    }
    let values = dag::eval(eval_dag, X_vars);
    vector_t<float> res;
    for (let &y : Y) {
      res.push_back(values[y.id]);
    }
    return res;
  };
}

}//[mto.module-end]

namespace _ns =
mto::math::ml::model::model//[mto.module-namespace]
    ;

INSTANCIATE_STACK_VARIANT(
    _ns::basic_scheduler_t,
    _ns::warmup_decay_scheduler_t);
