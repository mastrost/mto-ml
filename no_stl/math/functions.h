#pragma once

//[mto-gen.begin]
namespace mto::no_stl::math::functions {
}
#include "cpp_tools/defines.h"
//[mto-gen.end]
//[mto]
namespace mto::no_stl::math::functions {//[mto.module-begin]

/**
 * puissances
 */
float pow(float x, float exp);
double pow(double x, double exp);

float sqrt(float x);
double sqrt(double x);

float log(float x);
double log(double x);

float log2(float x);
double log2(double x);

float exp(float x);
double exp(double x);

float exp2(float x);
double exp2(double x);

/**
 * int conversion
 */
float floor(float);
double floor(double);

float round(float);
double round(double);

/**
 * trigo
 */
float cos(float x);
double cos(double x);

float sin(float x);
double sin(double x);

float acos(float x);
double acos(double x);

float asin(float x);
double asin(double x);

float atan(float t);
double atan(double t);

float atan2(float y, float x);
double atan2(double y, double x);

template <typename f_t>
static constexpr f_t pi = 3.14159265358979323846;

template <typename f_t>
f_t deg_to_grad(f_t a) {
  return pi<f_t> * a / f_t(180);
}

template <typename f_t>
f_t grad_to_deg(f_t d) {
  return f_t(180) * d / pi<f_t>;
}

/**
 * algo
 */
float fabs(float x);
double fabs(double x);

template <typename _t>
_t abs(_t x) {
  return x >= 0 ? x : -x;
}

template <typename _t>
inline _t min(_t x, _t y) {
  if (x <= y)
    return x;
  else
    return y;
}

template <typename _t>
inline _t max(_t x, _t y) {
  if (x >= y)
    return x;
  else
    return y;
}

template <typename _t>
inline _t clamp(_t x, _t _min, _t _max) {
  return min(max(x, _min), _max);
}

}//[mto.ns_end]
