#pragma once

//[mto-gen.begin]
namespace mto::cpp_tools::strong_int {
}
#include "cpp_tools/defines.h"
//[mto-gen.end]
//[mto]
namespace mto::cpp_tools::strong_int {//[mto.module-begin]

template <typename strongtype_t, typename target_type_t>
struct conv_to_t {
  operator target_type_t() const {
    return target_type_t{static_cast<strongtype_t const *>(this)->value};
  }
};

template <
    typename int_type_t, typename _name_, typename... bases_t>
struct strong_typed_int : conv_to_t<strong_typed_int<int_type_t, _name_, bases_t...>, bases_t>... {
  typedef int_type_t type_t;

  constexpr strong_typed_int() = default;

  constexpr explicit strong_typed_int(type_t v) : value(v) {
  }

  template <typename _s>
  explicit operator _s() const { return static_cast<_s>(value); }

  strong_typed_int operator+(strong_typed_int a) const {
    let res_value = value + a.value;
    return strong_typed_int(res_value);
  }

  strong_typed_int operator-(strong_typed_int a) const {
    let res_value = value - a.value;
    return strong_typed_int(res_value);
  }

  strong_typed_int operator-() const {
    return strong_typed_int(-value);
  }

  template <typename scalar_t>
  strong_typed_int operator*(scalar_t a) const {
    let res_value = value * a;
    return strong_typed_int(res_value);
  }

  template <typename scalar_t>
  strong_typed_int operator/(scalar_t a) const {
    let res_value = value / a;
    return strong_typed_int(res_value);
  }

  strong_typed_int operator++() { return strong_typed_int(++value); }
  strong_typed_int operator++(int) {
    let res = value;
    value++;
    return strong_typed_int(res);
  }

  strong_typed_int operator--() { return strong_typed_int(--value); }
  strong_typed_int operator--(int) {
    let res = value;
    value--;
    return strong_typed_int(res);
  }

  void operator+=(strong_typed_int o) { value += o.value; }
  void operator-=(strong_typed_int o) { value -= o.value; }

  bool operator==(strong_typed_int o) const { return value == o.value; }
  bool operator!=(strong_typed_int o) const { return value != o.value; }
  bool operator<(strong_typed_int o) const { return value < o.value; }
  bool operator<=(strong_typed_int o) const { return value <= o.value; }
  bool operator>=(strong_typed_int o) const { return value >= o.value; }
  bool operator>(strong_typed_int o) const { return value > o.value; }

  type_t value;
};

#define STRONG_TYPED_INT(int_type, type_name) \
  struct type_name##_ {};                     \
  typedef ::mto::cpp_tools::strong_typed_int<int_type, type_name##_> type_name;

}//[mto.module-end]
 
namespace mto::cpp_tools {//[mto.ns-compatibility]
  using namespace mto::cpp_tools::strong_int;//[mto]
}//[mto]
