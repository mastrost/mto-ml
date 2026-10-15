#include <cstdio>
#include <random>

#include "./common.h"
#include "./../../expr/expr.h"
#include "./../../expr/dag.h"
#include "./../../expr/dag_eval.h"
#include "cpp_tools/main.h"
#include "no_stl/result/error.h"
#include "no_stl/system/file/file_utils.h"
#include "no_stl/math/functions.h"
#include "no_stl/vector/vector.h"
namespace mto::math::ml::projects::makemore::bigram2 {
namespace common = mto::math::ml::projects::makemore::common;
namespace expr = mto::math::ml::expr::expr;
namespace dag = mto::math::ml::expr::dag;
namespace dag_eval = mto::math::ml::expr::dag_eval;
using mto::no_stl::result::error::result_t;
using mto::no_stl::result::error::error_t;
using mto::no_stl::result::error::empty_t;
namespace file_utils = mto::no_stl::system::file::file_utils;
using mto::no_stl::math::functions::min;
using mto::no_stl::vector::vector::vector_t;
}
#include "cpp_tools/defines.h"
namespace mto::math::ml::projects::makemore::bigram2 {

typedef expr::mat_t::shape_t shape_t;

shape_t shape(shape_t x) {
  return x;
}

std::mt19937 gen(0);

size_t sample(vector_t<float> const &probs) {
  std::discrete_distribution<size_t> dist(probs.begin(), probs.end());
  return dist(gen);
}

// model: precicts the probability of each possible character
//        using a simple linear neuron layers, with one-hot encoding.
//        This can be implemented with matrix operations only.
result_t<> run(int argc, char const **argv) {
  let words = GET_RES(file_utils::read_lines(argv[1]));
  let bigrams = common::extract_bigrams(words.span_of().slice(0, min(int(words.size()), 100)));
  // let bigrams = common::extract_bigrams(words);
  printf("num bigrames: %d\n", int(bigrams.size()));
  let b = int(bigrams.size()); // batch size
  // X, Y: one hot encoded (char -> next char)

  auto dag = dag::dag_t{};
  auto ops = expr::ops_t{&dag};
  let X = ops.mat(b, 28);
  let Y = ops.mat(b, 28);
  // in practice, the one hot encoding acts as a lookup
  // to the good row of W. The row 'c' W(c, :) is the "probability"
  // (logits in fact) of each next caracter of 'c'.
  let W = ops.mat(28, 28, false);
  let Logits = X * W; // (b, 28)
  CHECK(Logits.shape == shape({b, 28}));

  // Loss = cross entropy (CE), which is natural for one hot encoding of Y
  let Logits_exp = exp(Logits); // (b, 28)
  // TODO:
  //  - softmax helper
  //  - merge softmax & Logits to avoid exp
  let Probas = Logits_exp / sum_last_dim(Logits_exp);
  CHECK(Probas.shape == shape({b, 28}));

  // cross entropy computing. In practice, the one hot encoding
  // of `Y` acts as a lookup to the good row of `Proba`
  let Likelyhoods = -Y % log(Probas);
  CHECK(Likelyhoods.shape == shape({b, 28}));
  // the loss for one sample is the sum over all Likelyhoods
  // (i.e. this is the cross entropy)
  // the loss for the whole batch is the sum over all samples,
  // => so we just have to sum over the whole matrix.
  //    (and normalize on the batch size)
  let Loss = sum_all_dims(Likelyhoods) / ops.const_mat({{float(b)}});
  CHECK(Loss.shape == shape({1, 1}));

  let p_dag_eval = dag_eval::create_dag_evaluator(&dag);
  let p_values = p_dag_eval->allocate();
  // set samples (X Y) one and for all
  auto X_values = p_values->as_fmat(X.id);
  auto Y_values = p_values->as_fmat(Y.id);
  for (let &i_bigram : bigrams.foreach_index()) {
    let x_one_hot = common::char_one_hot(bigrams[i_bigram][0]);
    let y_one_hot = common::char_one_hot(bigrams[i_bigram][1]);
    for (let k : x_one_hot.foreach_index()) {
      X_values(i_bigram, k) = x_one_hot[k];
      Y_values(i_bigram, k) = y_one_hot[k];
    }
  }
  // init weights
  auto W_values = p_values->as_fmat(W.id);
  for (int32_t i = 0; i < W.shape[0]; ++i) {
    for (int32_t j = 0; j < W.shape[1]; ++j) {
      W_values(i, j) = 1.f / 28.f;
    }
  }

  auto &loss = p_values->as_fmat(Loss.id)(0, 0);

  let p_bw_grad_values = p_dag_eval->allocate();
  auto &dloss = p_bw_grad_values->as_fmat(Loss.id)(0, 0);
  auto dW = p_bw_grad_values->as_fmat(W.id);

  for (int i = 0; i < 100; ++i) {
    let eval_res = p_dag_eval->eval(*p_values);
    CHECK(eval_res);
    printf("%d: %f\n", i, loss);
    p_bw_grad_values->zero();
    dloss = 1;
    let bw_grad_eval_res = p_dag_eval->eval_bw_grad(*p_values, *p_bw_grad_values);
    CHECK(bw_grad_eval_res);
    let lr = 50.f;
    for (int32_t i = 0; i < W.shape[0]; ++i) {
      for (int32_t j = 0; j < W.shape[1]; ++j) {
        W_values(i, j) -= dW(i, j) * lr;
      }
    }
  }

  // make a few predictions
  for (int w = 0; w < 10; ++w) {
    auto c = common::begin;
    while (c != common::end) {
      printf("%c", c);
      // probs for char c = softmax(W(c, :))
      vector_t<float> probs;
      float sum_exp = 0.f;
      for (int32_t j = 0; j < W_values.shape[1]; ++j) {
        sum_exp += std::exp(W_values(common::to_index(c), j));
      }
      for (int32_t j = 0; j < W_values.shape[1]; ++j) {
        probs.push_back(std::exp(W_values(common::to_index(c), j)) / sum_exp);
      }
      CHECK(probs.size() == 28);
      c = common::to_char(sample(probs));
    }
    printf("%c\n", c);
  }

  return empty_t{};
}

MAIN(argc, argv) {
  // TODO:
  //  - example 1: matrix model with one hot encoding
  //  - example 2: matrix model with lookup table
  let res = run(argc, argv);
  if (!res) {
    fprintf(stderr, "Error: %s\n", res.get_error().msg.c_str_host().c_str());
    return 1;
  }
  return 0;
}

}
