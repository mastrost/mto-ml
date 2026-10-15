//[mto.import ./ast_to_c_source]
//[mto.import cpp_tools/unittest:UNITTEST#]
//[mto.import no_stl/string/string]
#include <cstdio>

//[mto-gen.begin]
#include "./ast_to_c_source.h"
#include "cpp_tools/unittest.h"
#include "no_stl/string/string.h"
namespace mto::math::ml::expr::compiler::ast_to_c_source {
namespace ast_to_c_source = mto::math::ml::expr::compiler::ast_to_c_source;
namespace string = mto::no_stl::string::string;
}
#include "cpp_tools/defines.h"
//[mto-gen.end]
//[mto]
namespace mto::math::ml::expr::compiler::ast_to_c_source {//[mto.module-begin]

using namespace ast;
using namespace string::literal;

UNITTEST() {
  let ast = function_def_t{
      {"func", "int*", {{"x", "int"}, {"y", "float *"}}},
      {{
          expression_t{bin_op_t{"=", "x"_s, "y"_s}},
          expression_t{unary_op_t{"-", "x"_s}},
          expression_t{call_t{"f", {"x"_s, "y"_s}}},
          return_t{"u"_s},
          if_t{
              {"u"_s, {expression_t{bin_op_t{"=", "x"_s, "y"_s}}}},
              {"u"_s, {expression_t{"y"_s}}},
          },
          while_t{
              expression_t{"b"},
              {},
          },
          var_decl_t{"int", "x"},
      }},
  };
  let src = generate_c_source(ast);

  printf("%s\n", src.c_str_host().c_str());
}

}//[mto.module-end]
