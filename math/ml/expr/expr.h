#pragma once


#include "./dag.h"
#include "cpp_tools/strong_int.h"
#include "no_stl/vector/vector.h"
#include "no_stl/variant/heap_variant.h"
#include "no_stl/span/span.h"
#include "no_stl/array/array.h"
namespace mto::math::ml::expr::expr {
namespace dag = mto::math::ml::expr::dag;
using mto::no_stl::vector::vector::vector_t;
using mto::no_stl::variant::heap_variant::heap_variant_t;
using mto::no_stl::span::span::cspan_t;
using mto::no_stl::array::array::array_t;
}
#include "cpp_tools/defines.h"
namespace mto::math::ml::expr::expr {

using dag::node_id_t;
using dag::dag_t;
using dag::type_t;
using dag::dtype_t;
using dag::ftype;
using dag::data_t;
using dag::byte_t;

struct ops_t;

/**
 * Todo:
 *  - [dag]
 *    - switch to tensor only
 *      - interface
 *      - data
 *      - operations
 *  - [expr]
 *    - add 'array' handle type
 *    - add 'tensor' handle type
 *    - add 'tensor<>' handle type
 */

/**
 * strongly typed handle for scalar types
 * type = {dtype_t::f32, {}}
 */
struct real_t {
  real_t(dag_t *_p_dag, node_id_t _id);

  void operator=(real_t const &o);

  real_t operator*(real_t b) const;
  real_t operator/(real_t b) const;
  real_t operator+(float b) const;
  real_t operator+(real_t b) const;
  void operator+=(real_t b);
  void operator-=(real_t b);
  real_t operator-(real_t b) const;

  ops_t ops() const;

  real_t res(node_id_t res_id) const;
  dag_t *const p_dag;
  node_id_t id;
};

real_t operator-(real_t b);
real_t operator-(float x, real_t b);
real_t operator+(float x, real_t b);
real_t operator*(float x, real_t b);
real_t operator/(float x, real_t b);
real_t operator/(real_t x, float b);

real_t relu(real_t x);
real_t log(real_t x);
real_t exp(real_t x);

/**
 * operators on arrays of real_t
 */
vector_t<real_t> operator+(cspan_t<real_t> A, cspan_t<real_t> B);
vector_t<real_t> operator-(cspan_t<real_t> A, cspan_t<real_t> B);
real_t operator|(cspan_t<real_t> A, cspan_t<real_t> B);

real_t mse(cspan_t<vector_t<real_t>> samples,
           cspan_t<vector_t<real_t>> predictions);

/**
 * strongly typed handle for vector types
 * type = {dtype_t::f32, {n}}
 */
struct vec_t {
  vec_t(dag_t *_p_dag, node_id_t _id, int32_t n);

  vec_t operator+(vec_t const &b) const;

  type_t type() const;
  ops_t ops() const;

  dag_t *const p_dag;
  node_id_t id;
  int32_t n;

  //internal
  vec_t res(node_id_t res_id) const;
};

/**
 * strongly typed handle for matrix types
 * type = {dtype_t::f32, {n, m}}
 */
struct mat_t {
  typedef array_t<int32_t, size_t, 2> shape_t;

  mat_t(dag_t *_p_dag, node_id_t _id, shape_t shape);

  mat_t operator+(mat_t const &b) const;
  // matmul
  mat_t operator*(mat_t const &b) const;

  type_t type() const;
  ops_t ops() const;

  dag_t *const p_dag;
  node_id_t id;
  shape_t shape;
  // Note: we could host the stripe to propagate it more cleverly
  //       (even if it's just a hint)

  //internal
  mat_t res(node_id_t res_id) const;
};

struct ops_t {
  struct case_t {
    real_t condition_value;
    real_t result_value;
  };

  dag_t *const p_dag;

  /**
   * real_t
   */
  real_t operator()(float c) const;
  vector_t<real_t> operator()(cspan_t<float> cs) const;
  real_t real() const;
  real_t cases(real_t cond, vector_t<case_t> const &cases) const;

  /**
   * vec_t
   */
  vec_t vec(int32_t n) const;

  /**
   * mat_t
   */
  mat_t mat(int32_t m, int32_t n, bool row_major = true) const;
};

/**
 * utils expressions
 */
// !do not use after a relu, but from an input with values in [-inf,+inf]
float sigmoid(float x);
real_t sigmoid(real_t x);

// Warning, softmax is prone to overflow
// -> keep the logits at small numbers.
vector_t<real_t> softmax(cspan_t<real_t> logits);
vector_t<float> softmax(cspan_t<float> logits);

// good degree of freedom (n-1), and the last logit is fixed at 1/n
vector_t<real_t>
softmax_dim_minus_one(cspan_t<real_t> partial_logits);
vector_t<float>
softmax_dim_minus_one(cspan_t<float> partial_logits);

}
