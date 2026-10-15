#include <cstdio>

#include "./expr.h"
#include "./dag_eval.h"
#include "cpp_tools/unittest.h"
#include "no_stl/math/functions.h"
namespace mto::math::ml::expr::expr {
namespace expr = mto::math::ml::expr::expr;
namespace dag_eval = mto::math::ml::expr::dag_eval;
namespace math = mto::no_stl::math::functions;
}
#include "cpp_tools/defines.h"
namespace mto::math::ml::expr::expr {

typedef vector_t<dag_eval::var_value_t> vec;

void test_type() {
  {
    // row_major = true
    let t_row = type_t{dtype_t::f32, {2, 3}, true};
    CHECK(t_row.stride == dag::stride_t({3, 1}));

    // col major
    let t_col = type_t{dtype_t::f32, {2, 3}, false};
    CHECK(t_col.stride == dag::stride_t({1, 2}));
  }

  {
    CHECK(dag::end(ftype) == dag::offset_t(4));
    let t_row = type_t{dtype_t::f32, {2, 3}};
    CHECK(dag::end(t_row) == dag::offset_t(24));
    CHECK(dag::end(t_row) == dag::size(t_row));
    auto t_pad = type_t{dtype_t::f32, {2, 3}, dag::stride_t({4, 2})};
    CHECK(dag::end(t_pad) == dag::offset_t(36));
  }
}

float equals(float a, float b, float eps = .00001) {
  return math::fabs(a - b) < eps;
}

void test_cases() {
  auto dag = dag_t{};
  auto ops = ops_t{&dag};

  let x = ops.real();
  let y = ops.cases(
      ops(20), {
                   {ops(10), x},
                   {ops(20), x * x},
               });

  let values = eval(dag, vec{{x.id, 10}});
  CHECK(values[y.id] == 100);

  let bw_grad_values = eval_bw_grad(dag, values, vec{{y.id, 1}});
  CHECK(bw_grad_values[x.id] == 20);

  let fw_grad_values = eval_fw_grad(dag, values, vec{{x.id, 1}});
  CHECK(fw_grad_values[y.id] == 20);
}

// test fw grad VS bw grad VS finite differences
template <typename expression_t>
void test_expression(expression_t const &f, float x) {

  auto dag = dag_t{};
  auto ops = ops_t{&dag};
  let expr_x = ops.real();
  let expr_y = f(expr_x);
  let values = eval(dag, vec{{expr_x.id, x}});
  let y = f(x);
  CHECK(equals(values[expr_y.id], y, .0001));

  let eps = .00001f;
  let dy_dx = (f(x + eps) - y) / eps;

  let bw_grad_values = eval_bw_grad(dag, values, vec{{expr_y.id, 1}});
  let bw_grad = bw_grad_values[expr_x.id];

  let fw_grad_values = eval_fw_grad(dag, values, vec{{expr_x.id, 1}});
  let fw_grad = fw_grad_values[expr_y.id];

  CHECK(equals(fw_grad, bw_grad));
  // Warning:
  // - finite difference is a rather crude approximation.
  // - `exp` increases errors on large numbers
  CHECK(equals(bw_grad, dy_dx, .01));
}

template <typename expression_t, typename... f_ts>
void test_expressions(expression_t const &f, f_ts... xs) {
  (test_expression(f, xs), ...);
}

void test_expressions() {
  using expr::exp;
  using math::exp;
  using expr::log;
  using math::log;
  using expr::relu;
  using math::relu;

  test_expression([](auto x) { return 3 * x * x - 4 * x + 5; }, .5);
  test_expression([](auto x) { return x * x; }, 2);
  test_expression([](auto x) { return 1 / (x * x); }, 2);
  test_expression([](auto x) { return exp(x / 10); }, .1);
  test_expression([](auto x) { return log(x * x); }, 10);
  test_expressions([](auto x) { return relu(x * x); }, 2, -2);
}

void test_mat_expressions() {
  typedef values::fmat_t::shape_t shape_t;
  for (let b_row_major : {true, false}) {
    auto dag = dag_t{};
    auto ops = ops_t{&dag};
    let A = ops.mat(2, 3);
    let B = ops.mat(3, 1, b_row_major);
    let C = A * B; // (2, 1)
    let _const_val = 2.f;
    let _const = ops.const_mat(1, 1, _const_val);
    let D = C.t() * (C * _const); // (1, 1)
    let p_dag_eval = dag_eval::create_dag_evaluator(&dag);
    auto p_values = p_dag_eval->allocate();
    // set(p_values->as_fmat(_const.id), {{_const_val}});
    set(p_values->as_fmat(A.id), {{1, 2, 3}, {4, 5, 6}});
    set(p_values->as_fmat(B.id), {{10}, {20}, {30}});

    let res = p_dag_eval->eval(*p_values);
    auto matC = p_values->as_fmat(C.id);
    CHECK(matC.shape == (shape_t{2, 1}));
    let c0 = float(1 * 10 + 2 * 20 + 3 * 30);
    let c1 = float(4 * 10 + 5 * 20 + 6 * 30);
    CHECK(matC(0, 0) == c0);
    CHECK(matC(1, 0) == c1);

    auto matD = p_values->as_fmat(D.id);
    CHECK(matD.shape == (shape_t{1, 1}));
    CHECK(matD(0, 0) == (c0 * c0 + c1 * c1) * _const_val);

    auto p_bw_grad_values = p_dag_eval->allocate();

    // bw grad
    using values::vecvec_t;
    auto bw_dD_dB = vecvec_t{{0}, {0}, {0}};
    {
      p_bw_grad_values->zero();
      set(p_bw_grad_values->as_fmat(D.id), {{1}});
      let bw_res = p_dag_eval->eval_bw_grad(*p_values, *p_bw_grad_values);
      CHECK(bw_res);
      bw_dD_dB = to_vecvec(p_bw_grad_values->as_fmat(B.id));
    }

    // fw grad
    auto fw_dD_dB = vecvec_t{{0}, {0}, {0}};
    {
      auto p_fw_grad_values = p_dag_eval->allocate();

      let d_B0 = vecvec_t{{1}, {0}, {0}};
      let d_B1 = vecvec_t{{0}, {1}, {0}};
      let d_B2 = vecvec_t{{0}, {0}, {1}};

      int i = 0;
      for (let &d_B : {d_B0, d_B1, d_B2}) {
        p_fw_grad_values->zero();
        set(p_fw_grad_values->as_fmat(B.id), d_B);
        let fw_res = p_dag_eval->eval_fw_grad(*p_values, *p_fw_grad_values);
        CHECK(fw_res);
        let d_D = p_fw_grad_values->as_fmat(D.id)(0, 0);
        fw_dD_dB[i++][0] = d_D;
      }
    }

    // olé!
    CHECK(bw_dD_dB == fw_dD_dB);
  }
}

// Simple least square optimisation for fun.
// Shows a pure matrix based ML optimisation.
void test_least_square_optimisation() {
  typedef values::fmat_t::shape_t shape_t;

  struct sample_t {
    float x;
    float y;
  };

  // the underlying real model
  let real = [](float x) -> float {
    return 2 * x + 3;
  };

  // samples
  let _b = 100;
  vector_t<sample_t> samples;
  for (int i = 0; i < _b; ++i) {
    let x = 10 * float(i) / (_b - 1);
    let y = real(x);
    samples.push_back({x, y});
  }

  auto dag = dag_t{};
  auto ops = ops_t{&dag};
  let Y_samples = ops.mat(_b, 1);
  let X_samples = ops.mat(_b, 1);
  let A = ops.mat(1, 1);
  let B = ops.mat(1, 1);
  let num_samples = ops.mat(1, 1);
  // simple least square (notice that matrix broadcast is used)
  let Diff = Y_samples - (A % X_samples + B);
  let Loss = (Diff.t() * Diff) / num_samples;
  CHECK(Loss.shape == (shape_t{1, 1}));

  // expression 'compilation' (here the interpretor is used)
  let p_dag_eval = dag_eval::create_dag_evaluator(&dag);
  let p_values = p_dag_eval->allocate();
  p_values->as_fmat(num_samples.id)(0, 0) = _b;

  auto X_values = p_values->as_fmat(X_samples.id);
  auto Y_values = p_values->as_fmat(Y_samples.id);
  // set samples values once and for all
  for (let i_s : samples.foreach_rindex()) {
    X_values(i_s, 0) = samples[i_s].x;
    Y_values(i_s, 0) = samples[i_s].y;
  }
  auto &a = p_values->as_fmat(A.id)(0, 0);
  auto &b = p_values->as_fmat(B.id)(0, 0);
  auto &loss = p_values->as_fmat(Loss.id)(0, 0);
  // init a & b
  a = 0;
  b = 0;

  let p_bw_grad_values = p_dag_eval->allocate();
  auto &dloss = p_bw_grad_values->as_fmat(Loss.id)(0, 0);
  auto &da = p_bw_grad_values->as_fmat(A.id)(0, 0);
  auto &db = p_bw_grad_values->as_fmat(B.id)(0, 0);

  for (int i = 0; i < 1000; ++i) {
    printf("%f, %f: %f\n", a, b, loss);
    let eval_res = p_dag_eval->eval(*p_values);
    CHECK(eval_res);
    p_bw_grad_values->zero();
    dloss = 1;
    let bw_grad_eval_res = p_dag_eval->eval_bw_grad(*p_values, *p_bw_grad_values);
    CHECK(bw_grad_eval_res);
    let lr = .01f;
    a -= da * lr;
    b -= db * lr;
  }
  // olé
  CHECK(equals(a, 2, .05));
  CHECK(equals(b, 3, .05));
}

UNITTEST() {
  test_type();
  test_expressions();
  test_cases();
  test_mat_expressions();
  test_least_square_optimisation();
}

}
