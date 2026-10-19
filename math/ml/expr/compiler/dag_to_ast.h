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
 * Generates functions: 
 *
 * int init_values(float *values, int32_t const *var_ids, 
 *                 float const *var_values, int32_t num_vars);
 *
 * int eval(float *values, int32_t num_values);
 *
 * // `bw_grad_values` must have all values set 0 excepted
 * // the backward first element, which should be set to 1.
 * int eval_bw_grad(float *restrict bw_grad_values,
 *                  float const *restrict values, 
 *                  int32_t num_values);
 */

ast::function_def_t
to_eval_init_c_source(dag::dag_t const &dag, string_t const &func_name);

ast::function_def_t
to_eval_c_source(dag::dag_t const &dag, string_t const &func_name);

ast::function_def_t
to_bw_grad_eval_c_source(dag::dag_t const &dag, string_t const &func_name);

}//[mto.module-end]
