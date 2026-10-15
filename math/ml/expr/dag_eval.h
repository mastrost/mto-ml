#pragma once

#include "./dag.h"
#include "./values.h"
#include "no_stl/unique_ptr/unique_ptr.h"
#include "no_stl/result/error.h"
#include "no_stl/span/span.h"
#include "no_stl/vector/vector.h"
#include "no_stl/byte/byte.h"
namespace mto::math::ml::expr::dag_eval {
namespace dag = mto::math::ml::expr::dag;
using mto::math::ml::expr::values::fmat_t;
using mto::no_stl::unique_ptr::unique_ptr::unique_ptr_t;
using mto::no_stl::result::error::result_t;
using mto::no_stl::result::error::error_t;
using mto::no_stl::result::error::empty_t;
using mto::no_stl::span::span::cspan_t;
using mto::no_stl::vector::vector::vector_t;
using mto::no_stl::byte::byte::byte_t;
}
#include "cpp_tools/defines.h"
namespace mto::math::ml::expr::dag_eval {

using dag::dag_t;
using dag::node_id_t;

/**
 */
struct dag_data_t {
  /**
   * access to data from the host, to fill inputs, retrieve outputs, etc.
   */
  virtual void zero() = 0;
  virtual float *as_float(node_id_t id) = 0;
  virtual fmat_t as_fmat(node_id_t id) = 0;

  virtual ~dag_data_t() {}
};

struct evaluator_t {
  // Note: allocation may or may not use the stride indication in the dag.
  virtual unique_ptr_t<dag_data_t> allocate() = 0;

  virtual result_t<> eval(dag_data_t &values) = 0;
  virtual result_t<> eval_fw_grad(dag_data_t &values,
                                  dag_data_t &fw_grad_values) = 0;
  virtual result_t<> eval_bw_grad(dag_data_t &values,
                                  dag_data_t &bw_grad_values) = 0;

  /**
   * deprecated
   */
  virtual result_t<> eval(float *values) = 0;
  virtual result_t<> eval(byte_t *values) = 0;
  virtual result_t<>
  eval_bw_grad(float *bw_grad_values, float const *values) = 0;

  virtual ~evaluator_t() {}
};

/**
 * basic interpreted implementation
 */
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

unique_ptr_t<evaluator_t>
create_dag_evaluator(dag_t const *p_dag);

}
