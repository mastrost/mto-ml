
#include "./values.h"
namespace mto::math::ml::expr::values {
namespace values = mto::math::ml::expr::values;
}
#include "cpp_tools/defines.h"
namespace mto::math::ml::expr::values {

/**
 * math functions.
 */

void set_matmul(fmat_t dst, fmat_t a, fmat_t b) {
  REQUIRES(a.size[1] == b.size[0]);
  REQUIRES(dst.size[0] == a.size[0]);
  REQUIRES(dst.size[1] == b.size[1]);
  for (int32_t i = 0; i < a.size[0]; ++i) {
    for (int32_t j = 0; j < b.size[1]; ++j) {
      float s = 0.f;
      for (int32_t k = 0; k < a.size[1]; ++k) {
        s += a(i, k) * b(k, j);
      }
      dst(i, j) = s;
    }
  }
}

void acc_matmul(fmat_t dst, fmat_t a, fmat_t b) {
  REQUIRES(a.size[1] == b.size[0]);
  REQUIRES(dst.size[0] == a.size[0]);
  REQUIRES(dst.size[1] == b.size[1]);
  for (int32_t i = 0; i < a.size[0]; ++i) {
    for (int32_t j = 0; j < b.size[1]; ++j) {
      float s = 0.f;
      for (int32_t k = 0; k < a.size[1]; ++k) {
        s += a(i, k) * b(k, j);
      }
      dst(i, j) += s;
    }
  }
}

void set_transpose(fmat_t dst, fmat_t a) {
  REQUIRES(dst.size[0] == a.size[1]);
  REQUIRES(dst.size[1] == a.size[0]);
  for (int32_t i = 0; i < a.size[0]; ++i) {
    for (int32_t j = 0; j < a.size[1]; ++j) {
      dst(j, i) = a(i, j);
    }
  }
}

/**
 * c++ helpers
 */

void set(fmat_t y, vector_t<vector_t<float>> const &m) {
  REQUIRES(int32_t(m.size()) == y.size[0]);
  for (let i : m.foreach_index()) {
    let &r = m[i];
    REQUIRES(int32_t(r.size()) == y.size[1]);
    for (let j : r.foreach_index()) {
      y(i, j) = r[j];
    }
  }
}

}
