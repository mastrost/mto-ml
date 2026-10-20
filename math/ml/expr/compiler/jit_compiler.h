#pragma once

//[mto.import ../dag]
//[mto.import no_stl/result/result]
//[mto.import no_stl/unique_ptr/unique_ptr:unique_ptr_t]
//[mto.import no_stl/string/string:string_t]

//[mto-gen.begin]
#include "./../dag.h"
#include "no_stl/result/result.h"
#include "no_stl/unique_ptr/unique_ptr.h"
#include "no_stl/string/string.h"
namespace mto::math::ml::expr::compiler::jit_compiler {
namespace dag = mto::math::ml::expr::dag;
namespace result = mto::no_stl::result::result;
using mto::no_stl::unique_ptr::unique_ptr::unique_ptr_t;
using mto::no_stl::string::string::string_t;
}
#include "cpp_tools/defines.h"
//[mto-gen.end]
//[mto]
namespace mto::math::ml::expr::compiler::jit_compiler {//[mto.module-begin]

struct empty_t {};

struct error_t {
  string_t msg;
};

template <typename _t>
using result_t = result::result_t<_t, error_t>;

struct evaluator_t {
  virtual result_t<empty_t> eval(float *values) = 0;

  virtual result_t<empty_t>
  eval_bw_grad(float *bw_grad_values, float const *values) = 0;

  virtual ~evaluator_t() {}
};

result_t<unique_ptr_t<evaluator_t>>
compile_dag(dag::dag_t const &dag,
            string_t const &compiler_path,
            string_t const &c_source_path,
            string_t const &lib_path,
            bool remove_tmp_files = true);

}//[mto.module-end]
