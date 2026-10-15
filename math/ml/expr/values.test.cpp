#include <cstdio>

#include "./values.h"
#include "cpp_tools/unittest.h"
namespace mto::math::ml::expr::values {
namespace values = mto::math::ml::expr::values;
}
#include "cpp_tools/defines.h"
namespace mto::math::ml::expr::values {

void test_mat_broadcast() {
  vector_t<float> buf_a, buf_b, buf_c;

  // broadcast a row (1,3) to (2,3)
  let a = create_fmat({{1, 2, 3}}, buf_a);
  let a_bc = a.broadcast({2, 3});
  CHECK(a_bc.shape == (matshape_t{2, 3}));
  CHECK(a_bc.stride == (matshape_t{0, 1}));
  CHECK(to_vecvec(a_bc) == (vecvec_t{{1, 2, 3}, {1, 2, 3}}));

  // broadcast a column (2,1) to (2,3)
  let b = create_fmat({{4}, {5}}, buf_b);
  let b_bc = b.broadcast({2, 3});
  CHECK(b_bc.shape == (matshape_t{2, 3}));
  CHECK(b_bc.stride == (matshape_t{1, 0}));
  CHECK(to_vecvec(b_bc) == (vecvec_t{{4, 4, 4}, {5, 5, 5}}));

  // broadcast (1,1) to (2,3)
  let c = create_fmat({{7}}, buf_c);
  let c_bc = c.broadcast({2, 3});
  CHECK(to_vecvec(c_bc) == (vecvec_t{{7, 7, 7}, {7, 7, 7}}));
}

void test_set_binop() {
  vector_t<float> buf_a, buf_b, buf_dst;

  let a = create_fmat({{1, 2}, {3, 4}}, buf_a);
  let b = create_fmat({{10, 20}, {30, 40}}, buf_b);
  let dst = create_fmat({{0, 0}, {0, 0}}, buf_dst);

  // dst = a + b
  set_binop<false>(dst, a, b, [](float x, float y) { return x + y; });
  CHECK(to_vecvec(dst) == (vecvec_t{{11, 22}, {33, 44}}));

  // dst += a * b
  set_binop<true>(dst, a, b, [](float x, float y) { return x * y; });
  CHECK(to_vecvec(dst) == (vecvec_t{{11 + 10, 22 + 40}, {33 + 90, 44 + 160}}));
}

void test_set() {
  vector_t<float> buf_src, buf_dst;

  let src = create_fmat({{1, 2}, {3, 4}}, buf_src);
  let dst = create_fmat({{0, 0}, {0, 0}}, buf_dst);

  // dst = src * 2
  set<false>(dst, src, [](float x) { return x * 2; });
  CHECK(to_vecvec(dst) == (vecvec_t{{2, 4}, {6, 8}}));

  // dst += src
  set<true>(dst, src, [](float x) { return x; });
  CHECK(to_vecvec(dst) == (vecvec_t{{3, 6}, {9, 12}}));

  vector_t<float> buf2;
  let m = create_fmat({{0, 0}, {0, 0}}, buf2);
  set(m, {{5, 6}, {7, 8}});
  CHECK(to_vecvec(m) == (vecvec_t{{5, 6}, {7, 8}}));
}

void test_set_matmul() {
  vector_t<float> buf_a, buf_b, buf_dst;

  let a = create_fmat({{1, 2, 3}, {4, 5, 6}}, buf_a);      // 2x3
  let b = create_fmat({{7, 8}, {9, 10}, {11, 12}}, buf_b); // 3x2
  let dst = create_fmat({{0, 0}, {0, 0}}, buf_dst);        // 2x2

  // dst = a * b
  set_matmul<false>(dst, a, b);
  CHECK(to_vecvec(dst) == (vecvec_t{{58, 64}, {139, 154}}));

  // dst += a * b
  set_matmul<true>(dst, a, b);
  CHECK(to_vecvec(dst) == (vecvec_t{{116, 128}, {278, 308}}));
}

UNITTEST() {
  test_mat_broadcast();
  test_set_binop();
  test_set();
  test_set_matmul();
}

}
