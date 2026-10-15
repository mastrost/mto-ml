#pragma once

#include "no_stl/array/array.h"
namespace mto::math::ml::expr::values {
using mto::no_stl::array::array::array_t;
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

  float *p;
  array_t<int32_t, size_t, 2> size;
  array_t<int32_t, size_t, 2> stride;
};

}
