#pragma once

//[mto.import ../expr/expr:ops_t,real_t]
//[mto.import no_stl/vector/vector:vector_t]
//[mto.import no_stl/span/span:cspan_t]

//[mto-gen.begin]
#include "./../expr/expr.h"
#include "no_stl/vector/vector.h"
#include "no_stl/span/span.h"
namespace mto::math::ml::mlp::mlp {
using mto::math::ml::expr::expr::ops_t;
using mto::math::ml::expr::expr::real_t;
using mto::no_stl::vector::vector::vector_t;
using mto::no_stl::span::span::cspan_t;
}
#include "cpp_tools/defines.h"
//[mto-gen.end]
//[mto]
namespace mto::math::ml::mlp::mlp {//[mto.module-begin]

enum class activation_t { linear,
                          relu };

real_t eval_neuron(cspan_t<real_t> X,
                   real_t b, cspan_t<real_t> W,
                   activation_t activation,
                   ops_t ops);

struct neuron_t {
  // consomme les elements de 'params' pour initialiser b et W
  neuron_t(size_t num_inputs,
           activation_t _activation,
           cspan_t<real_t> &params,
           ops_t _ops);

  // meme ordre que le constructeur utilise pour `params`
  static void
  get_init_parameters_values(size_t num_inputs, vector_t<float> &params);

  real_t eval(cspan_t<real_t> X) const;

  real_t b;
  vector_t<real_t> W;
  activation_t activation;
  ops_t ops;
};

struct layer_t {
  layer_t(size_t num_inputs, size_t num_neurons,
          activation_t activation,
          cspan_t<real_t> &params,
          ops_t ops);

  static void
  get_init_parameters_values(size_t num_inputs, size_t num_neurons,
                             vector_t<float> &params);

  vector_t<real_t> eval(cspan_t<real_t> X) const;

  vector_t<neuron_t> neurons;
};

struct mlp_t {
  mlp_t(size_t num_inputs,
        vector_t<size_t> const &layers_sizes,
        vector_t<activation_t> const &layers_activations,
        cspan_t<real_t> &params, ops_t ops);

  static void
  get_init_parameters_values(size_t num_inputs,
                             vector_t<size_t> const &layers_sizes,
                             vector_t<float> &params);

  vector_t<real_t> eval(cspan_t<real_t> X) const;

  // doivent être de la forme (a,b) -> (b->c) -> (c->d)
  vector_t<layer_t> layers;
};

}//[mto.module-end]
