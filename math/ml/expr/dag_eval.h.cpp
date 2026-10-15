#include <cstring>

#include "./dag_eval.h"
#include "./values.h"
#include "no_stl/span/span.h"
#include "no_stl/math/functions.h"
#include "no_stl/byte/byte.h"
#include "no_stl/function/function.h"
#include "no_stl/utility.h"
namespace mto::math::ml::expr::dag_eval {
namespace dag_eval = mto::math::ml::expr::dag_eval;
using mto::math::ml::expr::values::fmat_t;
using mto::no_stl::span::span::span_t;
namespace math = mto::no_stl::math::functions;
using mto::no_stl::byte::byte::byte_t;
using mto::no_stl::function::function::function_t;
using mto::no_stl::utility::is_same_v;
}
#include "cpp_tools/defines.h"
namespace mto::math::ml::expr::dag_eval {

constexpr float fnan = __builtin_nanf("");

using namespace dag;

namespace {

float identity(float x) { return x; }
float neg(float x) { return -x; }
float reluf(float x) { return math::relu(x); }
float logf(float x) { return math::log(x); }
float expf(float x) { return math::exp(x); }
float negf(float x) { return -x; }
float invf(float x) { return 1.f / x; }

float d_reluf(float x, float dx) { return x < 0 ? 0 : dx; }
float d_logf(float x, float dx) { return dx / x; }
float d_expf(float x, float dx) { return math::exp(x) * dx; }
float d_invf(float x, float dx) { return -dx / (x * x); }

float addf(float x, float y) { return x + y; }
float mulf(float x, float y) { return x * y; }

struct value_t {
  byte_t *values;
  node_id_t id;
};

struct dag_values_t {
  offset_t get_offset(node_id_t id) const {
    return p_dag->nodes[id].offset;
  }

  type_t get_type(node_id_t id) const {
    return p_dag->nodes[id].t;
  }

  bool is_real(node_id_t id) const {
    return get_type(id).shape.size() == 0;
  }

  bool is_mat(node_id_t id) const {
    return get_type(id).shape.size() == 2;
  }

  byte_t *get_ptr(value_t val) const {
    let offset = get_offset(val.id);
    return (val.values + size_t(offset));
  }

  float *get_fptr(value_t val) const {
    let offset = get_offset(val.id);
    return (float *)(val.values + size_t(offset));
  }

  float &get(value_t val) const {
    return *get_fptr(val);
  }

  fmat_t get_fmat(value_t val) const {
    let t = get_type(val.id);
    REQUIRES(t.dtype == dtype_t::f32);
    REQUIRES(t.shape.size() == 2);
    float *p = get_fptr(val);
    return {p, {t.shape[0], t.shape[1]}, {t.stride[0], t.stride[1]}};
  }

  // propagates 'f' as inlinable function to allow inlining and
  // vectorization
  template <float (*f)(float), bool accumulate>
  void result(value_t dst, value_t src) const {
    if (is_real(dst.id)) {
      if constexpr (accumulate) {
        get(dst) += f(get(src));
      } else {
        get(dst) = f(get(src));
      }
    } else if (is_mat(dst.id)) {
      set<accumulate>(get_fmat(dst), get_fmat(src), f);
    } else {
      EXIT_NOT_IMPL();
    }
  }

  template <float (*f)(float)>
  void set_result(value_t dst, value_t src) const {
    return result<f, false>(dst, src);
  }

  template <float (*f)(float)>
  void acc_result(value_t dst, value_t src) const {
    return result<f, true>(dst, src);
  }

  template <float (*f)(float, float), bool accumulate>
  void bin_op_result(value_t dst, value_t lhs, value_t rhs) const {
    if (is_real(dst.id)) {
      if constexpr (accumulate) {
        get(dst) += f(get(lhs), get(rhs));
      } else {
        get(dst) = f(get(lhs), get(rhs));
      }
    } else if (is_mat(dst.id)) {
      let dst_mat = get_fmat(dst);
      let lhs_mat = get_fmat(lhs);
      let rhs_mat = get_fmat(rhs);
      if (lhs_mat.shape == rhs_mat.shape) {
        set_binop<accumulate>(dst_mat, lhs_mat, rhs_mat, f);
      } else {
        // TODO: handle broadcast as a 'proxy' matrix like transpose
        // -> it should then be forbidden to have non equal shapes here
        EXIT_NOT_IMPL();
      }
    } else {
      EXIT_NOT_IMPL();
    }
  }

  template <float (*f)(float, float)>
  void set_bin_op_result(value_t dst, value_t lhs, value_t rhs) const {
    return bin_op_result<f, false>(dst, lhs, rhs);
  }

  template <float (*f)(float, float)>
  void acc_bin_op_result(value_t dst, value_t lhs, value_t rhs) const {
    return bin_op_result<f, true>(dst, lhs, rhs);
  }

  void set_matmul(value_t dst, value_t lhs, value_t rhs) const {
    REQUIRES(is_mat(dst.id));
    values::set_matmul<false>(get_fmat(dst), get_fmat(lhs), get_fmat(rhs));
  }

  void acc_matmul(value_t dst, value_t lhs, value_t rhs) const {
    REQUIRES(is_mat(dst.id));
    values::set_matmul<true>(get_fmat(dst), get_fmat(lhs), get_fmat(rhs));
  }

  void set_data(value_t dst, const_t const &data) const {
    let res = data.data.visit([&]<typename _t>(_t const &d) {
      if constexpr (is_same_v<_t, float>) {
        *get_fptr(dst) = d;
        return 0;
      } else if constexpr (is_same_v<_t, const_t::matrix_literal_t>) {
        auto M = get_fmat(dst);
        for (int32_t i = 0; i < M.shape[0]; ++i) {
          for (int32_t j = 0; j < M.shape[1]; ++j) {
            M(i, j) = d[i][j];
          }
        }
        return 0;
      }
    });
    (void)res;
  }

  void set_zero(value_t dst) const {
    let t = get_type(dst.id);
    if (t.shape.size() == 0) {
      *get_fptr(dst) = 0;
    } else if (t.shape.size() == 2) {
      auto M = get_fmat(dst);
      for (int32_t i = 0; i < M.shape[0]; ++i) {
        for (int32_t j = 0; j < M.shape[1]; ++j) {
          M(i, j) = 0;
        }
      }
    } else {
      EXIT_NOT_IMPL();
    }
  }

  dag_t const *const p_dag;
};

struct eval_t {
  value_t val(node_id_t id) const {
    return {values, id};
  }

  template <float (*f)(float)>
  void _set_result(node_id_t dst_id, node_id_t src_id) const {
    return vals.set_result<f>(val(dst_id), val(src_id));
  }

  template <float (*f)(float, float)>
  void _set_bin_op_result(node_id_t dst_id, node_id_t lhs, node_id_t rhs) const {
    return vals.set_bin_op_result<f>(val(dst_id), val(lhs), val(rhs));
  }

  void _set_result(node_id_t dst_id, const_t const &op) const {
    vals.set_data(val(dst_id), op);
  }

  void _set_result(node_id_t dst_id, var_t const &op) const {
    // variables are set by the user before evaluation
  }

  void _set_result(node_id_t dst_id, plus_t const &op) const {
    return _set_bin_op_result<addf>(dst_id, op.lhs, op.rhs);
  }

  void _set_result(node_id_t dst_id, neg_t const &op) const {
    return _set_result<negf>(dst_id, op.sub);
  }

  void _set_result(node_id_t dst_id, times_t const &op) const {
    return _set_bin_op_result<mulf>(dst_id, op.lhs, op.rhs);
  }

  void _set_result(node_id_t dst_id, inv_t const &op) const {
    return _set_result<invf>(dst_id, op.sub);
  }

  void _set_result(node_id_t dst_id, view_t const &op) const {
  }

  void _set_result(node_id_t dst_id, matmul_t const &op) const {
    if (vals.is_mat(dst_id)) {
      vals.set_matmul(val(dst_id), val(op.lhs), val(op.rhs));
    } else {
      // TODO: handle matmul for tensors (as bulks of matrices)
      EXIT_NOT_IMPL();
    }
  }

  void _set_result(node_id_t dst_id, cases_t const &op) const {
    let condition = vals.get(val(op.condition));
    for (let &c : op.cases) {
      if (vals.get(val(c.condition_value)) == condition) {
        return _set_result<identity>(dst_id, c.result_value);
      }
    }
  }

  void _set_result(node_id_t dst_id, special_func_t const &op) const {
    switch (op.func) {
    case relu:
      return _set_result<reluf>(dst_id, op.arg);
    case log:
      return _set_result<logf>(dst_id, op.arg);
    case exp:
      return _set_result<expf>(dst_id, op.arg);
    }
    __builtin_unreachable();
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
  byte_t *const values;
  dag_values_t const vals;
};

struct fw_grad_eval_t {
  value_t val(node_id_t id) const {
    return {values, id};
  }

  value_t fw_grad(node_id_t id) const {
    return {fw_grad_values, id};
  }

  void _set_result(node_id_t dst_id, const_t const &op) {
    vals.set_zero(fw_grad(dst_id));
  }

  void _set_result(node_id_t dst_id, var_t const &op) {
    // variables grads are set by the user before evaluation
  }

  void _set_result(node_id_t dst_id, plus_t const &op) {
    vals.set_bin_op_result<addf>(fw_grad(dst_id), fw_grad(op.lhs), fw_grad(op.rhs));
  }

  void _set_result(node_id_t dst_id, neg_t const &op) {
    vals.set_result<negf>(fw_grad(dst_id), fw_grad(op.sub));
  }

  void _set_result(node_id_t dst_id, times_t const &op) {
    let a = val(op.lhs);
    let da = fw_grad(op.lhs);
    let b = val(op.rhs);
    let db = fw_grad(op.rhs);
    let dy = fw_grad(dst_id);
    // dy = da * b + a * db;
    vals.set_bin_op_result<mulf>(dy, da, b);
    vals.acc_bin_op_result<mulf>(dy, a, db);
  }

  void _set_result(node_id_t dst_id, matmul_t const &op) {
    let a = val(op.lhs);
    let da = fw_grad(op.lhs);
    let b = val(op.rhs);
    let db = fw_grad(op.rhs);
    let dy = fw_grad(dst_id);
    // dy = da * b + a * db;
    vals.set_matmul(dy, da, b);
    vals.acc_matmul(dy, a, db);
  }

  void _set_result(node_id_t dst_id, inv_t const &op) {
    let x = val(op.sub);
    let dx = fw_grad(op.sub);
    // dy = -dx / x;
    vals.set_bin_op_result<d_invf>(fw_grad(dst_id), x, dx);
  }

  void _set_result(node_id_t dst_id, view_t const &op) {
  }

  void _set_result(node_id_t dst_id, cases_t const &op) {
    let condition = vals.get(val(op.condition));
    for (let &c : op.cases) {
      if (vals.get(val(c.condition_value)) == condition) {
        return vals.set_result<identity>(fw_grad(dst_id), fw_grad(c.result_value));
      }
    }
    // TODO: handle errors
    EXIT_NOT_IMPL();
  }

  void _set_result(node_id_t dst_id, special_func_t const &op) {
    let x = val(op.arg);
    let dx = fw_grad(op.arg);
    switch (op.func) {
    case relu:
      return vals.set_bin_op_result<d_reluf>(fw_grad(dst_id), x, dx);
    case log:
      return vals.set_bin_op_result<d_logf>(fw_grad(dst_id), x, dx);
    case exp:
      return vals.set_bin_op_result<d_expf>(fw_grad(dst_id), x, dx);
    }
    __builtin_unreachable();
  }

  void set_result(node_id_t dst_id, any_op_t const &op) {
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
  byte_t *const values;
  byte_t *const fw_grad_values;
  dag_values_t const vals;
};

struct bw_grad_eval_t {
  value_t val(node_id_t id) const {
    return {values, id};
  }

  value_t bw_grad(node_id_t id) const {
    return {bw_grad_values, id};
  }

  void _set_contribs(node_id_t grad_id, const_t const &op) {
  }

  void _set_contribs(node_id_t grad_id, var_t const &op) {
  }

  void _set_contribs(node_id_t grad_id, plus_t const &op) {
    vals.acc_result<identity>(bw_grad(op.lhs), bw_grad(grad_id));
    vals.acc_result<identity>(bw_grad(op.rhs), bw_grad(grad_id));
  }

  void _set_contribs(node_id_t grad_id, neg_t const &op) {
    vals.acc_result<neg>(bw_grad(op.sub), bw_grad(grad_id));
  }

  void _set_contribs(node_id_t grad_id, times_t const &op) {
    let grad = bw_grad(grad_id);
    vals.acc_bin_op_result<mulf>(bw_grad(op.lhs), grad, val(op.rhs));
    vals.acc_bin_op_result<mulf>(bw_grad(op.rhs), val(op.lhs), grad);
  }

  void _set_contribs(node_id_t grad_id, matmul_t const &op) {
    // dA += G @ B.T
    // dB += A.T @ G
    let G = vals.get_fmat(bw_grad(grad_id));
    let A = vals.get_fmat(val(op.lhs));
    let dA = vals.get_fmat(bw_grad(op.lhs));
    let B = vals.get_fmat(val(op.rhs));
    let dB = vals.get_fmat(bw_grad(op.rhs));

    values::set_matmul<true>(dA, G, B.t());
    values::set_matmul<true>(dB, A.t(), G);
  }

  void _set_contribs(node_id_t grad_id, inv_t const &op) {
    let grad = bw_grad(grad_id);
    let x = val(op.sub);
    vals.acc_bin_op_result<d_invf>(bw_grad(op.sub), x, grad);
  }

  void _set_contribs(node_id_t grad_id, view_t const &op) {
  }

  void _set_contribs(node_id_t grad_id, cases_t const &op) {
    let condition = vals.get(val(op.condition));
    for (let &c : op.cases) {
      if (vals.get(val(c.condition_value)) == condition) {
        return vals.acc_result<identity>(bw_grad(c.result_value), bw_grad(grad_id));
      }
    }
    EXIT_NOT_IMPL();
  }

  void _set_contribs(node_id_t grad_id, special_func_t const &op) {
    let x = val(op.arg);
    let dx = bw_grad(grad_id);
    switch (op.func) {
    case relu:
      return vals.acc_bin_op_result<d_reluf>(bw_grad(op.arg), x, dx);
    case log:
      return vals.acc_bin_op_result<d_logf>(bw_grad(op.arg), x, dx);
    case exp:
      return vals.acc_bin_op_result<d_expf>(bw_grad(op.arg), x, dx);
    }
    __builtin_unreachable();
  }

  void set_contribs(node_id_t grad_id, any_op_t const &op) {
    return op.visit([this, grad_id](let &op) {
      return this->_set_contribs(grad_id, op);
    });
  }

  void eval() {
    for (let r_i_op : p_dag->nodes.foreach_rindex()) {
      set_contribs(r_i_op, p_dag->nodes[r_i_op].op);
    }
  }

  dag_t const *const p_dag;
  byte_t *const values;
  byte_t *const bw_grad_values;
  dag_values_t const vals;
};

}

vector_t<float, node_id_t>
eval(dag_t const &dag, vector_t<var_value_t> const &var_values) {
  auto values = vector_t<float, node_id_t>(dag.nodes.size(), fnan);

  auto dag_eval = eval_t{&dag, (byte_t *)values.data(), {&dag}};

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
  auto fw_grad_values = vector_t<float, node_id_t>(dag.nodes.size(), fnan);

  for (let &var : var_grads) {
    fw_grad_values[var.id] = var.value;
  }

  auto dag_eval = fw_grad_eval_t{
      &dag,
      (byte_t *)values.data(),
      (byte_t *)fw_grad_values.data(),
      {&dag},
  };
  dag_eval.eval();
  return fw_grad_values;
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

  auto dag_eval = bw_grad_eval_t{
      &dag,
      (byte_t *)values.data(),
      (byte_t *)bw_grad_values.data(),
      {&dag},
  };
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

    void zero() {
      memset(data.data(), 0, static_cast<size_t>(p_dag->end));
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
      auto dag_eval = eval_t{p_dag, values_buf, {p_dag}};
      dag_eval.eval();
      return empty_t{};
    }

    result_t<> eval_fw_grad(dag_data_t &_values,
                            dag_data_t &_fw_grad_values) {
      auto fw_grad_values_buf = static_cast<dag_data_impl_t &>(_fw_grad_values).data.data();
      auto values_buf = static_cast<dag_data_impl_t &>(_values).data.data();
      auto dag_eval = fw_grad_eval_t{
          p_dag,
          values_buf,
          fw_grad_values_buf,
          {p_dag},
      };
      dag_eval.eval();
      return empty_t{};
    }

    result_t<> eval_bw_grad(dag_data_t &_values,
                            dag_data_t &_bw_grad_values) {
      auto bw_grad_values_buf = static_cast<dag_data_impl_t &>(_bw_grad_values).data.data();
      auto values_buf = static_cast<dag_data_impl_t &>(_values).data.data();
      auto dag_eval = bw_grad_eval_t{
          p_dag,
          values_buf,
          bw_grad_values_buf,
          {p_dag},
      };
      dag_eval.eval();
      return empty_t{};
    }

    result_t<> eval(float *values) {
      auto dag_eval = eval_t{p_dag, (byte_t *)values, {p_dag}};
      dag_eval.eval();
      return empty_t{};
    }

    result_t<> eval(byte_t *values) {
      auto dag_eval = eval_t{p_dag, values, {p_dag}};
      dag_eval.eval();
      return empty_t{};
    }

    result_t<>
    eval_bw_grad(float *bw_grad_values, float const *values) {
      auto dag_eval = bw_grad_eval_t{
          p_dag,
          (byte_t *)values,
          (byte_t *)bw_grad_values,
          {p_dag},
      };
      dag_eval.eval();
      return empty_t{};
    }

    dag_t const *p_dag;
  };

  return new impl_t{p_dag};
}
}
