#pragma once
//[mto.import no_stl/vector/vector:vector_t]
//[mto.import no_stl/variant/stack_variant:stack_variant_t]
//[mto.import cpp_tools/strong_int:STRONG_TYPED_INT#]
//[mto.import no_stl/span/span:cspan_t]

//[mto-gen.begin]
#include "no_stl/vector/vector.h"
#include "no_stl/variant/stack_variant.h"
#include "cpp_tools/strong_int.h"
#include "no_stl/span/span.h"
namespace mto::math::ml::expr::dag {
using mto::no_stl::vector::vector::vector_t;
using mto::no_stl::variant::stack_variant::stack_variant_t;
using mto::no_stl::span::span::cspan_t;
}
#include "cpp_tools/defines.h"
//[mto-gen.end]
//[mto]
namespace mto::math::ml::expr::dag {//[mto.module-begin]

STRONG_TYPED_INT(int32_t, node_id_t);

/**
 * TODO:
 *  - support tensors
 *  - the dag should be agnostic of the real tensor
 *    dimensions. This enables the calling of the model
 *    with the array of samples, which returns an array
 *    of results, comparable with the samples with
 *    a tensor function in the loss function
 *    -> avoids the loop over all samples in the loss function.
 *       (and makes the dag independant of the number of inputs)
 */
struct fconst_t {
  float value;
};

struct var_t {
  node_id_t id;
};

struct plus_t {
  node_id_t lhs;
  node_id_t rhs;
};

struct neg_t {
  node_id_t sub;
};

struct times_t {
  node_id_t lhs;
  node_id_t rhs;
};

struct inv_t {
  node_id_t sub;
};

struct cases_t {
  struct case_t {
    node_id_t condition_value;
    node_id_t result_value;
  };

  node_id_t condition;
  vector_t<case_t> cases;
};

enum func_t { relu,
              log,
              exp };

struct special_func_t {
  func_t func;
  node_id_t arg;
};

typedef stack_variant_t<fconst_t, var_t,
                        plus_t, neg_t, times_t, inv_t,
                        cases_t, special_func_t>
    any_op_t;

struct dag_t {
  node_id_t _const(float x);
  node_id_t real();
  node_id_t plus(plus_t op);
  node_id_t neg(neg_t op);
  node_id_t times(times_t op);
  node_id_t inv(inv_t op);
  node_id_t cases(cases_t const &op);
  node_id_t special(special_func_t op);

  node_id_t push(any_op_t const &op);

  vector_t<any_op_t, node_id_t> ops;
};

struct var_value_t {
  node_id_t id;
  float value;
};

vector_t<float, node_id_t>
eval(dag_t const &dag, vector_t<var_value_t> const &var_values);

vector_t<float, node_id_t>
eval_fw_grad(dag_t const &dag,
             cspan_t<float, node_id_t> values,
             vector_t<var_value_t> const &var_grads);

vector_t<float, node_id_t>
eval_bw_grad(dag_t const &dag,
             cspan_t<float, node_id_t> values,
             vector_t<var_value_t> const &var_grads);

}//[mto.module-end]
