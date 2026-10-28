//[mto.import ./dag]
//[mto.import no_stl/variant/stack_variant.impl:INSTANCIATE_STACK_VARIANT#]
//[mto.import no_stl/math/functions as math]

//[mto-gen.begin]
#include "./dag.h"
#include "no_stl/variant/stack_variant.impl.h"
#include "no_stl/math/functions.h"
namespace mto::math::ml::expr::dag {
namespace dag = mto::math::ml::expr::dag;
namespace math = mto::no_stl::math::functions;
}
#include "cpp_tools/defines.h"
//[mto-gen.end]
//[mto]
namespace mto::math::ml::expr::dag {//[mto.module-begin]

#define fnan (0.f / 0.f)

namespace {

struct eval_t {
  eval_t(dag_t const *const _p_dag) : p_dag(_p_dag) {
    values = vector_t<float, node_id_t>(p_dag->ops.size(), fnan);
  }

  float _eval(fconst_t const &op) const {
    return op.value;
  }

  float _eval(var_t const &op) const {
    return values[op.id];
  }

  float _eval(plus_t const &op) const {
    return values[op.lhs] + values[op.rhs];
  }

  float _eval(neg_t const &op) const {
    return -values[op.sub];
  }

  float _eval(times_t const &op) const {
    return values[op.lhs] * values[op.rhs];
  }

  float _eval(inv_t const &op) const {
    return 1.f / values[op.sub];
  }

  float _eval(cases_t const &op) const {
    let condition = values[op.condition];
    for (let &c : op.cases) {
      if (values[c.condition_value] == condition) {
        return values[c.result_value];
      }
    }
    // TODO: handle errors
    EXIT_NOT_IMPL();
  }

  float eval_relu(float x) const {
    return x < 0 ? 0 : x;
  }

  float eval_log(float x) const {
    return math::log(x);
  }

  float eval_exp(float x) const {
    return math::exp(x);
  }

  float _eval(special_func_t const &op) const {
    let x = values[op.arg];
    switch (op.func) {
    case relu:
      return eval_relu(x);
    case log:
      return eval_log(x);
    case exp:
      return eval_exp(x);
    }
    __builtin_unreachable();
  }

  float eval(any_op_t const &op) const {
    return op.visit([this](let &op) {
      return this->_eval(op);
    });
  }

  void eval(cspan_t<var_value_t> var_values) {
    for (let &var : var_values) {
      values[var.id] = var.value;
    }

    for (let i_op : p_dag->ops.foreach_index()) {
      values[i_op] = eval(p_dag->ops[i_op]);
    }
  }

  dag_t const *const p_dag;
  vector_t<float, node_id_t> values;
};

struct fw_grad_eval_t {
  fw_grad_eval_t(dag_t const *const _p_dag,
                 cspan_t<float, node_id_t> const _values)
      : p_dag(_p_dag), values(_values) {
    fw_grad_values = vector_t<float, node_id_t>(p_dag->ops.size(), fnan);
  }

  float _eval(fconst_t const &op) const {
    return 0;
  }

  float _eval(var_t const &op) const {
    return fw_grad_values[op.id];
  }

  float _eval(plus_t const &op) const {
    return fw_grad_values[op.lhs] + fw_grad_values[op.rhs];
  }

  float _eval(neg_t const &op) const {
    return -fw_grad_values[op.sub];
  }

  float _eval(times_t const &op) const {
    return values[op.lhs] * fw_grad_values[op.rhs] +
           fw_grad_values[op.lhs] * values[op.rhs];
  }

  float _eval(inv_t const &op) const {
    return -fw_grad_values[op.sub] / (values[op.sub] * values[op.sub]);
  }

  float _eval(cases_t const &op) const {
    EXIT_NOT_IMPL();
  }

  float _eval(special_func_t const &op) const {
    EXIT_NOT_IMPL();
  }

  float eval(any_op_t const &op) const {
    return op.visit([this](let &op) {
      return this->_eval(op);
    });
  }

  void eval(cspan_t<var_value_t> var_grads) {
    for (let &var : var_grads) {
      fw_grad_values[var.id] = var.value;
    }

    for (let i_op : p_dag->ops.foreach_index()) {
      fw_grad_values[i_op] = eval(p_dag->ops[i_op]);
    }
  }

  dag_t const *const p_dag;
  cspan_t<float, node_id_t> const values;
  vector_t<float, node_id_t> fw_grad_values;
};

struct bw_grad_eval_t {
  bw_grad_eval_t(dag_t const *const _p_dag,
                 cspan_t<float, node_id_t> const _values)
      : p_dag(_p_dag), values(_values) {
    // ! init to 0 is important in this case
    bw_grad_values = vector_t<float, node_id_t>(p_dag->ops.size(), 0.f);
  }

  void _set_contribs(float grad, fconst_t const &op) {
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
    bw_grad_values[op.rhs] += grad * values[op.lhs];
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

  void eval(cspan_t<var_value_t> var_grads) {
    for (let &var : var_grads) {
      bw_grad_values[var.id] = var.value;
    }

    for (let r_i_op : p_dag->ops.foreach_rindex()) {
      set_contribs(bw_grad_values[r_i_op], p_dag->ops[r_i_op]);
    }
  }

  dag_t const *const p_dag;
  cspan_t<float, node_id_t> const values;
  vector_t<float, node_id_t> bw_grad_values;
};

}

node_id_t dag_t::_const(float x) {
  return push(fconst_t(x));
}

node_id_t dag_t::real() {
  let id = ops.size();
  ops.push_back(var_t{id});
  return id;
}

node_id_t dag_t::plus(plus_t op) {
  return push(op);
}

node_id_t dag_t::neg(neg_t op) {
  return push(op);
}

node_id_t dag_t::times(times_t op) {
  return push(op);
}

node_id_t dag_t::inv(inv_t op) {
  return push(op);
}

node_id_t dag_t::cases(cases_t const &op) {
  return push(op);
}

node_id_t dag_t::special(special_func_t op) {
  return push(op);
}

node_id_t dag_t::push(any_op_t const &op) {
  let id = ops.size();
  ops.push_back(op);
  return id;
}

vector_t<float, node_id_t>
eval(dag_t const &dag, vector_t<var_value_t> const &var_values) {
  auto dag_eval = eval_t{&dag};
  dag_eval.eval(var_values);
  return dag_eval.values;
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
  auto dag_eval = bw_grad_eval_t{&dag, values};
  dag_eval.eval(var_grads);
  return dag_eval.bw_grad_values;
}

}//[mto.module-end]

namespace _ns =
mto::math::ml::expr::dag//[mto.module-namespace]
    ;

// not needed, any_op_t is only used in this cpp.
INSTANCIATE_STACK_VARIANT(
    _ns::fconst_t,
    _ns::var_t,
    _ns::plus_t, _ns::neg_t,
    _ns::times_t,
    _ns::inv_t,
    _ns::cases_t,
    _ns::special_func_t);
