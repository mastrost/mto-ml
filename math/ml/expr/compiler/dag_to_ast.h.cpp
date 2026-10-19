//[mto.import ./dag_to_ast]

//[mto.import no_stl/string/string]
//[mto.import no_stl/string/string.manip:to_string]
//[mto.import no_stl/optional/optional:optional_t]
//[mto.import no_stl/utility]

//[mto-gen.begin]
#include "./dag_to_ast.h"
#include "no_stl/string/string.h"
#include "no_stl/string/string.manip.h"
#include "no_stl/optional/optional.h"
#include "no_stl/utility.h"
namespace mto::math::ml::expr::compiler::dag_to_ast {
namespace dag_to_ast = mto::math::ml::expr::compiler::dag_to_ast;
namespace string = mto::no_stl::string::string;
using mto::no_stl::string::string::to_string;
using mto::no_stl::optional::optional::optional_t;
namespace utility = mto::no_stl::utility;
}
#include "cpp_tools/defines.h"
//[mto-gen.end]
//[mto]
namespace mto::math::ml::expr::compiler::dag_to_ast {//[mto.module-begin]

using namespace string::literal;
using namespace ast;

namespace {

expression_t
value_ast(dag::node_id_t node_id) {
  return "values[" + to_string(int(node_id)) + "]";
}

expression_t
bw_grad_value_ast(dag::node_id_t node_id) {
  return "bw_grad_values[" + to_string(int(node_id)) + "]";
}

expression_t
to_ast(float c) {
  return "(float)(" + to_string(c) + ")";
}

optional_t<expression_t>
_to_ast(dag::fconst_t const &op) {
  return expression_t{to_string(op.value)};
}

optional_t<expression_t>
_to_ast(dag::var_t const &op) {
  return {};
}

optional_t<expression_t>
_to_ast(dag::plus_t const &op) {
  return expression_t{
      bin_op_t{"+", value_ast(op.lhs), value_ast(op.rhs)}};
}

optional_t<expression_t>
_to_ast(dag::neg_t const &op) {
  return expression_t{
      unary_op_t{"-", value_ast(op.sub)}};
}

optional_t<expression_t>
_to_ast(dag::times_t const &op) {
  return expression_t{
      bin_op_t{"*", value_ast(op.lhs), value_ast(op.rhs)}};
}

optional_t<expression_t>
_to_ast(dag::inv_t const &op) {
  return expression_t{
      bin_op_t{"/", to_ast(1.f), value_ast(op.sub)}};
}

string_t
to_c_function(dag::func_t f) {
  switch (f) {
  case dag::relu:
    return "relu";
  case dag::log:
    return "log";
  case dag::exp:
    return "exp";
  }
  __builtin_unreachable();
}

optional_t<expression_t>
_to_ast(dag::special_func_t const &op) {
  return expression_t{call_t{to_c_function(op.func), {value_ast(op.arg)}}};
}

statement_t
_to_ast(dag::node_id_t dst, dag::cases_t const &op) {
  auto _if = if_t{};
  for (let &c : op.cases) {
    let cond = bin_op_t{"==", value_ast(op.condition), value_ast(c.condition_value)};
    let expr = expression_t{bin_op_t{"=", value_ast(dst), value_ast(c.result_value)}};
    let stmt = statement_t{expr};
    _if.push_back(if_case_t{cond, {stmt}});
  }
  return _if;
}

optional_t<statement_t>
to_ast(dag::node_id_t dst, dag::any_op_t const &op) {
  return op.visit([=]<typename _t>(_t const &op) -> optional_t<statement_t> {
    if constexpr (utility::is_same_v<_t, dag::cases_t>) {
      return _to_ast(dst, op);
    } else {
      let opt_rhs = _to_ast(op);
      if (opt_rhs) {
        let expr = expression_t{bin_op_t{"=", value_ast(dst), *opt_rhs}};
        return statement_t{expr};
      } else {
        return {};
      }
    }
  });
}

struct bw_grad_src_t {
  void _push_contribs_stmts(dag::fconst_t const &op) {
  }

  void _push_contribs_stmts(dag::var_t const &op) {
  }

  void _push_contribs_stmts(dag::plus_t const &op) {
    p_stmts->push_back(bw_grad_assign(op.lhs, grad_value()));
    p_stmts->push_back(bw_grad_assign(op.rhs, grad_value()));
  }

  void _push_contribs_stmts(dag::neg_t const &op) {
    p_stmts->push_back(bw_grad_assign(op.sub,
                                      bin_op_t{"*", to_ast(-1.f), grad_value()}));
  }

  void _push_contribs_stmts(dag::times_t const &op) {
    p_stmts->push_back(bw_grad_assign(op.lhs,
                                      bin_op_t{"*", grad_value(),
                                               value_ast(op.rhs)}));
    p_stmts->push_back(bw_grad_assign(op.rhs,
                                      bin_op_t{"*", grad_value(),
                                               value_ast(op.lhs)}));
  }

  void _push_contribs_stmts(dag::inv_t const &op) {
    let d = bin_op_t{"/", grad_value(), bin_op_t{"*", value_ast(op.sub), value_ast(op.sub)}};
    p_stmts->push_back(bw_grad_assign(op.sub,
                                      bin_op_t{"*", to_ast(-1.f), d}));
  }

  void _push_contribs_stmts(dag::cases_t const &op) {
    auto _if = if_t{};
    for (let &c : op.cases) {
      let cond = bin_op_t{"==", value_ast(op.condition), value_ast(c.condition_value)};
      let expr = bw_grad_assign(c.result_value, grad_value());
      let stmt = statement_t{expr};
      _if.push_back(if_case_t{cond, {stmt}});
    }
    p_stmts->push_back(_if);
  }

  void _push_contribs_stmts_relu(dag::node_id_t sub) {
    auto _if = if_t{
        {
            bin_op_t{">", value_ast(sub), "0"_s},
            {bw_grad_assign(sub, grad_value())},
        },
    };
    p_stmts->push_back(_if);
  }

  void _push_contribs_stmts_log(dag::node_id_t sub) {
    let stmt = bw_grad_assign(
        sub,
        bin_op_t{"/", grad_value(), value_ast(sub)});
    p_stmts->push_back(stmt);
  }

  void _push_contribs_stmts_exp(dag::node_id_t sub) {
    let stmt = bw_grad_assign(
        sub,
        bin_op_t{"*", grad_value(), call_t{"exp", {value_ast(sub)}}});
    p_stmts->push_back(stmt);
  }

  void _push_contribs_stmts(dag::special_func_t const &op) {
    let sub = op.arg;
    switch (op.func) {
    case dag::relu:
      return _push_contribs_stmts_relu(sub);
    case dag::log:
      return _push_contribs_stmts_log(sub);
    case dag::exp:
      return _push_contribs_stmts_exp(sub);
    }
    __builtin_unreachable();
  }

  void push_contribs_stmts(dag::any_op_t const &op) {
    return op.visit([this](let &op) {
      return _push_contribs_stmts(op);
    });
  }

  expression_t bw_grad_assign(dag::node_id_t dst, expression_t const &value) {
    return expression_t{bin_op_t{"+=", bw_grad_value_ast(dst), value}};
  }

  expression_t grad_value() {
    return bw_grad_value_ast(grad_src);
  }

  statements_t *p_stmts;
  dag::node_id_t grad_src;
};

}

function_def_t
to_eval_init_c_source(dag::dag_t const &dag, string_t const &func_name) {
  let decl = function_prototype_t{
      func_name,
      "int",
      {
          {"float *", "values"},
          {"int32_t const*", "var_ids"},
          {"float const*", "var_values"},
          {"int32_t", "num_vars"},
      },
  };
  auto body = statements_t{};
  let push = [&](statement_t const &stmt) {
    body.push_back(stmt);
  };

  push(var_decl_t{"int", "i"});
  push(expression_t{bin_op_t{"=", "i"_s, "0"_s}});
  push(while_t{bin_op_t{"<", "i"_s, "num_vars"_s},
               {
                   expression_t{bin_op_t{"=", "values[var_ids[i]]"_s, "var_values[i]"_s}},
                   expression_t{bin_op_t{"=", "i"_s, "i+1"_s}},
               }});
  push(return_t{"0"_s});

  return {decl, body};
}

function_def_t
to_eval_c_source(dag::dag_t const &dag, string_t const &func_name) {
  let decl = function_prototype_t{
      func_name,
      "int",
      {
          {"float * restrict", "values"},
          {"int32_t", "num_values"},
      },
  };
  auto body = statements_t{};

  for (let i_op : dag.ops.foreach_index()) {
    let opt_stmt = to_ast(i_op, dag.ops[i_op]);
    if (opt_stmt) {
      body.push_back(*opt_stmt);
    }
  }
  body.push_back(return_t{"0"_s});
  return {decl, body};
}

ast::function_def_t
to_bw_grad_eval_c_source(dag::dag_t const &dag, string_t const &func_name) {
  let decl = function_prototype_t{
      func_name,
      "int",
      {
          {"float *restrict", "bw_grad_values"},
          {"float const* restrict", "values"},
          {"int32_t", "num_values"},
      },
  };
  auto body = statements_t{};
  for (let r_i_op : dag.ops.foreach_rindex()) {
    bw_grad_src_t{&body, r_i_op}.push_contribs_stmts(dag.ops[r_i_op]);
  }
  body.push_back(return_t{"0"_s});
  return {decl, body};
}

}//[mto.module-end]
