//[mto.import ./functions]

#include <cmath>

//[mto-gen.begin]
#include "./functions.h"
namespace mto::no_stl::math::functions {
namespace functions = mto::no_stl::math::functions;
}
#include "cpp_tools/defines.h"
//[mto-gen.end]
//[mto]
namespace mto::no_stl::math::functions {//[mto.module-begin]

/**
 * puissances
 */
float pow(float x, float exp) {
  return std::pow(x, exp);
}

double pow(double x, double exp) {
  return std::pow(x, exp);
}

float sqrt(float x) {
  return std::sqrt(x);
}

double sqrt(double x) {
  return std::sqrt(x);
}

float log(float x) {
  return std::log(x);
}

double log(double x) {
  return std::log(x);
}

float log2(float x) {
  return std::log2(x);
}

double log2(double x) {
  return std::log2(x);
}

float exp(float x) {
  return std::exp(x);
}

double exp(double x) {
  return std::exp(x);
}

float exp2(float x) {
  return std::exp2(x);
}

double exp2(double x) {
  return std::exp2(x);
}

/**
 * int conversion
 */
float floor(float x) {
  return std::floor(x);
}

double floor(double x) {
  return std::floor(x);
}

float round(float x) {
  return std::round(x);
}

double round(double x) {
  return std::round(x);
}

/**
 * trigo
 */
float cos(float x) {
  return std::cos(x);
}

double cos(double x) {
  return std::cos(x);
}

float sin(float x) {
  return std::sin(x);
}

double sin(double x) {
  return std::sin(x);
}

float acos(float x) {
  return std::acos(x);
}

double acos(double x) {
  return std::acos(x);
}

float asin(float x) {
  return std::asin(x);
}

double asin(double x) {
  return std::asin(x);
}

float atan(float t) {
  return std::atan(t);
}

double atan(double t) {
  return std::atan(t);
}

float atan2(float y, float x) {
  return std::atan2(y, x);
}

double atan2(double y, double x) {
  return std::atan2(y, x);
}

/**
 * algo
 */
float fabs(float x) {
  return std::fabs(x);
}

double fabs(double x) {
  return std::fabs(x);
}

}//[mto.ns_end]
