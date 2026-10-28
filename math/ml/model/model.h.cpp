//[mto.import ./model]
//[mto.import ../expr/dag]
//[mto.import no_stl/variant/stack_variant.impl:INSTANCIATE_STACK_VARIANT#]
//[mto.import ../expr/compiler/jit_compiler]
#include <stdexcept>

//[mto-gen.begin]
#include "./model.h"
#include "./../expr/dag.h"
#include "no_stl/variant/stack_variant.impl.h"
#include "./../expr/compiler/jit_compiler.h"
namespace mto::math::ml::model::model {
namespace model = mto::math::ml::model::model;
namespace dag = mto::math::ml::expr::dag;
namespace jit_compiler = mto::math::ml::expr::compiler::jit_compiler;
}
#include "cpp_tools/defines.h"
//[mto-gen.end]
//[mto]
namespace mto::math::ml::model::model {//[mto.module-begin]

using dag::dag_t;

namespace {

struct step_eval_res_t {
  vector_t<float, dag::node_id_t> grads;
  float loss;
};

step_eval_res_t
eval_model(vector_t<dag::var_value_t> &params,
           dag::dag_t const &dag,
           jit_compiler::evaluator_t *p_compiled_eval,
           real_t y) {
  if (!p_compiled_eval) {
    let values = dag::eval(dag, params);
    let grads = dag::eval_bw_grad(dag, values, {{y.id, 1}});
    let loss = values[y.id];
    return {grads, loss};
  } else {
    auto values = vector_t<float, dag::node_id_t>(dag.ops.size(), 0);
    for (let &p : params) {
      values[p.id] = p.value;
    }
    let res = p_compiled_eval->eval(values.data());
    CHECK(res);

    auto grads = vector_t<float, dag::node_id_t>(dag.ops.size(), 0);
    grads[y.id] = 1;
    let res2 = p_compiled_eval->eval_bw_grad(grads.data(), values.data());
    CHECK(res2);

    return {grads, values[y.id]};
  }
}

void perform_descent_step(
    vector_t<dag::var_value_t> &params,
    dag::dag_t const &dag,
    jit_compiler::evaluator_t *p_eval,
    on_iteration_t const &on_iteration,
    real_t y, int32_t epoch, float rate) {

  auto const [grads, loss] = eval_model(params, dag, p_eval, y);

  let retrieve_parameters_weights = [&]() -> vector_t<float> {
    vector_t<float> weights;
    for (let &p : params) {
      weights.push_back(p.value);
    }
    return weights;
  };

  for (auto &p : params) {
    p.value -= grads[p.id] * rate;
  }
  on_iteration({epoch, rate, loss, retrieve_parameters_weights});
}

void _fit(vector_t<fsample_t> const &samples,
          bound_model_t const &bound_model,
          loss_func_t const &loss,
          vector_t<dag::var_value_t> &params,
          dag::dag_t const &dag,
          expr::ops_t const &ops,
          basic_scheduler_t const &scheduler,
          on_iteration_t const &on_iteration) {
  let y = loss(samples, bound_model, ops);
  for (auto e = 0; e < scheduler.max_epoch; ++e) {
    perform_descent_step(params, dag, nullptr, on_iteration, y, e,
                         scheduler.learning_rate);
  }
}

void _fit(vector_t<fsample_t> const &samples,
          bound_model_t const &bound_model,
          loss_func_t const &loss,
          vector_t<dag::var_value_t> &params,
          dag::dag_t const &dag,
          expr::ops_t const &ops,
          warmup_decay_scheduler_t const &scheduler,
          on_iteration_t const &on_iteration) {
  let y = loss(samples, bound_model, ops);

  // TODO:
  //  - use compiled version if desired.
  //  - specify optimization level (-O3 is very slow on fully inlined functions)
  //  Note: current compiled version is only x2 times faster then interpreted
  //        TODO:
  //         - remove allocations.
  //         - forward 'tensor' in the c source, to allow vectorization and
  //           to reduced the code size.
  jit_compiler::evaluator_t *p_compiled_eval = nullptr;
#if 0
  let compiled_version = true;
#else
  let compiled_version = false;
#endif
  jit_compiler::result_t<jit_compiler::unique_ptr_t<jit_compiler::evaluator_t>> opt_p_eval{jit_compiler::error_t{}};

  if (compiled_version) {
    opt_p_eval = jit_compiler::compile_dag(dag, "gcc", "/tmp/model.c", "/tmp/model.so", false);
    if (!opt_p_eval) {
      throw std::runtime_error(opt_p_eval.get_error().msg.c_str_host());
    }
    p_compiled_eval = (*opt_p_eval).get();
    CHECK(opt_p_eval);
  }

  auto rate = scheduler.init_learning_rate;
  auto e = 0;
  for (auto ew = 0; ew < scheduler.num_warmup_iterations; ++ew) {
    perform_descent_step(params, dag, p_compiled_eval, on_iteration, y, e++, rate);
    rate *= scheduler.warmup_rate;
  }
  for (auto ed = 0; ed < scheduler.num_descent_iterations; ++ed) {
    perform_descent_step(params, dag, p_compiled_eval, on_iteration, y, e++, rate);
    rate *= scheduler.decay_rate;
  }
}

void fit(vector_t<fsample_t> const &samples,
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

  fit(samples, bound_model, loss, params_values, dag, ops,
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
