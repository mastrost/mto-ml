//[mto.import ./mlp]
//[mto.import ../expr/expr]
//[mto.import ../expr/dag:,dag_t]
//[mto.import ../model/model]
//[mto.import ../model/loss_functions]
//[mto.import cpp_tools/unittest:UNITTEST#]
//[mto.import no_stl/math/functions:sqrt]
#include <cstdio>

//[mto-gen.begin]
#include "./mlp.h"
#include "./../expr/expr.h"
#include "./../expr/dag.h"
#include "./../model/model.h"
#include "./../model/loss_functions.h"
#include "cpp_tools/unittest.h"
#include "no_stl/math/functions.h"
namespace mto::math::ml::mlp::mlp {
namespace mlp = mto::math::ml::mlp::mlp;
namespace expr = mto::math::ml::expr::expr;
namespace dag = mto::math::ml::expr::dag;
using mto::math::ml::expr::dag::dag_t;
namespace model = mto::math::ml::model::model;
namespace loss_functions = mto::math::ml::model::loss_functions;
using mto::no_stl::math::functions::sqrt;
}
#include "cpp_tools/defines.h"
//[mto-gen.end]
//[mto]
namespace mto::math::ml::mlp::mlp {//[mto.module-begin]

void write_predictor_1_to_1(model::predictor_t const &f,
                            float x_min,
                            float const x_max,
                            int32_t const grid_size) {
  REQUIRES(grid_size >= 2);
  let dx = (x_max - x_min) / (grid_size - 1);
  for (int32_t i = 0; i < grid_size; ++i) {
    let x = x_min + i * dx;
    let Y = f({x});
    printf("%f;%f\n", x, Y[0]);
  }
}

void write_predictor_2_to_1(model::predictor_t const &f,
                            vector_t<float> x_mins,
                            vector_t<float> x_maxs,
                            vector_t<int32_t> grid_sizes) {
  let dx0 = (x_maxs[0] - x_mins[0]) / (grid_sizes[0] - 1);
  let dx1 = (x_maxs[1] - x_mins[1]) / (grid_sizes[1] - 1);

  for (int32_t i = 0; i < grid_sizes[0]; ++i) {
    for (int32_t j = 0; j < grid_sizes[1]; ++j) {
      let x0 = x_mins[0] + i * dx0;
      let x1 = x_mins[1] + j * dx1;
      let Y = f({x0, x1});
      printf("%f;%f;%f\n", x0, x1, Y[0]);
    }
  }
}

// le predicteur prédit la probabilité de chaque y_values[i]
float get_classifier_accuracy(model::predictor_t const &f,
                              vector_t<model::fsample_t> const &samples,
                              vector_t<float> const &y_values,
                              float threshold) {
  size_t accuracy = 0;
  for (let &s : samples) {
    let p_y = f(s.X);
    let y = s.Y[0];
    GHOST(bool value_found = false);
    for (let i_y_value : y_values.foreach_index()) {
      if (y == y_values[i_y_value]) {
        GHOST(value_found = true);
        if (p_y[i_y_value] > threshold) {
          ++accuracy;
        }
        break;
      }
    }
    REQUIRES(value_found);
  }
  return float(accuracy) / samples.size();
}

// le predicteur ne prédit que P(y=y0)
float get_binary_classifier_accuracy(model::predictor_t const &f,
                                     vector_t<model::fsample_t> const &samples,
                                     float y0, float y1,
                                     float threshold) {
  let f2 = [f](vector_t<float> const &X) -> vector_t<float> {
    let p_y = f(X);
    REQUIRES(p_y.size() == 1);
    return {p_y[0], 1 - p_y[0]};
  };
  return get_classifier_accuracy(f2, samples, {y0, y1}, threshold);
}

void test_binary_classification_X_1d() {
  let RED = 10.f;
  let BLUE = 20.f;

  vector_t<model::fsample_t> samples;
  for (int i = 1; i < 10; ++i) {
    samples.push_back({{float(-i)}, {RED}});
    samples.push_back({{float(+i)}, {BLUE}});
  }

  // 1 neuron linéaire  + sigmoid
  let sigmoid_model_func = [](cspan_t<real_t> params,
                              cspan_t<real_t> X, expr::ops_t ops) -> vector_t<real_t> {
    REQUIRES(params.size() == 2);
    REQUIRES(X.size() == 1);
    // Note: ne pas utiliser relu -> sigmoid
    auto neuron = neuron_t{1, activation_t::linear, params, ops};
    let logit = neuron.eval(X);
    return {sigmoid(logit)};
  };

  let get_init_parameters_values = []() -> vector_t<float> {
    vector_t<float> params;
    neuron_t::get_init_parameters_values(1, params);
    return params;
  };

  let model = model::model_t{sigmoid_model_func, get_init_parameters_values, 2, 1};

  let loss = loss_functions::get_binary_nll_loss(RED, BLUE);

  let init_params = model.get_init_parameters_values();
  let on_iteration = [&](model::iteration_cb_data_t const &data) {};
  let params = fit_model(model, loss, init_params, samples,
                         model::basic_scheduler_t{10, 1}, on_iteration);

  let predictor = build_predictor(model, params);

  let accuracy = get_binary_classifier_accuracy(predictor, samples, RED, BLUE, .9);
  CHECK(accuracy == 1);
  // write_predictor_1_to_1(predictor, -10, 10, 10);
}

vector_t<model::fsample_t>
get_samples(float RED, float BLUE) {
  vector_t<model::fsample_t> samples;
  int n = 10;
  for (int i = 0; i < n; ++i) {
    let x0 = float(i) / (n - 1);
    for (int j = 0; j < n; ++j) {
      let x1 = float(j) / (n - 1);
      let d2 = sqrt((x0 - .5) * (x0 - .5) + (x1 - .5) * (x1 - .5));
      float y = d2 > .4 ? RED : BLUE;
      samples.push_back({{x0, x1}, {y}});
    }
  }
  return samples;
}

void test_binary_classification_X_2d() {
  let RED = 10.f;
  let BLUE = 20.f;
  let samples = get_samples(RED, BLUE);
  let num_inputs = 2;
  let layers_sizes = vector_t<size_t>{8, 8, 1};
  let layers_activations = vector_t<activation_t>{
      activation_t::relu,
      activation_t::relu,
      activation_t::linear,
  };

  let get_init_parameters_values = [=]() -> vector_t<float> {
    vector_t<float> params;
    mlp_t::get_init_parameters_values(num_inputs, layers_sizes, params);
    return params;
  };

  let num_parameters = get_init_parameters_values().size();

  let sigmoid_model_func = [=](cspan_t<real_t> params,
                               cspan_t<real_t> X, expr::ops_t ops) -> vector_t<real_t> {
    REQUIRES(params.size() == num_parameters);
    REQUIRES(X.size() == num_inputs);
    mlp_t mlp(num_inputs, layers_sizes, layers_activations, params, ops);
    let logits = mlp.eval(X);
    REQUIRES(logits.size() == 1);
    return {sigmoid(logits[0])};
  };

  let model = model::model_t{sigmoid_model_func, get_init_parameters_values,
                             num_parameters, num_inputs};

  let loss = loss_functions::get_binary_nll_loss(RED, BLUE);

  let init_params = model.get_init_parameters_values();
  let on_iteration = [&](model::iteration_cb_data_t const &data) {
    printf("%f\n", data.loss);
  };

  // le warmup permet effectivement de stabiliser la descente.
  // le decay est essentiel pour à la fois :
  //  - avoir un decroissance rapide au debut
  //  - eviter les instabilité à la fin
  // -> ! si decay trop importante, on ne converge plus ...
  let scheduler = model::warmup_decay_scheduler_t{.1, 1.02, 100, .999, 1000};

  let params = fit_model(model, loss, init_params, samples,
                         scheduler, on_iteration);

  let predictor = build_predictor(model, params);

  let accuracy = get_binary_classifier_accuracy(predictor, samples, RED, BLUE, .8);
  printf("accuracy: %f\n", accuracy);
  CHECK(accuracy > .8);
  // write_predictor_2_to_1(predictor, {0,0}, {1,1}, {30,30});
}

UNITTEST() {
  test_binary_classification_X_1d();
  test_binary_classification_X_2d();
}

}//[mto.module-end]
