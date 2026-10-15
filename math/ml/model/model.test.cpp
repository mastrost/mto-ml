//[mto.import ./model]
//[mto.import ./loss_functions]
//[mto.import ../expr/expr]
//[mto.import ../expr/dag]
//[mto.import cpp_tools/unittest:UNITTEST#]
//[mto.import no_stl/math/functions as math]
#include <cstdio>

//[mto-gen.begin]
#include "./model.h"
#include "./loss_functions.h"
#include "./../expr/expr.h"
#include "./../expr/dag.h"
#include "cpp_tools/unittest.h"
#include "no_stl/math/functions.h"
namespace mto::math::ml::model::model {
namespace model = mto::math::ml::model::model;
namespace loss_functions = mto::math::ml::model::loss_functions;
namespace expr = mto::math::ml::expr::expr;
namespace dag = mto::math::ml::expr::dag;
namespace math = mto::no_stl::math::functions;
}
#include "cpp_tools/defines.h"
//[mto-gen.end]
//[mto]
namespace mto::math::ml::model::model {//[mto.module-begin]

bool equals(float a, float b) {
  return math::fabs(a - b) < .0001f;
}

void test_regression() {
  vector_t<fsample_t> samples;

  for (int i = 0; i < 10; ++i) {
    let x = float(i);
    samples.push_back({{x}, {x}});
  }

  let on_iteration = [](iteration_cb_data_t const &data) {
    let weights = data.retrieve_parameters_weights();
    // printf("%f,%f ; %f\n", weights[0], weights[1], data.loss);
  };

  let optimizer_params = basic_scheduler_t{10, .01f};

  let linear_model = create_linear_model_1d();
  let init_params = linear_model.get_init_parameters_values();

  let params_values = fit_model(linear_model, loss_functions::mse_loss,
                                init_params, samples,
                                optimizer_params, on_iteration);

  let predictor = build_predictor(linear_model, params_values);

  let x = float(1);
  let Y = predictor({x});
  CHECK(Y.size() == 1);
  // printf("model(%f) = %f\n", x, Y[0]);
}

vector_t<fsample_t>
get_binary_classification_samples(float p_y0,
                                  float y0, float y1,
                                  int32_t num_samples) {
  vector_t<fsample_t> samples;
  for (int i = 0; i < num_samples; ++i) {
    if (i < num_samples * p_y0) {
      samples.push_back({{}, {y0}});
    } else {
      samples.push_back({{}, {y1}});
    }
  }
  return samples;
}

vector_t<float>
fit(model_t const &model, loss_func_t const &loss,
    vector_t<fsample_t> const &samples,
    int32_t max_iter, float learning_rate) {
  let init_params = model.get_init_parameters_values();
  let optimizer_params = basic_scheduler_t{max_iter, learning_rate};
  let on_iteration = [](iteration_cb_data_t const &data) {
    let weights = data.retrieve_parameters_weights();
    // printf("%f ; %f\n", weights[0], data.loss);
  };

  return fit_model(model, loss, init_params, samples,
                   optimizer_params, on_iteration);
}

// le modèle est directement la probabilité à estimer
void test_binary_classification_raw() {
  let p_y0_real = .80f;
  let y0 = 0;
  let y1 = 1;
  let samples = get_binary_classification_samples(p_y0_real, y0, y1, 100);

  let sigmoid_model_func = [](cspan_t<real_t> params,
                              cspan_t<real_t> X, expr::ops_t ops) -> vector_t<real_t> {
    REQUIRES(params.size() == 1);
    let p_y0 = params[0];
    return {p_y0};
  };

  let model = model_t{sigmoid_model_func, []() -> vector_t<float> { return {.5f}; },
                      1, 0};

  let loss = loss_functions::get_binary_nll_loss(y0, y1);

  let params_values = fit(model, loss, samples, 100, .1f);

  CHECK(equals(params_values[0], p_y0_real));
}

// le modèle est un logit.
void test_binary_classification_sigmoid() {
  let p_y0_real = .80f;
  let y0 = 0;
  let y1 = 1;
  let samples = get_binary_classification_samples(p_y0_real, y0, y1, 100);

  let sigmoid_model_func = [](cspan_t<real_t> params,
                              cspan_t<real_t> X, expr::ops_t ops) -> vector_t<real_t> {
    REQUIRES(params.size() == 1);
    let p_y0 = sigmoid(params[0]);
    return {p_y0};
  };

  let model = model_t{sigmoid_model_func, []() -> vector_t<float> { return {.5f}; },
                      1, 0};

  let loss = loss_functions::get_binary_nll_loss(y0, y1);

  let params_values = fit(model, loss, samples, 100, 1.f);

  CHECK(equals(expr::sigmoid(params_values[0]), p_y0_real));
}

vector_t<fsample_t>
get_multiclass_classification_samples(
    float RED, float BLUE, float GREEN,
    float p_RED_real, float p_BLUE_real,
    int32_t num_samples) {

  vector_t<fsample_t> samples;
  for (auto i = 0; i < num_samples; ++i) {
    if (i < num_samples * p_RED_real) {
      samples.push_back({{}, {RED}});
    } else if (i < num_samples * (p_RED_real + p_BLUE_real)) {
      samples.push_back({{}, {BLUE}});
    } else {
      samples.push_back({{}, {GREEN}});
    }
  }
  return samples;
}

void test_multiclass_classification_raw() {
  let RED = 66;
  let BLUE = 77;
  let GREEN = 88;
  let p_RED_real = .5f;
  let p_BLUE_real = .2f;

  let samples = get_multiclass_classification_samples(
      RED, BLUE, GREEN, p_RED_real, p_BLUE_real, 1000);

  // pour n classes, il y n-1 degres de libertés (poids)
  let model_func = [](cspan_t<real_t> params,
                      cspan_t<real_t> X, expr::ops_t ops) -> vector_t<real_t> {
    REQUIRES(params.size() == 2);
    return {params[0], params[1], 1 - params[0] - params[1]};
  };

  let model = model_t{model_func, []() -> vector_t<float> {
                        return {1.f / 3, 1.f / 3};
                      },
                      2, 0};

  let loss = loss_functions::get_nll_loss({RED, BLUE, GREEN});

  let params_values = fit(model, loss, samples, 100, .1f);

  CHECK(equals(params_values[0], p_RED_real));
  CHECK(equals(params_values[1], p_BLUE_real));
}

void test_multiclass_classification_softmax() {
  let RED = 66;
  let BLUE = 77;
  let GREEN = 88;
  let p_RED_real = .5f;
  let p_BLUE_real = .2f;

  let samples = get_multiclass_classification_samples(
      RED, BLUE, GREEN, p_RED_real, p_BLUE_real, 1000);

  // pour n classes, il y n-1 degres de libertés (poids)
  let model_func = [](cspan_t<real_t> params,
                      cspan_t<real_t> X, expr::ops_t ops) -> vector_t<real_t> {
    REQUIRES(params.size() == 2);
    let probas = expr::softmax_dim_minus_one(params);
    REQUIRES(probas.size() == 3);
    return probas;
  };

  let model = model_t{model_func, []() -> vector_t<float> {
                        return {1.f / 3, 1.f / 3};
                      },
                      2, 0};

  let loss = loss_functions::get_nll_loss({RED, BLUE, GREEN});

  let params_values = fit(model, loss, samples, 100, 1.f);
  let probas = expr::softmax_dim_minus_one(params_values);

  CHECK(equals(probas[0], p_RED_real));
  CHECK(equals(probas[1], p_BLUE_real));
  CHECK(equals(probas[2], 1 - p_RED_real - p_BLUE_real));
}

UNITTEST() {
  test_binary_classification_raw();
  test_binary_classification_sigmoid();
  test_multiclass_classification_raw();
  test_multiclass_classification_softmax();
  test_regression();

  // TODO:
  //  - Energy distance
  //    => see 'energy score Gneiting–Raftery', which looks adpated
  //       to the special case where (X,Y) is causal Y=F(X), even
  //       if Y is stochastic.
}

}//[mto.module-end]
