#pragma once

//[mto.import ./model]
//[mto.import ../expr/expr]
//[mto.import no_stl/vector/vector:vector_t]
//[mto.import no_stl/span/span:cspan_t]

//[mto-gen.begin]
#include "./model.h"
#include "./../expr/expr.h"
#include "no_stl/vector/vector.h"
#include "no_stl/span/span.h"
namespace mto::math::ml::model::loss_functions {
namespace model = mto::math::ml::model::model;
namespace expr = mto::math::ml::expr::expr;
using mto::no_stl::vector::vector::vector_t;
using mto::no_stl::span::span::cspan_t;
}
#include "cpp_tools/defines.h"
//[mto-gen.end]
//[mto]
namespace mto::math::ml::model::loss_functions {//[mto.module-begin]

using model::loss_func_t;
using model::bound_model_t;
using model::fsample_t;
using expr::real_t;

real_t compute_samples_mse(cspan_t<vector_t<real_t>> samples,
                           cspan_t<vector_t<real_t>> predictions,
                           expr::ops_t ops);

real_t mse_loss(vector_t<fsample_t> const &samples,
                bound_model_t const &bound_model,
                expr::ops_t ops);

// The loss assumes the model outputs values in R: the probability of y0.
// One way to achieve this is to use a sigmoid function from a
// real-valued input (and not a non-negative output like a ReLU)
loss_func_t get_binary_nll_loss(float y0, float y1);

// The loss assumes that the model represents the probability of each class.
// Note: this version is adapted to small number of categories ('enum' like),
//       not to generic discrete laws.
//       When adapted, it avoids encoding the values.
loss_func_t get_nll_loss(vector_t<float> const &Y_values);

// The loss assumes that the model represents the probability of each class.
// Adapated to discrete laws with values in
// {0, .... , num_values - 1}
loss_func_t get_nll_loss();

}//[mto.module-end]
