//[mto.import ./common]
//[mto.import ../../expr/expr]
//[mto.import ../../mlp/mlp]
//[mto.import ../../model/model:real_t,]
//[mto.import ../../model/loss_functions]
//[mto.import no_stl/vector/vector:vector_t]
//[mto.import no_stl/string/string:string_t]
//[mto.import no_stl/system/file/file_utils]
//[mto.import no_stl/result/error:result_t,error_t,empty_t]
//[mto.import no_stl/span/span:cspan_t]
//[mto.import cpp_tools/main:MAIN#]

#include <random>

#include <cstdio>

//[mto-gen.begin]
#include "./common.h"
#include "./../../expr/expr.h"
#include "./../../mlp/mlp.h"
#include "./../../model/model.h"
#include "./../../model/loss_functions.h"
#include "no_stl/vector/vector.h"
#include "no_stl/string/string.h"
#include "no_stl/system/file/file_utils.h"
#include "no_stl/result/error.h"
#include "no_stl/span/span.h"
#include "cpp_tools/main.h"
namespace mto::math::ml::projects::makemore::bigram {
namespace common = mto::math::ml::projects::makemore::common;
namespace expr = mto::math::ml::expr::expr;
namespace mlp = mto::math::ml::mlp::mlp;
using mto::math::ml::model::model::real_t;
namespace model = mto::math::ml::model::model;
namespace loss_functions = mto::math::ml::model::loss_functions;
using mto::no_stl::vector::vector::vector_t;
using mto::no_stl::string::string::string_t;
namespace file_utils = mto::no_stl::system::file::file_utils;
using mto::no_stl::result::error::result_t;
using mto::no_stl::result::error::error_t;
using mto::no_stl::result::error::empty_t;
using mto::no_stl::span::span::cspan_t;
}
#include "cpp_tools/defines.h"
//[mto-gen.end]
//[mto]
namespace mto::math::ml::projects::makemore::bigram {//[mto.module-begin]

using namespace common;

vector_t<float> one_hot(size_t index) {
  auto enc = vector_t<float>(num_chars, 0);
  enc[index] = 1;
  return enc;
}

// samples adapted to nll loss function:
//  X: one hot encoding
//  Y: {index}
vector_t<model::fsample_t>
to_samples(vector_t<bigram_t> const &bigrams) {
  vector_t<model::fsample_t> samples;
  for (let &b : bigrams) {
    samples.push_back({one_hot(to_index(b[0])), {to_findex(b[1])}});
  }
  return samples;
}

// model: precicts the probability of each possible character
//        using a simple linear neuron layers, with one-hot encoding.
vector_t<real_t>
predicts(cspan_t<real_t> W, cspan_t<real_t> X, expr::ops_t ops) {
  vector_t<real_t> Y;
  mlp::layer_t layer(num_chars, num_chars, mlp::activation_t::linear, W, ops);
  return softmax(layer.eval(X));
}

vector_t<float>
get_init_parameters_values() {
  vector_t<float> values;
  mlp::layer_t::get_init_parameters_values(num_chars, num_chars, values);
  return values;
}

std::mt19937 gen(0);

size_t sample(vector_t<float> const &probs) {
  std::discrete_distribution<size_t> dist(probs.begin(), probs.end());
  return dist(gen);
}

/**
 * This version is fully 'flattened' to floats, which makes
 * the expression compilation very slow with the full set of
 * samples.
 */
result_t<> run(int argc, char const **argv) {
  if (argc != 2) {
    return error_t{"invalid usage"};
  }

  let words = GET_RES(file_utils::read_lines(argv[1]));
  let bigrams = extract_bigrams(words);

  if (false) {
    for (let &b : bigrams.span_of().slice(0, 10)) {
      let c0 = to_char(to_findex(b[0]));
      let c1 = to_char(to_findex(b[1]));
      printf("%c%c\n", c0, c1);
    }
  }

  let samples = to_samples(bigrams);

  let model = model::model_t{predicts,
                             get_init_parameters_values,
                             get_init_parameters_values().size(), num_chars};

  let loss = loss_functions::get_nll_loss();

  let scheduler = model::basic_scheduler_t{10, 10};

  let on_iteration = [&](model::iteration_cb_data_t const &data) {
    printf("loss: %f\n", data.loss);
  };

  let init_params = model.get_init_parameters_values();

  let params = fit_model(model, loss, init_params,
                         samples, scheduler, on_iteration);

  let predictor = model::build_predictor(model, params);

  for (int w = 0; w < 20; ++w) {
    auto char_index = to_index(begin);
    while (char_index != to_index(end)) {
      printf("%c", to_char(char_index));
      let probs = predictor(one_hot(char_index));
      char_index = sample(probs);
    }
    printf("%c\n", to_char(char_index));
  }

  return empty_t{};
}

MAIN(argc, argv) {
  let res = run(argc, argv);
  if (!res) {
    fprintf(stderr, "Error: %s\n", res.get_error().msg.c_str_host().c_str());
    return 1;
  }
  return 0;
}

}//[mto.module-end]
