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
  auto dag = dag_t{};
  auto ops = ops_t{&dag};
  let A = ops.mat(2, 3);
  for (let b_row_major : {true, false}) {
    let B = ops.mat(3, 1, b_row_major);
    let C = A * B;
    let D = C + C;
    let p_dag_eval = dag_eval::create_dag_evaluator(&dag);
    auto p_values = p_dag_eval->allocate();
    auto matA = p_values->as_fmat(A.id);
    auto matB = p_values->as_fmat(B.id);
    set(matA, {{1, 2, 3}, {4, 5, 6}});
    set(matB, {{10}, {20}, {30}});

    let res = p_dag_eval->eval(*p_values);
    auto matC = p_values->as_fmat(C.id);
    CHECK(matC.size[0] == 2);
    CHECK(matC.size[1] == 1);
    CHECK(matC(0, 0) == 1 * 10 + 2 * 20 + 3 * 30);
    CHECK(matC(1, 0) == 4 * 10 + 5 * 20 + 6 * 30);

    // TODO: test fw/bw grad
  }
}

UNITTEST() {
  test_type();

  test_expressions();
  test_cases();

  test_mat_expressions();
}

}
