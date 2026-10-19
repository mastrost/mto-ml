#pragma once

//[mto.import ./ast]
//[mto.import no_stl/string/string:string_t]

//[mto-gen.begin]
#include "./ast.h"
#include "no_stl/string/string.h"
namespace mto::math::ml::expr::compiler::ast_to_c_source {
namespace ast = mto::math::ml::expr::compiler::ast;
using mto::no_stl::string::string::string_t;
}
#include "cpp_tools/defines.h"
//[mto-gen.end]
//[mto]
namespace mto::math::ml::expr::compiler::ast_to_c_source {//[mto.module-begin]

string_t
generate_c_source(ast::function_def_t const &f);

string_t get_c_header();

}//[mto.module-end]
