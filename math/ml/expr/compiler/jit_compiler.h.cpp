//[mto.import ./jit_compiler]

//[mto-gen.begin]
#include "./jit_compiler.h"
namespace mto::math::ml::expr::compiler::jit_compiler {
namespace jit_compiler = mto::math::ml::expr::compiler::jit_compiler;
}
#include "cpp_tools/defines.h"
//[mto-gen.end]
//[mto]
namespace mto::math::ml::expr::compiler::jit_compiler {//[mto.module-begin]

namespace {

struct evaluator_impl_t : evaluator_t {
  int init_values(float *values, int32_t const *var_ids,
                  float const *var_values, int32_t num_vars) {
    EXIT_NOT_IMPL();
  }

  int eval(float *values, int32_t num_values) {
    EXIT_NOT_IMPL();
  }

  int eval_bw_grad(float *bw_grad_values, float const *values, int32_t num_values) {
    EXIT_NOT_IMPL();
  }
};

}

unique_ptr_t<evaluator_t>
compile_dag(dag::dag_t const &dag) {
  EXIT_NOT_IMPL();
}

}//[mto.module-end]
