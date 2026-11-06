#pragma once
#include <cstdio>

#include "no_stl/array/array.h"
#include "no_stl/vector/vector.h"
namespace mto::math::ml::expr::values {
using mto::no_stl::array::array::array_t;
using mto::no_stl::vector::vector::vector_t;
}
#include "cpp_tools/defines.h"
namespace mto::math::ml::expr::values {

/**
 * structs for manipulating data on host side
 */
struct fmat_t {
  float &operator()(int32_t i, int32_t j) {
    return *(p + i * stride[0] + j * stride[1]);
  }

  fmat_t t() const {
    return {p, {size[1], size[0]}, {stride[1], stride[0]}};
  }

  float *p;
  array_t<int32_t, size_t, 2> size;
  array_t<int32_t, size_t, 2> stride;
};

/**
 * math functions.
 */
// member to member operations
template <typename transform_t>
void set_binop(fmat_t dst, fmat_t a, fmat_t b, transform_t const &f) {
  REQUIRES(a.size == b.size);
  REQUIRES(dst.size == a.size);
  for (int32_t i = 0; i < a.size[0]; ++i) {
    for (int32_t j = 0; j < a.size[1]; ++j) {
      dst(i, j) = f(a(i, j), b(i, j));
    }
  }
}

template <typename transform_t>
void acc_binop(fmat_t dst, fmat_t a, fmat_t b, transform_t const &f) {
  REQUIRES(a.size == b.size);
  REQUIRES(dst.size == a.size);
  for (int32_t i = 0; i < a.size[0]; ++i) {
    for (int32_t j = 0; j < a.size[1]; ++j) {
      dst(i, j) += f(a(i, j), b(i, j));
    }
  }
}

template <typename transform_t>
void set(fmat_t dst, fmat_t src, transform_t const &f) {
  REQUIRES(dst.size[0] == src.size[0]);
  REQUIRES(dst.size[1] == src.size[1]);
  for (int32_t i = 0; i < src.size[0]; ++i) {
    for (int32_t j = 0; j < src.size[1]; ++j) {
      dst(i, j) = f(src(i, j));
    }
  }
}

template <typename transform_t>
void acc(fmat_t dst, fmat_t src, transform_t const &f) {
  REQUIRES(dst.size[0] == src.size[0]);
  REQUIRES(dst.size[1] == src.size[1]);
  for (int32_t i = 0; i < src.size[0]; ++i) {
    for (int32_t j = 0; j < src.size[1]; ++j) {
      dst(i, j) += f(src(i, j));
    }
  }
}

// dst = a * b (matrice multiplication)
void set_matmul(fmat_t dst, fmat_t a, fmat_t b);
// dst += a * b (matrice multiplication)
void acc_matmul(fmat_t dst, fmat_t a, fmat_t b);
// dst = a^t
void set_transpose(fmat_t dst, fmat_t a);

/**
 * c++ helpers
 */
void set(fmat_t y, vector_t<vector_t<float>> const &m);

}
