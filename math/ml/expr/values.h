#pragma once
#include <cstdio>

#include "no_stl/array/array.h"
#include "no_stl/vector/vector.h"
#include "no_stl/optional/optional.h"
namespace mto::math::ml::expr::values {
using mto::no_stl::array::array::array_t;
using mto::no_stl::vector::vector::vector_t;
using mto::no_stl::optional::optional::optional_t;
}
#include "cpp_tools/defines.h"
namespace mto::math::ml::expr::values {

/**
 * structs for manipulating data on host side
 */
typedef array_t<int32_t, size_t, 2> matshape_t;

struct fmat_t {
  typedef matshape_t shape_t;

  float &operator()(int32_t i, int32_t j) {
    REQUIRES((i >= 0 && i < shape[0]) && (j >= 0 && j < shape[1]));
    return *(p + i * stride[0] + j * stride[1]);
  }

  fmat_t t() const;

  fmat_t broadcast(shape_t bc_shape) const;

  float *p;
  shape_t shape;
  shape_t stride;
};

optional_t<matshape_t>
get_broadcast_shape(matshape_t a_shape, matshape_t b_shape);

// a broadcast is just a stride of 0 in the broadcast dimensions.
// Note that a stride of 0 would also be compatible with non broadcast
// dimensions with shape 1.
matshape_t
get_broadcast_stride(matshape_t src_shape, matshape_t src_stride);

/**
 * math functions.
 */

// member to member operations
template <bool accumulate, typename transform_t>
void set_binop(fmat_t dst, fmat_t a, fmat_t b, transform_t const &f) {
  REQUIRES(a.shape == b.shape);
  REQUIRES(dst.shape == a.shape);
  for (int32_t i = 0; i < a.shape[0]; ++i) {
    for (int32_t j = 0; j < a.shape[1]; ++j) {
      if constexpr (accumulate) {
        dst(i, j) += f(a(i, j), b(i, j));
      } else {
        dst(i, j) = f(a(i, j), b(i, j));
      }
    }
  }
}

template <bool accumulate, typename transform_t>
void set(fmat_t dst, fmat_t src, transform_t const &f) {
  REQUIRES(dst.shape[0] == src.shape[0]);
  REQUIRES(dst.shape[1] == src.shape[1]);
  for (int32_t i = 0; i < src.shape[0]; ++i) {
    for (int32_t j = 0; j < src.shape[1]; ++j) {
      if constexpr (accumulate) {
        dst(i, j) += f(src(i, j));
      } else {
        dst(i, j) = f(src(i, j));
      }
    }
  }
}

// dst [=|+=] a * b (matrice multiplication)
template <bool accumulate>
void set_matmul(fmat_t dst, fmat_t a, fmat_t b);
// dst = a^t
void set_transpose(fmat_t dst, fmat_t a);

/**
 * c++ helpers
 */
typedef vector_t<vector_t<float>> vecvec_t;

void set(fmat_t y, vecvec_t const &m);
vecvec_t to_vecvec(fmat_t a);

fmat_t create_fmat(vecvec_t const &data, vector_t<float> &out_buf);

}
