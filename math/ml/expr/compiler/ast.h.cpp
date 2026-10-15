
#include "./ast.h"
#include "no_stl/variant/heap_variant.impl.h"
namespace mto::math::ml::expr::compiler::ast {
namespace ast = mto::math::ml::expr::compiler::ast;
}
#include "cpp_tools/defines.h"
namespace mto::math::ml::expr::compiler::ast {
}

namespace _ns =
mto::math::ml::expr::compiler::ast
    ;

INSTANCIATE_HEAP_VARIANT(
    _ns::string_t,
    _ns::unary_op_t,
    _ns::bin_op_t,
    _ns::call_t);

INSTANCIATE_HEAP_VARIANT(
    _ns::var_decl_t,
    _ns::expression_t,
    _ns::return_t,
    _ns::if_t,
    _ns::while_t);
