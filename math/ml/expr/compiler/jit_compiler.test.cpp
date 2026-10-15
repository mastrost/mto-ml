#include <cstdio>

#include "./jit_compiler.h"
#include "./../expr.h"
#include "cpp_tools/unittest.h"
namespace mto::math::ml::expr::compiler::jit_compiler {
namespace jit_compiler = mto::math::ml::expr::compiler::jit_compiler;
namespace expr = mto::math::ml::expr::expr;
}
#include "cpp_tools/defines.h"
namespace mto::math::ml::expr::compiler::jit_compiler {

UNITTEST() {
  auto dag = dag::dag_t{};
  auto ops = expr::ops_t{&dag};
  let x = ops.real();
  let y = expr::relu(x * x);
  (void)y;

  let opt_p_eval = compile_dag(dag, "gcc", "/tmp/model.c", "/tmp/model.so");
  if (!opt_p_eval) {
    fprintf(stderr, "error: %s\n", opt_p_eval.get_error().msg.c_str_host().c_str());
    CHECK(false);
  }

  let num_values = int32_t(dag.nodes.size());
  auto &eval = **opt_p_eval;

  float values[num_values];
  values[int32_t(x.id)] = 10;
  let res = eval.eval(values);
  CHECK(res);
  let y_value = values[int32_t(y.id)];
  CHECK(y_value == 100);

  float bw_grad_values[num_values];
  for (auto i = 0; i < num_values; ++i) {
    bw_grad_values[i] = 0;
  }
  bw_grad_values[int32_t(y.id)] = 1;
  let res2 = eval.eval_bw_grad(bw_grad_values, values);
  CHECK(res2);
  let dy = bw_grad_values[int32_t(x.id)];
  CHECK(dy == 20);
}

}
