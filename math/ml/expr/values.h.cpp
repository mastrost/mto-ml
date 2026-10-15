
#include "./values.h"
namespace mto::math::ml::expr::values {
namespace values = mto::math::ml::expr::values;
}
#include "cpp_tools/defines.h"
namespace mto::math::ml::expr::values {

namespace {

optional_t<int32_t> get_broadcast_dim(int32_t a, int32_t b) {
  if (a == b) {
    return a;
  } else if (a == 1) {
    return b;
  } else if (b == 1) {
    return a;
  } else {
    return {};
  }
}

}

matshape_t
get_broadcast_stride(matshape_t src_shape, matshape_t src_stride) {
  // Note: with a convention that any matrix uses a stride of 0
  // for dimensions of size 1, there would be non change to do
  // for broadcast. As this convention is not ensured, we force
  // the stride to 0 here.
  auto bc_stride = src_stride;
  bc_stride[0] = src_shape[0] == 1 ? 0 : src_stride[0];
  bc_stride[1] = src_shape[1] == 1 ? 0 : src_stride[1];
  return bc_stride;
}

optional_t<matshape_t>
get_broadcast_shape(matshape_t a_shape, matshape_t b_shape) {
  let opt_m = get_broadcast_dim(a_shape[0], b_shape[0]);
  let opt_n = get_broadcast_dim(a_shape[1], b_shape[1]);
  if (opt_m && opt_n) {
    return matshape_t{*opt_m, *opt_n};
  } else {
    return {};
  }
}

fmat_t fmat_t::t() const {
  return {p, {shape[1], shape[0]}, {stride[1], stride[0]}};
}

fmat_t fmat_t::broadcast(shape_t bc_shape) const {
  REQUIRES(shape[0] == 1 || shape[0] == bc_shape[0]);
  REQUIRES(shape[1] == 1 || shape[1] == bc_shape[1]);
  auto bc_stride = get_broadcast_stride(shape, stride);
  return {p, bc_shape, bc_stride};
}

/**
 * math functions.
 */

template <bool accumulate>
void set_matmul(fmat_t dst, fmat_t a, fmat_t b) {
  REQUIRES(a.shape[1] == b.shape[0]);
  REQUIRES(dst.shape[0] == a.shape[0]);
  REQUIRES(dst.shape[1] == b.shape[1]);
  for (int32_t i = 0; i < a.shape[0]; ++i) {
    for (int32_t j = 0; j < b.shape[1]; ++j) {
      float s = 0.f;
      for (int32_t k = 0; k < a.shape[1]; ++k) {
        s += a(i, k) * b(k, j);
      }
      if constexpr (accumulate) {
        dst(i, j) += s;
      } else {
        dst(i, j) = s;
      }
    }
  }
}

template 
void set_matmul<true>(fmat_t dst, fmat_t a, fmat_t b);

template 
void set_matmul<false>(fmat_t dst, fmat_t a, fmat_t b);

void set_transpose(fmat_t dst, fmat_t a) {
  REQUIRES(dst.shape[0] == a.shape[1]);
  REQUIRES(dst.shape[1] == a.shape[0]);
  for (int32_t i = 0; i < a.shape[0]; ++i) {
    for (int32_t j = 0; j < a.shape[1]; ++j) {
      dst(j, i) = a(i, j);
    }
  }
}

/**
 * c++ helpers
 */

void set(fmat_t y, vecvec_t const &m) {
  REQUIRES(int32_t(m.size()) == y.shape[0]);
  for (let i : m.foreach_index()) {
    let &r = m[i];
    REQUIRES(int32_t(r.size()) == y.shape[1]);
    for (let j : r.foreach_index()) {
      y(i, j) = r[j];
    }
  }
}

vecvec_t to_vecvec(fmat_t a) {
  vecvec_t vecvec;
  for (int32_t i = 0; i < a.shape[0]; ++i) {
    vector_t<float> row;
    for (int32_t j = 0; j < a.shape[1]; ++j) {
      row.push_back(a(i, j));
    }
    vecvec.push_back(row);
  }
  return vecvec;
}

fmat_t create_fmat(vecvec_t const &data, vector_t<float> &out_buf) {
  REQUIRES(data.size() > 0);
  let m = int32_t(data.size());
  let n = int32_t(data[0].size());
  out_buf = vector_t<float>();
  for (int32_t i = 0; i < m; ++i) {
    REQUIRES(int32_t(data[i].size()) == n);
    for (int32_t j = 0; j < n; ++j) {
      out_buf.push_back(data[i][j]);
    }
  }
  return fmat_t{out_buf.data(), {m, n}, {n, 1}};
}

}
