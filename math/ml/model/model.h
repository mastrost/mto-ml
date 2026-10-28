#pragma once
//[mto.import ../expr/expr]
//[mto.import no_stl/vector/vector:vector_t]
//[mto.import no_stl/function/function:function_t]
//[mto.import no_stl/span/span:cspan_t]
//[mto.import no_stl/variant/stack_variant:stack_variant_t]

//[mto-gen.begin]
#include "./../expr/expr.h"
#include "no_stl/vector/vector.h"
#include "no_stl/function/function.h"
#include "no_stl/span/span.h"
#include "no_stl/variant/stack_variant.h"
namespace mto::math::ml::model::model {
namespace expr = mto::math::ml::expr::expr;
using mto::no_stl::vector::vector::vector_t;
using mto::no_stl::function::function::function_t;
using mto::no_stl::span::span::cspan_t;
using mto::no_stl::variant::stack_variant::stack_variant_t;
}
#include "cpp_tools/defines.h"
//[mto-gen.end]
//[mto]
namespace mto::math::ml::model::model {//[mto.module-begin]

using expr::real_t;

struct sample_t {
  vector_t<real_t> X;
  vector_t<real_t> Y;
};

struct fsample_t {
  vector_t<float> X;
  vector_t<float> Y;
};

typedef function_t<vector_t<real_t>(
    cspan_t<real_t> X, expr::ops_t ops)>
    bound_model_t;

typedef function_t<vector_t<real_t>(cspan_t<real_t> params,
                                    cspan_t<real_t> X,
                                    expr::ops_t ops)>
    model_func_t;

/**
 * The loss is linked to the type of prediction.
 * Each loss assumes a specific structure and semantics for
 * the predictions.
 * Ex: binary NLL loss:
 * * assumes a 1D prediction (taking values in {'0', '1'}, for example)
 * * 1D-valued model: the probability of '0'
 *
 * Version with samples as constants (in order to be compatible
 * with discrete variables and nll loss).
 * Note: samples could be `real_t` based (non constant) in other cases.
 */
typedef function_t<real_t(vector_t<fsample_t> const &samples,
                          bound_model_t const &bound_model,
                          expr::ops_t ops)>
    loss_func_t;

struct model_t {
  model_func_t compute;
  function_t<vector_t<float>()> get_init_parameters_values;
  size_t num_parameters;
  size_t num_inputs;

  bound_model_t bind(vector_t<real_t> const &params) const;
};

/**
 * Simple models
 */
// y = a x * b (scalaires) (2 params, 1 input)
model_t create_linear_model_1d();

/**
 * model fitting
 */

struct iteration_cb_data_t {
  int32_t epoch;
  float learning_rate;
  float loss;
  function_t<vector_t<float>()> retrieve_parameters_weights;
};

typedef function_t<void(iteration_cb_data_t const &data)> on_iteration_t;

struct basic_scheduler_t {
  int32_t max_epoch = 10;
  float learning_rate;
};

struct warmup_decay_scheduler_t {
  float init_learning_rate;
  float warmup_rate;
  int32_t num_warmup_iterations;
  float decay_rate;
  int32_t num_descent_iterations;
};

typedef stack_variant_t<basic_scheduler_t, warmup_decay_scheduler_t>
    any_scheduler_t;

/**
 * model, loss, samples must be compatible.
 */
vector_t<float>
fit_model(model_t const &model,
          loss_func_t const &loss,
          vector_t<float> const &init_params,
          vector_t<fsample_t> const &samples,
          any_scheduler_t const &scheduler,
          on_iteration_t const &on_iteration);

typedef function_t<vector_t<float>(vector_t<float> const &)> predictor_t;

/**
 * TODO:
 *  - version that takes X and Params as parameters (for evaluation during
 *    training)
 */
predictor_t
build_predictor(model_t const &model,
                vector_t<float> const &params_values);

}//[mto.module-end]
