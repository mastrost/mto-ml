#pragma once

//[mto.import ./ast]
//[mto.import ../dag]
//[mto.import no_stl/string/string:string_t]

//[mto-gen.begin]
#include "./ast.h"
#include "./../dag.h"
#include "no_stl/string/string.h"
namespace mto::math::ml::expr::compiler::dag_to_ast {
namespace ast = mto::math::ml::expr::compiler::ast;
namespace dag = mto::math::ml::expr::dag;
using mto::no_stl::string::string::string_t;
}
#include "cpp_tools/defines.h"
//[mto-gen.end]
//[mto]
namespace mto::math::ml::expr::compiler::dag_to_ast {//[mto.module-begin]

/**
 * Types of generates functions:
 */
typedef int (*eval_func_t)(float *values);

// `bw_grad_values` must have all values set 0 excepted
// the backward first element, which should be set to 1.
typedef int (*eval_bw_grad_func_t)(float *bw_grad_values,
                                   float const *values);

ast::function_def_t
to_eval_c_source(dag::dag_t const &dag, string_t const &func_name);

ast::function_def_t
to_bw_grad_eval_c_source(dag::dag_t const &dag, string_t const &func_name);

}//[mto.module-end]
