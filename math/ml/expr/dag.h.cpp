
#include "./dag.h"
#include "no_stl/variant/stack_variant.impl.h"
namespace mto::math::ml::expr::dag {
namespace dag = mto::math::ml::expr::dag;
}
#include "cpp_tools/defines.h"
namespace mto::math::ml::expr::dag {

type_t ftype = type_t{dtype_t::f32, {}};

type_t::type_t(dtype_t d, shape_t s, stride_t st) : dtype(d), shape(s), stride(st) {
}

type_t::type_t(dtype_t d, shape_t s, bool row_major) : dtype(d), shape(s), stride(s.size(), 0) {
  if (row_major) {
    int32_t acc = 1;
    for (let i : shape.foreach_rindex()) {
      stride[i] = acc;
      acc *= shape[i];
    }
  } else {
    // col major
    int32_t acc = 1;
    for (let i : shape.foreach_index()) {
      stride[i] = acc;
      acc *= shape[i];
    }
  }
}

int64_t num_elements(shape_t const &s) {
  int64_t n = 1;
  for (let &k : s) {
    n *= k;
  }
  return n;
}

offset_t size(dtype_t t) {
  switch (t) {
  case dtype_t::f32:
    return offset_t(4);
  }
  __builtin_unreachable();
}

offset_t size(type_t t) {
  return size(t.dtype) * num_elements(t.shape);
}

offset_t end(type_t t) {
  int64_t last = 0;
  for (let i : t.shape.foreach_index()) {
    last += int64_t(t.shape[i] - 1) * t.stride[i];
  }
  return size(t.dtype) * (last + 1);
}

node_id_t push_const(dag_t &dag, float x) {
  auto data = data_t(offset_t(4), byte_t(0));
  auto *p = (float *)data.data();
  *p = x;
  return dag._const(data, ftype);
}

node_id_t dag_t::_const(data_t const &data, type_t t) {
  return push(const_t(data), t);
}

offset_t dag_t::insert_var(type_t t) {
  let pos = end;
  end += size(t);
  return pos;
}

node_id_t dag_t::var(type_t t) {
  let id = nodes.size();
  nodes.push_back({var_t{id}, t, insert_var(t)});
  return id;
}

node_id_t dag_t::plus(plus_t op, type_t t) {
  return push(op, t);
}

node_id_t dag_t::neg(neg_t op, type_t t) {
  return push(op, t);
}

node_id_t dag_t::times(times_t op, type_t t) {
  return push(op, t);
}

node_id_t dag_t::inv(inv_t op, type_t t) {
  return push(op, t);
}

node_id_t dag_t::matmul(matmul_t op, type_t t) {
  return push(op, t);
}

node_id_t dag_t::cases(cases_t const &op, type_t t) {
  return push(op, t);
}

node_id_t dag_t::special(special_func_t op, type_t t) {
  return push(op, t);
}

node_id_t dag_t::push(any_op_t const &op, type_t t) {
  let id = nodes.size();
  nodes.push_back({op, t, insert_var(t)});
  return id;
}

}

namespace _ns =
mto::math::ml::expr::dag
    ;

// not needed, any_op_t is only used in this cpp.
INSTANCIATE_STACK_VARIANT(
    _ns::const_t,
    _ns::var_t,
    _ns::plus_t, _ns::neg_t,
    _ns::times_t,
    _ns::inv_t,
    _ns::matmul_t,
    _ns::cases_t,
    _ns::special_func_t);
