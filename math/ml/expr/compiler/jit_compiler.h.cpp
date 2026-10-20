//[mto.import ./jit_compiler]
//[mto.import ./dag_to_ast]
//[mto.import ./ast_to_c_source]
#include <dlfcn.h>
#include <cstdio>

//[mto-gen.begin]
#include "./jit_compiler.h"
#include "./dag_to_ast.h"
#include "./ast_to_c_source.h"
namespace mto::math::ml::expr::compiler::jit_compiler {
namespace jit_compiler = mto::math::ml::expr::compiler::jit_compiler;
namespace dag_to_ast = mto::math::ml::expr::compiler::dag_to_ast;
namespace ast_to_c_source = mto::math::ml::expr::compiler::ast_to_c_source;
}
#include "cpp_tools/defines.h"
//[mto-gen.end]
//[mto]
namespace mto::math::ml::expr::compiler::jit_compiler {//[mto.module-begin]

using namespace dag_to_ast;
using namespace ast_to_c_source;

namespace {
struct evaluator_impl_t : evaluator_t {
  result_t<empty_t>
  eval(float *values) {
    let err = c_eval(values);
    if (err != 0) {
      return error_t{"error occured in compiled 'eval'"};
    } else {
      return empty_t{};
    }
  }

  result_t<empty_t>
  eval_bw_grad(float *bw_grad_values, float const *values) {
    let err = c_eval_bw_grad(bw_grad_values, values);
    if (err != 0) {
      return error_t{"error occured in compiled 'eval_bw_grad'"};
    } else {
      return empty_t{};
    }
  }

  ~evaluator_impl_t() {
    dlclose(handle);
  }

  evaluator_impl_t(void *_handle,
                   eval_func_t _c_eval,
                   eval_bw_grad_func_t _c_eval_bw_grad)
      : handle(_handle),
        c_eval(_c_eval), c_eval_bw_grad(_c_eval_bw_grad) {
  }

  void *const handle;
  eval_func_t const c_eval;
  eval_bw_grad_func_t const c_eval_bw_grad;
};

string_t
get_full_c_source(dag::dag_t const &dag) {
  string_t src = get_c_header();
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
  return src;
}

}

result_t<unique_ptr_t<evaluator_t>>
compile_dag(dag::dag_t const &dag,
            string_t const &compiler_path,
            string_t const &c_source_path,
            string_t const &lib_path,
            bool remove_tmp_files) {
  {
    let src_str = get_full_c_source(dag);
    let f = fopen(c_source_path.c_str_host(), "w");
    if (f == NULL) {
      return error_t{"could not open '" + c_source_path + "' for writting the c source"};
    }
    fprintf(f, "%s", src_str.c_str_host().c_str());
    fclose(f);
  }
  let gcc_cmd = compiler_path + " -O0 -FPIC -shared -o " + lib_path + " " + c_source_path;
  let res = std::system(gcc_cmd.c_str_host());
  if (res != 0) {
    return error_t{"could not build lib"};
  }

  ////////////////////

  let handle = dlopen(lib_path.c_str_host(), RTLD_LAZY);
  if (!handle) {
    return error_t{string_t("dl open failed: ") + dlerror()};
  }

  char const *error;

  let c_eval = (eval_func_t)dlsym(handle, "eval");
  if ((error = dlerror()) != NULL) {
    let er = error_t{error};
    dlclose(handle);
    return er;
  }

  let c_eval_bw_grad = (eval_bw_grad_func_t)dlsym(handle, "eval_bw_grad");
  if ((error = dlerror()) != NULL) {
    let er = error_t{error};
    dlclose(handle);
    return er;
  }

  if (remove_tmp_files) {
    remove(c_source_path.c_str_host());
    remove(lib_path.c_str_host());
  }

  return unique_ptr_t<evaluator_t>(new evaluator_impl_t{
      handle, c_eval, c_eval_bw_grad});
}

}//[mto.module-end]
