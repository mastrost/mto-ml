//[mto.import ./mlp]
//[mto.import ../expr/expr]
#include <cstdlib>

//[mto-gen.begin]
#include "./mlp.h"
#include "./../expr/expr.h"
namespace mto::math::ml::mlp::mlp {
namespace mlp = mto::math::ml::mlp::mlp;
namespace expr = mto::math::ml::expr::expr;
}
#include "cpp_tools/defines.h"
//[mto-gen.end]
//[mto]
namespace mto::math::ml::mlp::mlp {//[mto.module-begin]

namespace {
float frand() {
  return (float(rand()) / float(RAND_MAX)) * 2 - 1;
}

[[maybe_unused]] float frand(float min, float max) {
  return frand() * (max - min) + min;
}

}
real_t eval_neuron(cspan_t<real_t> X,
                   real_t b, cspan_t<real_t> W,
                   activation_t activation,
                   ops_t ops) {
  REQUIRES(X.size() == W.size());
  auto res = ops(0);
  for (let i : W.foreach_index()) {
    res += (X[i] * W[i]);
  }
  switch (activation) {
  case activation_t::linear:
    return res + b;
  case activation_t::relu:
    return expr::relu(res + b);
  };
  __builtin_unreachable();
}

/**
 * neuron
 */
neuron_t::neuron_t(size_t num_inputs,
                   activation_t _activation,
                   cspan_t<real_t> &params,
                   ops_t _ops)
    : b(params[0]),
      W(params.slice(1, num_inputs)),
      activation(_activation),
      ops(_ops) {
  params = params.slice(num_inputs + 1);
}

void neuron_t::get_init_parameters_values(size_t num_inputs,
                                          vector_t<float> &params) {
  params.push_back(0); // b
  for (auto i = 0u; i < num_inputs; ++i) {
    // TODO: utiliser seed
#if 1
    params.push_back(frand(-1, 1) / 10);
#else
    params.push_back(1);
#endif
  }
}

real_t neuron_t::eval(cspan_t<real_t> X) const {
  return eval_neuron(X, b, W, activation, ops);
}

/**
 * layer
 */
layer_t::layer_t(size_t num_inputs, size_t num_neurons,
                 activation_t activation,
                 cspan_t<real_t> &params,
                 ops_t ops) {
  for (auto i_n = 0u; i_n < num_neurons; ++i_n) {
    neurons.push_back(neuron_t(num_inputs, activation, params, ops));
  }
}

void layer_t::get_init_parameters_values(size_t num_inputs, size_t num_neurons,
                                         vector_t<float> &params) {
  for (auto i_n = 0u; i_n < num_neurons; ++i_n) {
    neuron_t::get_init_parameters_values(num_inputs, params);
  }
}

vector_t<real_t> layer_t::eval(cspan_t<real_t> X) const {
  vector_t<real_t> res;
  for (let &n : neurons) {
    res.push_back(n.eval(X));
  }
  // TODO: return `res` as a contiguous and aligned array 
  //       of variables, to enable vectorization
  //       in `eval_neuron`. 
  //       Note: weights must also be contiguous and aligned.
  //       -> we could ensure that with a special variable
  //          in [dag] and [expr]
  //          (maybe with a generalized `tensor` type)
  return res;
}

/**
 * mlp
 */
mlp_t::mlp_t(size_t num_inputs,
             vector_t<size_t> const &layers_sizes,
             vector_t<activation_t> const &layers_activations,
             cspan_t<real_t> &params, ops_t ops) {
  let layer_num_inputs = [&](size_t i_layer) -> size_t {
    return i_layer == 0 ? num_inputs : layers_sizes[i_layer - 1];
  };
  for (let i_layer : layers_sizes.foreach_index()) {
    let activation = layers_activations[i_layer];
    layers.push_back({layer_num_inputs(i_layer), layers_sizes[i_layer],
                      activation, params, ops});
  }
}

void mlp_t::get_init_parameters_values(size_t num_inputs,
                                       vector_t<size_t> const &layers_sizes,
                                       vector_t<float> &params) {
  let layer_num_inputs = [&](size_t i_layer) -> size_t {
    return i_layer == 0 ? num_inputs : layers_sizes[i_layer - 1];
  };
  for (let i_layer : layers_sizes.foreach_index()) {
    layer_t::get_init_parameters_values(layer_num_inputs(i_layer),
                                        layers_sizes[i_layer], params);
  }
}

vector_t<real_t> mlp_t::eval(cspan_t<real_t> X) const {
  auto res = vector_t<real_t>(X);
  for (let &layer : layers) {
    res = layer.eval(res);
  }
  return res;
}

}//[mto.module-end]
