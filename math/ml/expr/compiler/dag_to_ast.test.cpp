//[mto.import ./dag_to_ast]
//[mto.import ./ast_to_c_source]
//[mto.import ./jit_compiler]
//[mto.import ../expr]
//[mto.import cpp_tools/unittest:UNITTEST#]

#include <cstdio>

//[mto-gen.begin]
#include "./dag_to_ast.h"
#include "./ast_to_c_source.h"
#include "./jit_compiler.h"
#include "./../expr.h"
#include "cpp_tools/unittest.h"
namespace mto::math::ml::expr::compiler::dag_to_ast {
namespace dag_to_ast = mto::math::ml::expr::compiler::dag_to_ast;
namespace ast_to_c_source = mto::math::ml::expr::compiler::ast_to_c_source;
namespace jit_compiler = mto::math::ml::expr::compiler::jit_compiler;
namespace expr = mto::math::ml::expr::expr;
}
#include "cpp_tools/defines.h"
//[mto-gen.end]
//[mto]
namespace mto::math::ml::expr::compiler::dag_to_ast {//[mto.module-begin]

using namespace ast_to_c_source;

UNITTEST() {
  auto dag = dag::dag_t{};
  auto ops = expr::ops_t{&dag};
  let c = ops(123) - ops(1);
  let x = ops.real();
  let y = (x * (-x) + c) / 8;
  let z = relu(log(exp(y)));
  ops.cases(z, {{
                    ops(1),
                    ops(10),
                },
                {
                    ops(2),
                    ops(20),
                }});

  string_t src = get_c_header();
  src += "\n";
  {
    let ast = to_eval_init_c_source(dag, "init_values");
    src += generate_c_source(ast);
  }
  src += "\n";
  {
    let ast = to_eval_c_source(dag, "eval");
    src += generate_c_source(ast);
  }
  src += "\n";
  {
    let ast = to_bw_grad_eval_c_source(dag, "eval_bw_grad");
    src += generate_c_source(ast);
  }
  printf("%s\n", src.c_str_host().c_str());
}

}//[mto.module-end]
