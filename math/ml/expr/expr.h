#pragma once

//[mto.import ./dag]
//[mto.import no_stl/vector/vector:vector_t]
//[mto.import no_stl/variant/heap_variant:heap_variant_t]
//[mto.import cpp_tools/strong_int:STRONG_TYPED_INT#]
//[mto.import no_stl/span/span:cspan_t]

//[mto-gen.begin]
#include "./dag.h"
#include "no_stl/vector/vector.h"
#include "no_stl/variant/heap_variant.h"
#include "cpp_tools/strong_int.h"
#include "no_stl/span/span.h"
namespace mto::math::ml::expr::expr {
namespace dag = mto::math::ml::expr::dag;
using mto::no_stl::vector::vector::vector_t;
using mto::no_stl::variant::heap_variant::heap_variant_t;
using mto::no_stl::span::span::cspan_t;
}
#include "cpp_tools/defines.h"
//[mto-gen.end]
//[mto]
namespace mto::math::ml::expr::expr {//[mto.module-begin]

using dag::node_id_t;
using dag::dag_t;

struct ops_t;

struct real_t {
public:
  real_t(dag_t *_p_dag, float c);
  real_t(dag_t *_p_dag);
  real_t(dag_t *_p_dag, node_id_t _id);

  void operator=(real_t const &o);

  real_t operator*(real_t b) const;
  real_t operator/(real_t b) const;
  real_t operator+(float b) const;
  real_t operator+(real_t b) const;
  void operator+=(real_t b);
  void operator-=(real_t b);
  real_t operator-(real_t b) const;
  real_t res(node_id_t res_id) const;

  ops_t ops() const;

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

struct ops_t {
  struct case_t {
    real_t condition_value;
    real_t result_value;
  };

  dag_t *const p_dag;

  real_t operator()(float c) const;
  real_t real() const;

  real_t cases(real_t cond, vector_t<case_t> const &cases) const;
};

/**
 * operators on arrays/tensors
 * TODO: create an 'array/tensor' user type (traduit en float dans le dag
 *       ou bien en tensor dans le dag, si tensor disponible).
 */
vector_t<real_t> operator+(cspan_t<real_t> A, cspan_t<real_t> B);
vector_t<real_t> operator-(cspan_t<real_t> A, cspan_t<real_t> B);
real_t operator|(cspan_t<real_t> A, cspan_t<real_t> B);

real_t mse(cspan_t<vector_t<real_t>> samples,
           cspan_t<vector_t<real_t>> predictions);

/**
 * utils expressions
 */
// !ne pas utiliser apres un relu, mais depuis un input a valeur dans [-inf,+inf]
float sigmoid(float x);
real_t sigmoid(real_t x);


// Attention, softmax à l'overflow facile
// -> maintenir le logits a des nombres petits.
vector_t<real_t> softmax(cspan_t<real_t> logits);
vector_t<float> softmax(cspan_t<float> logits);

// bon degré de liberté (n-1), et le dernier logits fixé a 1/n
vector_t<real_t>
softmax_dim_minus_one(cspan_t<real_t> partial_logits);
vector_t<float>
softmax_dim_minus_one(cspan_t<float> partial_logits);

}//[mto.module-end]
