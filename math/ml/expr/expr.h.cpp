//[mto.import ./expr]
//[mto.import no_stl/math/functions as math]

//[mto-gen.begin]
#include "./expr.h"
#include "no_stl/math/functions.h"
namespace mto::math::ml::expr::expr {
namespace expr = mto::math::ml::expr::expr;
namespace math = mto::no_stl::math::functions;
}
#include "cpp_tools/defines.h"
//[mto-gen.end]
//[mto]
namespace mto::math::ml::expr::expr {//[mto.module-begin]

real_t::real_t(dag_t *_p_dag, float c) : p_dag(_p_dag),
                                         id(p_dag->_const(c)) {
  REQUIRES(p_dag != nullptr);
}

real_t::real_t(dag_t *_p_dag, node_id_t _id) : p_dag(_p_dag), id(_id) {
  REQUIRES(p_dag != nullptr);
}

real_t::real_t(dag_t *_p_dag) : p_dag(_p_dag), id(p_dag->real()) {
  REQUIRES(p_dag != nullptr);
}

void real_t::operator=(real_t const &o) {
  id = o.id;
}

real_t real_t::operator*(real_t b) const {
  return res(p_dag->times({id, b.id}));
}

real_t real_t::operator/(real_t b) const {
  let inv = p_dag->inv({b.id});
  return res(p_dag->times({id, inv}));
}

real_t real_t::operator+(float b) const {
  let c = p_dag->_const(b);
  return res(p_dag->plus({id, c}));
}

real_t real_t::operator+(real_t b) const {
  return res(p_dag->plus({id, b.id}));
}

void real_t::operator+=(real_t b) {
  *this = (*this) + b;
}

void real_t::operator-=(real_t b) {
  *this = (*this) - b;
}

real_t real_t::operator-(real_t b) const {
  let neg = p_dag->neg({b.id});
  return res(p_dag->plus({id, neg}));
}

real_t real_t::res(node_id_t res_id) const {
  return {p_dag, res_id};
}

ops_t real_t::ops() const {
  return {p_dag};
}

real_t operator*(float x, real_t b) {
  return real_t{b.p_dag, x} * b;
}

real_t operator/(float x, real_t b) {
  return real_t{b.p_dag, x} / b;
}

real_t operator/(real_t x, float b) {
  return x / real_t{x.p_dag, b};
}

real_t operator+(float x, real_t b) {
  return real_t{b.p_dag, x} + b;
}

real_t operator-(real_t b) {
  return -1.f * b;
}

real_t operator-(float x, real_t b) {
  return real_t{b.p_dag, x} - b;
}

real_t relu(real_t x) {
  return x.res(x.p_dag->special({dag::relu, x.id}));
}

real_t log(real_t x) {
  return x.res(x.p_dag->special({dag::log, x.id}));
}

real_t exp(real_t x) {
  return x.res(x.p_dag->special({dag::exp, x.id}));
}

/**
 * ops
 */
real_t ops_t::operator()(float c) const {
  return real_t(p_dag, c);
}

real_t ops_t::real() const {
  return real_t(p_dag);
}

real_t ops_t::cases(real_t cond, vector_t<case_t> const &cases) const {
  vector_t<dag::cases_t::case_t> dag_cases;
  for (let &c : cases) {
    dag_cases.push_back({c.condition_value.id, c.result_value.id});
  }
  return {p_dag, p_dag->cases({cond.id, dag_cases})};
}

/**
 * operators on arrays/tensors
 */
vector_t<real_t> operator+(cspan_t<real_t> A, cspan_t<real_t> B) {
  vector_t<real_t> d;
  REQUIRES(A.size() == B.size());
  for (let i : A.foreach_index()) {
    d.push_back(A[i] + B[i]);
  }
  return d;
}
vector_t<real_t> operator-(cspan_t<real_t> A, cspan_t<real_t> B) {
  vector_t<real_t> d;
  REQUIRES(A.size() == B.size());
  for (let i : A.foreach_index()) {
    d.push_back(A[i] - B[i]);
  }
  return d;
}

real_t operator|(cspan_t<real_t> A, cspan_t<real_t> B) {
  REQUIRES(A.size() > 0);
  REQUIRES(A.size() == B.size());
  let ops = A[0].ops();
  auto res = ops(0);
  for (let i : A.foreach_index()) {
    res += A[i] * B[i];
  }
  return res;
}

real_t mse(cspan_t<vector_t<real_t>> samples,
           cspan_t<vector_t<real_t>> predictions) {
  REQUIRES(samples.size() > 0);
  REQUIRES(samples[0].size() > 0);
  REQUIRES(samples.size() == predictions.size());
  let ops = samples[0][0].ops();
  auto res = ops(0);
  for (let i : samples.foreach_index()) {
    let diff = samples[i] - predictions[i];
    res += diff | diff;
  }
  return (1.f / float(samples.size())) * res;
}

/**
 * utils expressions
 */
real_t sigmoid(real_t x) {
  return 1.f / (1.f + exp(-x));
}

float sigmoid(float x) {
  return 1.f / (1.f + math::exp(-x));
}

template <typename f_t>
vector_t<f_t>
softmax(cspan_t<f_t> logits, f_t zero) {
  REQUIRES(logits.size() > 0);
  using math::exp;
  auto total = zero;
  for (let &l : logits) {
    total += exp(l);
  }
  vector_t<f_t> outs;
  for (let &l : logits) {
    outs.push_back(exp(l) / total);
  }
  return outs;
}

vector_t<real_t>
softmax(cspan_t<real_t> logits) {
  let ops = logits[0].ops();
  return softmax(logits, ops(0));
}

vector_t<float>
softmax(cspan_t<float> logits) {
  return softmax(logits, 0.f);
}

vector_t<real_t>
softmax_dim_minus_one(cspan_t<real_t> partial_logits) {
  REQUIRES(partial_logits.size() > 0);
  let ops = partial_logits[0].ops();
  auto logits = vector_t<real_t>(partial_logits);
  logits.push_back(ops(1.f / (partial_logits.size() + 1)));
  return softmax(logits);
}

vector_t<float>
softmax_dim_minus_one(cspan_t<float> partial_logits) {
  REQUIRES(partial_logits.size() > 0);
  auto logits = vector_t<float>(partial_logits);
  logits.push_back(1.f / (partial_logits.size() + 1));
  return expr::softmax(logits);
}

}//[mto.module-end]
