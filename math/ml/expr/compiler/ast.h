#pragma once

//[mto.import no_stl/string/string:string_t]
//[mto.import no_stl/vector/vector:vector_t]
//[mto.import no_stl/variant/heap_variant:heap_variant_t]

//[mto-gen.begin]
#include "no_stl/string/string.h"
#include "no_stl/vector/vector.h"
#include "no_stl/variant/heap_variant.h"
namespace mto::math::ml::expr::compiler::ast {
using mto::no_stl::string::string::string_t;
using mto::no_stl::vector::vector::vector_t;
using mto::no_stl::variant::heap_variant::heap_variant_t;
}
#include "cpp_tools/defines.h"
//[mto-gen.end]
//[mto]
namespace mto::math::ml::expr::compiler::ast {//[mto.module-begin]

struct function_prototype_t {
  struct parameter_t {
    string_t type;
    string_t name;
  };

  string_t name;
  string_t result_type;
  vector_t<parameter_t> parameters;
};

struct unary_op_t;
struct bin_op_t;
struct call_t;

typedef heap_variant_t<string_t, unary_op_t, bin_op_t, call_t>
    expression_t;

struct return_t;
struct if_case_t;

typedef vector_t<if_case_t> if_t;

struct while_t;
struct var_decl_t;

typedef heap_variant_t<var_decl_t, expression_t, return_t, if_t, while_t>
    statement_t;

struct unary_op_t {
  string_t op;
  expression_t expr;
};

struct bin_op_t {
  string_t op;
  expression_t lhs;
  expression_t rhs;
};

struct call_t {
  string_t function_name;
  vector_t<expression_t> arguments;
};

struct var_decl_t {
  string_t type;
  string_t name;
};

struct return_t {
  expression_t expr;
};

typedef vector_t<statement_t> statements_t;

struct if_case_t {
  expression_t condition;
  statements_t body;
};

struct function_def_t {
  function_prototype_t prototype;
  statements_t body;
};

struct while_t {
  expression_t condition;
  statements_t body;
};

}//[mto.module-end]
