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
using model::sample_t;
using expr::real_t;

real_t compute_samples_mse(cspan_t<vector_t<real_t>> samples,
                           cspan_t<vector_t<real_t>> predictions,
                           expr::ops_t ops);

real_t mse_loss(vector_t<sample_t> const &samples,
                bound_model_t const &bound_model,
                expr::ops_t ops);

// la loss suppose le modèle à valeur dans R: la probabilité de y0.
// Une façon de faire et d'utiliser une sigmoid depuis une entrée a valeur
// dans R (et *pas* a valeur dans R+ comme un relu).
loss_func_t get_binary_nll_loss(float y0, float y1);

// la loss suppose que le modèle represente les probabilités
// de chaque classe
loss_func_t get_nll_loss(vector_t<float> const &Y_values);

}//[mto.module-end]
