#pragma once


#include "./../dag_eval.h"
#include "no_stl/unique_ptr/unique_ptr.h"
#include "no_stl/string/string.h"
#include "no_stl/result/error.h"
namespace mto::math::ml::expr::compiler::jit_compiler {
namespace dag_eval = mto::math::ml::expr::dag_eval;
using mto::no_stl::unique_ptr::unique_ptr::unique_ptr_t;
using mto::no_stl::string::string::string_t;
using mto::no_stl::result::error::result_t;
using mto::no_stl::result::error::error_t;
using mto::no_stl::result::error::empty_t;
}
#include "cpp_tools/defines.h"
namespace mto::math::ml::expr::compiler::jit_compiler {

// Note: compiled version is only x2 times faster then interpreted one
//       (which is quite fast), due to the lack of vectorization and
//       tensor support.
result_t<unique_ptr_t<dag_eval::evaluator_t>>
compile_dag(dag::dag_t const &dag,
            string_t const &compiler_path,
            string_t const &c_source_path,
            string_t const &lib_path,
            bool remove_tmp_files = true);

}
