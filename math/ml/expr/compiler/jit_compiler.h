#pragma once

//[mto.import ../dag]
//[mto.import no_stl/result/result]
//[mto.import no_stl/unique_ptr/unique_ptr:unique_ptr_t]

//[mto-gen.begin]
#include "./../dag.h"
#include "no_stl/result/result.h"
#include "no_stl/unique_ptr/unique_ptr.h"
namespace mto::math::ml::expr::compiler::jit_compiler {
namespace dag = mto::math::ml::expr::dag;
namespace result = mto::no_stl::result::result;
using mto::no_stl::unique_ptr::unique_ptr::unique_ptr_t;
}
#include "cpp_tools/defines.h"
//[mto-gen.end]
//[mto]
namespace mto::math::ml::expr::compiler::jit_compiler {//[mto.module-begin]

struct evaluator_t {
  virtual int init_values(float *values, int32_t const *var_ids,
                          float const *var_values, int32_t num_vars) = 0;

  virtual int eval(float *values, int32_t num_values) = 0;

  virtual int eval_bw_grad(float *bw_grad_values, float const *values, int32_t num_values) = 0;

  virtual ~evaluator_t() {}
};

unique_ptr_t<evaluator_t>
compile_dag(dag::dag_t const &dag);

}//[mto.module-end]
