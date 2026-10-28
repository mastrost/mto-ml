//[mto.import ./loss_functions]

//[mto-gen.begin]
#include "./loss_functions.h"
namespace mto::math::ml::model::loss_functions {
namespace loss_functions = mto::math::ml::model::loss_functions;
}
#include "cpp_tools/defines.h"
//[mto-gen.end]
//[mto]
namespace mto::math::ml::model::loss_functions {//[mto.module-begin]

real_t mse_loss(vector_t<fsample_t> const &samples,
                bound_model_t const &bound_model,
                expr::ops_t ops) {
  vector_t<vector_t<real_t>> samples_y;
  vector_t<vector_t<real_t>> predictions;
  for (let &s : samples) {
    samples_y.push_back(ops(s.Y));
    predictions.push_back(bound_model(ops(s.X), ops));
  }
  return mse(samples_y, predictions);
}

loss_func_t get_binary_nll_loss(float y0, float y1) {
  let binary_nll_loss = [y0, y1](vector_t<fsample_t> const &samples,
                                 bound_model_t const &model,
                                 expr::ops_t ops) -> real_t {
    auto loss = ops(0);
    for (let &sample : samples) {
      REQUIRES(sample.Y.size() == 1);
      let y = sample.Y[0];
      REQUIRES(y == y0 || y == y1);
      let y_law = model(ops(sample.X), ops);
      REQUIRES(y_law.size() == 1);
      let p_y0 = y_law[0];
      let p_y1 = 1 - y_law[0];
      let py = y == y0 ? p_y0 : p_y1;
      loss -= log(py);
    }
    return loss / float(samples.size());
  };
  return binary_nll_loss;
}

loss_func_t get_nll_loss(vector_t<float> const &Y_values) {
  let nll_loss = [Y_values](vector_t<fsample_t> const &samples,
                            bound_model_t const &model,
                            expr::ops_t ops) -> real_t {
    auto loss = ops(0);
    for (let &sample : samples) {
      REQUIRES(sample.Y.size() == 1);
      let y = sample.Y[0];
      // ops.requires(y in Y_values);

      let y_law = model(ops(sample.X), ops);
      REQUIRES(y_law.size() == Y_values.size());

      // TODO: remove the expr.cases: we can do the switch
      //       case statically because the samples are constants.
      vector_t<expr::ops_t::case_t> cases;
      for (let i_case : Y_values.foreach_index()) {
        cases.push_back({ops(Y_values[i_case]), y_law[i_case]});
      }
      let py = ops.cases(ops(y), cases);
      loss -= log(py);
    }
    return loss / float(samples.size());
  };
  return nll_loss;
}

loss_func_t get_nll_loss() {
  let nll_loss = [](vector_t<fsample_t> const &samples,
                    bound_model_t const &model,
                    expr::ops_t ops) -> real_t {
    auto loss = ops(0);
    for (let &sample : samples) {
      REQUIRES(sample.Y.size() == 1);
      let y = sample.Y[0];
      let y_law = model(ops(sample.X), ops);
      REQUIRES(y >= 0 && y < y_law.size() && float(int(y)) == y);
      let py = y_law[y];
      loss -= log(py);
    }
    return loss / float(samples.size());
  };
  return nll_loss;
}

}//[mto.module-end]
