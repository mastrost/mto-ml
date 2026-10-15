#pragma once

#include "no_stl/vector/vector.h"
#include "no_stl/variant/stack_variant.h"
#include "cpp_tools/strong_int.h"
#include "no_stl/byte/byte.h"
namespace mto::math::ml::expr::dag {
using mto::no_stl::vector::vector::vector_t;
using mto::no_stl::variant::stack_variant::stack_variant_t;
using mto::no_stl::byte::byte::byte_t;
}
#include "cpp_tools/defines.h"
namespace mto::math::ml::expr::dag {

STRONG_TYPED_INT(int32_t, node_id_t);
STRONG_TYPED_INT(int32_t, offset_t);

enum class dtype_t { f32,
};

typedef vector_t<int32_t> shape_t;
typedef vector_t<int32_t> stride_t;

struct type_t {
  dtype_t dtype;
  shape_t shape;
  stride_t stride;

  type_t(dtype_t d, shape_t s, stride_t st);
  type_t(dtype_t d, shape_t s, bool row_major = true);
};

offset_t size(dtype_t);
// compacted size
offset_t size(type_t t);
// first byte after the last element (may be different from size depending on stride)
offset_t end(type_t t);
int64_t num_elements(shape_t const &s);

extern type_t ftype;

typedef vector_t<byte_t, offset_t> data_t;

// to incorporate literals into the dag expression
struct const_t {
  // TODO: use a generic tensor literal type
  typedef vector_t<vector_t<float>> matrix_literal_t;
  stack_variant_t<float, matrix_literal_t> data;
};

struct var_t {
  node_id_t id;
};

struct plus_t {
  node_id_t lhs;
  node_id_t rhs;
};

struct neg_t {
  node_id_t sub;
};

struct times_t {
  node_id_t lhs;
  node_id_t rhs;
};

struct inv_t {
  node_id_t sub;
};

// logical operation, no data created.
// used for transposition, broadcasting, etc.
// (i.e. any type casting (on compatible types))
struct view_t {
  node_id_t arg;
};

struct matmul_t {
  node_id_t lhs;
  node_id_t rhs;
};

struct cases_t {
  struct case_t {
    node_id_t condition_value;
    node_id_t result_value;
  };

  node_id_t condition;
  vector_t<case_t> cases;
};

enum func_t { relu,
              log,
              exp };

struct special_func_t {
  func_t func;
  node_id_t arg;
};

typedef stack_variant_t<const_t, var_t,
                        plus_t, neg_t, times_t, inv_t, view_t, matmul_t,
                        cases_t, special_func_t>
    any_op_t;

struct node_t {
  any_op_t op;
  type_t t;
  offset_t offset;
};

struct dag_t;

/**
 * expression dag
 */
struct dag_t {
  node_id_t _const(float c, type_t t);
  node_id_t _const(vector_t<vector_t<float>> const &mat, type_t t);
  node_id_t var(type_t t);
  node_id_t plus(plus_t op, type_t t);
  node_id_t neg(neg_t op, type_t t);
  node_id_t times(times_t op, type_t t);
  node_id_t inv(inv_t op, type_t t);
  node_id_t view(view_t op, type_t t);
  node_id_t matmul(matmul_t op, type_t t);
  node_id_t cases(cases_t const &op, type_t);
  node_id_t special(special_func_t op, type_t t);

  node_id_t push(any_op_t const &op, type_t t);
  offset_t insert_var(type_t);

  vector_t<node_t, node_id_t> nodes;
  offset_t end = offset_t{0};
};

node_id_t push_const(dag_t &dag, float x);

}
