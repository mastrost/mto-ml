
#include "./expr.h"
#include "no_stl/math/functions.h"
#include "cpp_tools/contract.h"
namespace mto::math::ml::expr::expr {
namespace expr = mto::math::ml::expr::expr;
namespace math = mto::no_stl::math::functions;
}
#include "cpp_tools/defines.h"
namespace mto::math::ml::expr::expr {

/**
 * real_t
 */
real_t::real_t(dag_t *_p_dag, node_id_t _id) : p_dag(_p_dag), id(_id) {
  REQUIRES(p_dag != nullptr);
}

void real_t::operator=(real_t const &o) {
  id = o.id;
}

real_t real_t::operator*(real_t b) const {
  return res(p_dag->times({id, b.id}, ftype));
}

real_t real_t::operator/(real_t b) const {
  return *this * res(p_dag->inv({b.id}, ftype));
}

real_t real_t::operator+(float b) const {
  return (*this) + res(push_const(*p_dag, b));
}

real_t real_t::operator+(real_t b) const {
  return res(p_dag->plus({id, b.id}, ftype));
}

void real_t::operator+=(real_t b) {
  *this = (*this) + b;
}

void real_t::operator-=(real_t b) {
  *this = (*this) - b;
}

real_t real_t::operator-(real_t b) const {
  return *this + res(p_dag->neg({b.id}, ftype));
}

real_t real_t::res(node_id_t res_id) const {
  return {p_dag, res_id};
}

ops_t real_t::ops() const {
  return {p_dag};
}

real_t operator*(float x, real_t b) {
  return b.ops()(x) * b;
}

real_t operator/(float x, real_t b) {
  return b.ops()(x) / b;
}

real_t operator/(real_t x, float b) {
  return x / x.ops()(b);
}

real_t operator+(float x, real_t b) {
  return b.ops()(x) + b;
}

real_t operator-(real_t b) {
  return -1.f * b;
}

real_t operator-(float x, real_t b) {
  return b.ops()(x) - b;
}

real_t relu(real_t x) {
  return x.res(x.p_dag->special({dag::relu, x.id}, ftype));
}

real_t log(real_t x) {
  return x.res(x.p_dag->special({dag::log, x.id}, ftype));
}

real_t exp(real_t x) {
  return x.res(x.p_dag->special({dag::exp, x.id}, ftype));
}

/**
 * vec_t
 */
vec_t::vec_t(dag_t *_p_dag, node_id_t _id, int32_t _n)
    : p_dag(_p_dag), id(_id), n(_n) {
}

vec_t vec_t::operator+(vec_t const &b) const {
  REQUIRES(b.n == n);
  return res(p_dag->plus({id, b.id}, type()));
}

type_t vec_t::type() const {
  return {dtype_t::f32, {n}};
}

vec_t vec_t::res(node_id_t res_id) const {
  return {p_dag, res_id, n};
}

ops_t vec_t::ops() const {
  return {p_dag};
}

/**
 * mat_t
 */
mat_t::mat_t(dag_t *_p_dag, node_id_t _id, shape_t _shape)
    : p_dag(_p_dag), id(_id), shape{_shape} {
}

mat_t mat_t::operator+(mat_t const &b) const {
  REQUIRES(b.shape[0] == shape[0] && b.shape[1] == shape[1]);
  return res(p_dag->plus({id, b.id}, type()));
}

mat_t mat_t::operator*(mat_t const &b) const {
  REQUIRES(b.shape[0] == shape[1]);
  let t = type_t{dtype_t::f32, {shape[0], b.shape[1]}};
  return res(p_dag->matmul({id, b.id}, t));
}

type_t mat_t::type() const {
  return {dtype_t::f32, {shape[0], shape[1]}};
}

mat_t mat_t::res(node_id_t res_id) const {
  let t = (*p_dag).nodes[res_id].t;
  return {p_dag, res_id, {t.shape[0], t.shape[1]}};
}

ops_t mat_t::ops() const {
  return {p_dag};
}

/**
 * ops: real_t
 */
real_t ops_t::operator()(float c) const {
  let id = push_const(*p_dag, c);
  return real_t(p_dag, id);
}

vector_t<real_t> ops_t::operator()(cspan_t<float> cs) const {
  vector_t<real_t> out;
  for (let &c : cs) {
    out.push_back((*this)(c));
  }
  return out;
}

real_t ops_t::real() const {
  let id = p_dag->var(ftype);
  return real_t{p_dag, id};
}

real_t ops_t::cases(real_t cond, vector_t<case_t> const &cases) const {
  vector_t<dag::cases_t::case_t> dag_cases;
  for (let &c : cases) {
    dag_cases.push_back({c.condition_value.id, c.result_value.id});
  }
  return {p_dag, p_dag->cases({cond.id, dag_cases}, ftype)};
}

/**
 * ops: vec_t
 */
vec_t ops_t::vec(int32_t n) const {
  let id = p_dag->var({dtype_t::f32, {n}});
  return vec_t{p_dag, id, n};
}

/**
 * ops: mat_t
 */
mat_t ops_t::mat(int32_t m, int32_t n, bool row_major) const {
  let id = p_dag->var({dtype_t::f32, {m, n}, row_major});
  return mat_t{p_dag, id, {m, n}};
}

/**
 * operators on arrays of real_t
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

}
