//[mto.import ./ast_to_c_source]
//[mto.import cpp_tools/contract:REQUIRES#]

//[mto-gen.begin]
#include "./ast_to_c_source.h"
#include "cpp_tools/contract.h"
namespace mto::math::ml::expr::compiler::ast_to_c_source {
namespace ast_to_c_source = mto::math::ml::expr::compiler::ast_to_c_source;
}
#include "cpp_tools/defines.h"
//[mto-gen.end]
//[mto]
namespace mto::math::ml::expr::compiler::ast_to_c_source {//[mto.module-begin]

namespace {

struct gen_t {
  string_t gen(ast::function_prototype_t const &f) {
    string_t src;
    src += f.result_type;
    src += " ";
    src += f.name;
    src += "(";
    for (let i_p : f.parameters.foreach_index()) {
      let &p = f.parameters[i_p];
      if (i_p > 0) {
        src += ", ";
      }
      src += p.type;
      src += " ";
      src += p.name;
    }
    src += ")";
    return src;
  }

  string_t gen(ast::string_t const &e) {
    return e;
  }

  string_t gen(ast::unary_op_t const &e) {
    string_t src;
    src += "(" + e.op + " " + gen(e.expr) + ")";
    return src;
  }

  string_t gen(ast::bin_op_t const &e) {
    string_t src;
    src += "(" + gen(e.lhs) + " " + e.op + " " + gen(e.rhs) + ")";
    return src;
  }

  string_t gen(ast::call_t const &e) {
    string_t src;
    src += e.function_name;
    src += "(";
    for (let i_arg : e.arguments.foreach_index()) {
      if (i_arg > 0) {
        src += ", ";
      }
      src += gen(e.arguments[i_arg]);
    }
    src += ")";
    return src;
  }

  string_t gen(ast::expression_t const &f) {
    return f.visit([&](let &f) { return gen(f); });
  }

  string_t gen(ast::var_decl_t const &f) {
    return f.type + " " + f.name;
  }

  string_t gen(ast::return_t const &f) {
    return "return " + gen(f.expr);
  }

  string_t gen(ast::if_t const &f) {
    REQUIRES(f.size() > 0);

    string_t src;

    for (let i_c : f.foreach_index()) {
      let &c = f[i_c];
      if (i_c == 0) {
        src += "if (" + gen(c.condition) + ")\n";
        src += gen(c.body);
      } else {
        src += "\nelse if (" + gen(c.condition) + ")\n";
        src += gen(c.body);
      }
    }
    return src;
  }

  string_t gen(ast::while_t const &f) {
    string_t src;
    src += "while (" + gen(f.condition) + ")\n";
    src += gen(f.body);
    return src;
  }

  string_t gen(ast::statement_t const &f) {
    return f.visit([&](let &f) { return gen(f); }) + ";";
  }

  string_t gen(ast::statements_t const &statements) {
    string_t src;
    src += "{\n";
    for (let &stmt : statements) {
      src += gen(stmt);
      src += "\n";
    }
    src += "}";
    return src;
  }

  string_t gen(ast::function_def_t const &f) {
    auto src = gen(f.prototype);
    src += "\n";
    src += gen(f.body);
    src += "\n";
    return src;
  }
};

};

string_t
generate_c_source(ast::function_def_t const &f) {
  return gen_t{}.gen(f);
}

string_t get_c_header() {
  string_t src;
  src += "#include <math.h>\n";
  src += "#include <stdint.h>\n";
  src += "\n";
  src +=
      "#ifdef __clang__\n"
      "#pragma clang diagnostic ignored \"-Wparentheses-equality\"\n"
      "#endif\n";
  src += "\n";
  src +=
      "inline float relu(float x)\n"
      "{\n"
      "  return x < 0 ? 0 : x; \n"
      "}\n";

  return src;
}

}//[mto.module-end]
