
#include "./values.h"
#include "./dag_eval.h"
#include "no_stl/span/span.h"
#include "no_stl/math/functions.h"
#include "no_stl/byte/byte.h"
namespace mto::math::ml::expr::dag_eval {
namespace values = mto::math::ml::expr::values;
namespace dag_eval = mto::math::ml::expr::dag_eval;
using mto::no_stl::span::span::span_t;
namespace math = mto::no_stl::math::functions;
using mto::no_stl::byte::byte::byte_t;
}
#include "cpp_tools/defines.h"
namespace mto::math::ml::expr::dag_eval {

constexpr float fnan = __builtin_nanf("");

using namespace dag;

namespace {

struct ftensor_t {
  float *data;
  int64_t N;
};

struct eval_t {
  offset_t get_offset(node_id_t id) const {
    return p_dag->nodes[id].offset;
  }

  type_t get_type(node_id_t id) const {
    return p_dag->nodes[id].t;
  }

  ftensor_t get_tensor(node_id_t id) const {
    let t = get_type(id);
    REQUIRES(t.dtype == dtype_t::f32);
    float *p = get_fptr(id);
    return {p, num_elements(t.shape)};
  }

#define REQUIRES_REAL(id) REQUIRES(get_type(id).shape.is_empty());
  float *get_fptr(node_id_t id) const {
    let offset = get_offset(id);
    return (float *)(values + size_t(offset));
  }

  float &get(node_id_t id) const {
    return *get_fptr(id);
  }

  void _set_result(node_id_t dst_id, const_t const &op) const {
    REQUIRES_REAL(dst_id);

    REQUIRES(int(op.data.size()) == 4);
    let *p = (float *)op.data.data();
    get(dst_id) = *p;
  }

  void _set_result(node_id_t dst_id, var_t const &op) const {
  }

  void _set_result(node_id_t dst_id, plus_t const &op) const {
    let lhs = get_tensor(op.lhs);
    let rhs = get_tensor(op.rhs);
    let dst = get_tensor(dst_id);
    for (int32_t i = 0; i < lhs.N; ++i) {
      dst.data[i] = lhs.data[i] + rhs.data[i];
    }
  }

  void _set_result(node_id_t dst_id, neg_t const &op) const {
    REQUIRES_REAL(dst_id);
    get(dst_id) = -get(op.sub);
  }

  void _set_result(node_id_t dst_id, times_t const &op) const {
    REQUIRES_REAL(dst_id);
    get(dst_id) = get(op.lhs) * get(op.rhs);
  }

  void _set_result(node_id_t dst_id, inv_t const &op) const {
    REQUIRES_REAL(dst_id);
    get(dst_id) = 1.f / get(op.sub);
  }

  void _set_result(node_id_t dst_id, matmul_t const &op) const {
    EXIT_NOT_IMPL();
  }

  void _set_result(node_id_t dst_id, cases_t const &op) const {
    REQUIRES_REAL(dst_id);
    let condition = get(op.condition);
    for (let &c : op.cases) {
      if (get(c.condition_value) == condition) {
        get(dst_id) = get(c.result_value);
        return;
      }
    }
    // TODO: handle errors
    EXIT_NOT_IMPL();
  }

  void _set_result(node_id_t dst_id, special_func_t const &op) const {
    REQUIRES_REAL(dst_id);
    let x = get(op.arg);
    let y = [&]() {
      switch (op.func) {
      case relu:
        return x < 0 ? 0 : x;
      case log:
        return math::log(x);
      case exp:
        return math::exp(x);
      }
      __builtin_unreachable();
    }();
    get(dst_id) = y;
  }

  void set_result(node_id_t dst_id, any_op_t const &op) const {
    op.visit([this, dst_id](let &op) {
      this->_set_result(dst_id, op);
    });
  }

  void eval() {
    for (let i_op : p_dag->nodes.foreach_index()) {
      set_result(i_op, p_dag->nodes[i_op].op);
    }
  }

  dag_t const *const p_dag;
  byte_t *values;
};

struct fw_grad_eval_t {
  fw_grad_eval_t(dag_t const *const _p_dag,
                 cspan_t<float, node_id_t> const _values)
      : p_dag(_p_dag), values(_values) {
    fw_grad_values = vector_t<float, node_id_t>(p_dag->nodes.size(), fnan);
  }

  void _set_result(node_id_t dst_id, const_t const &op) {
    fw_grad_values[dst_id] = 0;
  }

  void _set_result(node_id_t dst_id, var_t const &op) {
    fw_grad_values[dst_id] = fw_grad_values[op.id];
  }

  void _set_result(node_id_t dst_id, plus_t const &op) {
    fw_grad_values[dst_id] = fw_grad_values[op.lhs] + fw_grad_values[op.rhs];
  }

  void _set_result(node_id_t dst_id, neg_t const &op) {
    fw_grad_values[dst_id] = -fw_grad_values[op.sub];
  }

  void _set_result(node_id_t dst_id, times_t const &op) {
    let a = values[op.lhs];
    let da = fw_grad_values[op.lhs];
    let b = values[op.rhs];
    let db = fw_grad_values[op.rhs];
    fw_grad_values[dst_id] = da * b + a * db;
  }

  void _set_result(node_id_t dst_id, matmul_t const &op) {
    EXIT_NOT_IMPL();
  }

  void _set_result(node_id_t dst_id, inv_t const &op) {
    fw_grad_values[dst_id] =
        -fw_grad_values[op.sub] / (values[op.sub] * values[op.sub]);
  }

  void _set_result(node_id_t dst_id, cases_t const &op) {
    let condition = values[op.condition];
    for (let &c : op.cases) {
      if (values[c.condition_value] == condition) {
        fw_grad_values[dst_id] = fw_grad_values[c.result_value];
        return;
      }
    }
    // TODO: handle errors
    EXIT_NOT_IMPL();
  }

  void _set_result(node_id_t dst_id, special_func_t const &op) {
    let x = values[op.arg];
    let dx = fw_grad_values[op.arg];
    let y = [&]() {
      switch (op.func) {
      case relu:
        return x < 0 ? 0 : dx;
      case log:
        return (1.f / x) * dx;
      case exp:
        return math::exp(x) * dx;
      }
      __builtin_unreachable();
    }();
    fw_grad_values[dst_id] = y;
  }

  void set_result(node_id_t dst_id, any_op_t const &op) {
    op.visit([this, dst_id](let &op) {
      this->_set_result(dst_id, op);
    });
  }

  void eval(cspan_t<var_value_t> var_grads) {
    for (let &var : var_grads) {
      fw_grad_values[var.id] = var.value;
    }

    for (let i_op : p_dag->nodes.foreach_index()) {
      set_result(i_op, p_dag->nodes[i_op].op);
    }
  }

  dag_t const *const p_dag;
  cspan_t<float, node_id_t> const values;
  vector_t<float, node_id_t> fw_grad_values;
};

struct bw_grad_eval_t {
  void _set_contribs(float grad, const_t const &op) {
  }

  void _set_contribs(float grad, var_t const &op) {
  }

  void _set_contribs(float grad, plus_t const &op) {
    bw_grad_values[op.lhs] += grad;
    bw_grad_values[op.rhs] += grad;
  }

  void _set_contribs(float grad, neg_t const &op) {
    bw_grad_values[op.sub] -= grad;
  }

  void _set_contribs(float grad, times_t const &op) {
    bw_grad_values[op.lhs] += grad * values[op.rhs];
    bw_grad_values[op.rhs] += values[op.lhs] * grad;
  }

  void _set_contribs(float grad, matmul_t const &op) {
    EXIT_NOT_IMPL();
  }

  void _set_contribs(float grad, inv_t const &op) {
    bw_grad_values[op.sub] -= grad / (values[op.sub] * values[op.sub]);
  }

  void _set_contribs(float grad, cases_t const &op) {
    let condition = values[op.condition];
    bool is_valid_switch = false;
    for (let &c : op.cases) {
      if (values[c.condition_value] == condition) {
        bw_grad_values[c.result_value] += grad;
        is_valid_switch = true;
        break;
      }
    }
    // TODO: handle errors
    if (!is_valid_switch) {
      EXIT_NOT_IMPL();
    }
  }

  void set_contrib_relu(float grad, node_id_t sub) {
    if (values[sub] > 0) {
      bw_grad_values[sub] += grad;
    }
  }

  void set_contrib_log(float grad, node_id_t sub) {
    bw_grad_values[sub] += grad / values[sub];
  }

  void set_contrib_exp(float grad, node_id_t sub) {
    bw_grad_values[sub] += grad * math::exp(values[sub]);
  }

  void _set_contribs(float grad, special_func_t const &op) {
    let sub = op.arg;
    switch (op.func) {
    case relu:
      return set_contrib_relu(grad, sub);
    case log:
      return set_contrib_log(grad, sub);
    case exp:
      return set_contrib_exp(grad, sub);
    }
    __builtin_unreachable();
  }

  void set_contribs(float grad, any_op_t const &op) {
    return op.visit([this, grad](let &op) {
      return this->_set_contribs(grad, op);
    });
  }

  void eval() {
    for (let r_i_op : p_dag->nodes.foreach_rindex()) {
      set_contribs(bw_grad_values[r_i_op], p_dag->nodes[r_i_op].op);
    }
  }

  dag_t const *const p_dag;
  cspan_t<float, node_id_t> const values;
  span_t<float, node_id_t> bw_grad_values;
};

}

vector_t<float, node_id_t>
eval(dag_t const &dag, vector_t<var_value_t> const &var_values) {
  auto values = vector_t<float, node_id_t>(dag.nodes.size(), fnan);

  auto dag_eval = eval_t{&dag, (byte_t *)values.data()};

  for (let &var : var_values) {
    values[var.id] = var.value;
  }

  dag_eval.eval();
  return values;
}

vector_t<float, node_id_t>
eval_fw_grad(dag_t const &dag,
             cspan_t<float, node_id_t> values,
             vector_t<var_value_t> const &var_grads) {
  auto dag_eval = fw_grad_eval_t{&dag, values};
  dag_eval.eval(var_grads);
  return dag_eval.fw_grad_values;
}

vector_t<float, node_id_t>
eval_bw_grad(dag_t const &dag,
             cspan_t<float, node_id_t> values,
             vector_t<var_value_t> const &var_grads) {
  // ! init to 0 is important in this case
  auto bw_grad_values = vector_t<float, node_id_t>(dag.nodes.size(), 0.f);
  for (let &var : var_grads) {
    bw_grad_values[var.id] = var.value;
  }

  auto dag_eval = bw_grad_eval_t{&dag, values, bw_grad_values};
  dag_eval.eval();
  return bw_grad_values;
}

unique_ptr_t<evaluator_t>
create_dag_evaluator(dag_t const *p_dag) {
  // this implemention simply uses the stride that is indicated in the dag.
  struct dag_data_impl_t : dag_data_t {
    dag_data_impl_t(dag_t const *_p_dag)
        : p_dag(_p_dag),
          data(data_t{p_dag->end, byte_t(0)}) {
    }

    float *as_float(node_id_t id) {
      REQUIRES(p_dag->nodes[id].t.dtype == dtype_t::f32);
      return (float *)(data.data() + size_t(p_dag->nodes[id].offset));
    }

    fmat_t as_fmat(node_id_t id) {
      let &node = p_dag->nodes[id];
      REQUIRES(node.t.dtype == dtype_t::f32);
      REQUIRES(node.t.shape.size() == 2);
      auto *p = (float *)(data.data() + size_t(node.offset));
      return fmat_t{
          p,
          {node.t.shape[0], node.t.shape[1]},
          {node.t.stride[0], node.t.stride[1]},
      };
    }

    dag_t const *p_dag;
    data_t data;
  };

  struct impl_t : evaluator_t {
    impl_t(dag_t const *_p_dag) : p_dag(_p_dag) {
    }

    unique_ptr_t<dag_data_t> allocate() {
      return new dag_data_impl_t{p_dag};
    }

    result_t<> eval(dag_data_t &_values) {
      auto values_buf = static_cast<dag_data_impl_t &>(_values).data.data();
      auto dag_eval = eval_t{p_dag, values_buf};
      dag_eval.eval();
      return empty_t{};
    }

    result_t<> eval_bw_grad(dag_data_t &_bw_grad_values,
                            dag_data_t &_values) {
      auto bw_grad_values_buf = (float *)static_cast<dag_data_impl_t &>(_bw_grad_values).data.data();
      auto values_buf = (float *)static_cast<dag_data_impl_t &>(_values).data.data();
      let n = p_dag->nodes.size();
      auto dag_eval = bw_grad_eval_t{p_dag, {values_buf, n}, {bw_grad_values_buf, n}};
      dag_eval.eval();
      return empty_t{};
    }

    result_t<> eval(float *values) {
      auto dag_eval = eval_t{p_dag, (byte_t *)values};
      dag_eval.eval();
      return empty_t{};
    }

    result_t<> eval(byte_t *values) {
      auto dag_eval = eval_t{p_dag, values};
      dag_eval.eval();
      return empty_t{};
    }

    result_t<>
    eval_bw_grad(float *bw_grad_values, float const *values) {
      let n = p_dag->nodes.size();
      auto dag_eval = bw_grad_eval_t{p_dag, {values, n}, {bw_grad_values, n}};
      dag_eval.eval();
      return empty_t{};
    }

    dag_t const *p_dag;
  };

  return new impl_t{p_dag};
}
}
