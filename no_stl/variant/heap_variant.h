#pragma once
#include "./heap_variant.common.h"

//[mto-gen.begin]
namespace mto::no_stl::variant::heap_variant {
}
#include "cpp_tools/defines.h"
//[mto-gen.end]
//[mto]
namespace mto::no_stl::variant::heap_variant {//[mto.module-begin]
template <typename _0_t>
struct heap_variant_t<_0_t> {
  heap_variant_t(heap_variant_t const &);
  heap_variant_t(heap_variant_t &&);
  heap_variant_t &operator=(heap_variant_t const &);
  heap_variant_t &operator=(heap_variant_t &&);
  heap_variant_t(_0_t const &x);
  heap_variant_t(_0_t &&x);
  bool is(_0_t *) const;
  template <typename _t>
  bool is() const {
    return is((_t *)nullptr);
  }
  _0_t const &as(_0_t *) const;
  template <typename _t>
  _t const &as() const {
    return as((_t *)nullptr);
  }
  _0_t &as(_0_t *);
  template <typename _t>
  _t &as() {
    return as((_t *)nullptr);
  }
  _0_t const *as_ptr(_0_t *) const;
  template <typename _t>
  _t const *as_ptr() const {
    return as_ptr((_t *)nullptr);
  }
  _0_t *as_ptr(_0_t *);
  template <typename _t>
  _t *as_ptr() {
    return as_ptr((_t *)nullptr);
  }
  template <typename _f>
  decltype(auto) visit(_f const &f) {
    switch (current) {
    case 0:
      return f(*member_0);
    default:
      __builtin_unreachable();
    }
  }
  template <typename _f>
  decltype(auto) visit(_f const &f) const {
    switch (current) {
    case 0:
      return f(*member_0);
    default:
      __builtin_unreachable();
    }
  }
  ~heap_variant_t();
  size_t current;
  union {
    _0_t *member_0;
  };
};
template <typename _0_t, typename _1_t>
struct heap_variant_t<_0_t, _1_t> {
  heap_variant_t(heap_variant_t const &);
  heap_variant_t(heap_variant_t &&);
  heap_variant_t &operator=(heap_variant_t const &);
  heap_variant_t &operator=(heap_variant_t &&);
  heap_variant_t(_0_t const &x);
  heap_variant_t(_1_t const &x);
  heap_variant_t(_0_t &&x);
  heap_variant_t(_1_t &&x);
  bool is(_0_t *) const;
  bool is(_1_t *) const;
  template <typename _t>
  bool is() const {
    return is((_t *)nullptr);
  }
  _0_t const &as(_0_t *) const;
  _1_t const &as(_1_t *) const;
  template <typename _t>
  _t const &as() const {
    return as((_t *)nullptr);
  }
  _0_t &as(_0_t *);
  _1_t &as(_1_t *);
  template <typename _t>
  _t &as() {
    return as((_t *)nullptr);
  }
  _0_t const *as_ptr(_0_t *) const;
  _1_t const *as_ptr(_1_t *) const;
  template <typename _t>
  _t const *as_ptr() const {
    return as_ptr((_t *)nullptr);
  }
  _0_t *as_ptr(_0_t *);
  _1_t *as_ptr(_1_t *);
  template <typename _t>
  _t *as_ptr() {
    return as_ptr((_t *)nullptr);
  }
  template <typename _f>
  decltype(auto) visit(_f const &f) {
    switch (current) {
    case 0:
      return f(*member_0);
    case 1:
      return f(*member_1);
    default:
      __builtin_unreachable();
    }
  }
  template <typename _f>
  decltype(auto) visit(_f const &f) const {
    switch (current) {
    case 0:
      return f(*member_0);
    case 1:
      return f(*member_1);
    default:
      __builtin_unreachable();
    }
  }
  ~heap_variant_t();
  size_t current;
  union {
    _0_t *member_0;
    _1_t *member_1;
  };
};
template <typename _0_t, typename _1_t, typename _2_t>
struct heap_variant_t<_0_t, _1_t, _2_t> {
  heap_variant_t(heap_variant_t const &);
  heap_variant_t(heap_variant_t &&);
  heap_variant_t &operator=(heap_variant_t const &);
  heap_variant_t &operator=(heap_variant_t &&);
  heap_variant_t(_0_t const &x);
  heap_variant_t(_1_t const &x);
  heap_variant_t(_2_t const &x);
  heap_variant_t(_0_t &&x);
  heap_variant_t(_1_t &&x);
  heap_variant_t(_2_t &&x);
  bool is(_0_t *) const;
  bool is(_1_t *) const;
  bool is(_2_t *) const;
  template <typename _t>
  bool is() const {
    return is((_t *)nullptr);
  }
  _0_t const &as(_0_t *) const;
  _1_t const &as(_1_t *) const;
  _2_t const &as(_2_t *) const;
  template <typename _t>
  _t const &as() const {
    return as((_t *)nullptr);
  }
  _0_t &as(_0_t *);
  _1_t &as(_1_t *);
  _2_t &as(_2_t *);
  template <typename _t>
  _t &as() {
    return as((_t *)nullptr);
  }
  _0_t const *as_ptr(_0_t *) const;
  _1_t const *as_ptr(_1_t *) const;
  _2_t const *as_ptr(_2_t *) const;
  template <typename _t>
  _t const *as_ptr() const {
    return as_ptr((_t *)nullptr);
  }
  _0_t *as_ptr(_0_t *);
  _1_t *as_ptr(_1_t *);
  _2_t *as_ptr(_2_t *);
  template <typename _t>
  _t *as_ptr() {
    return as_ptr((_t *)nullptr);
  }
  template <typename _f>
  decltype(auto) visit(_f const &f) {
    switch (current) {
    case 0:
      return f(*member_0);
    case 1:
      return f(*member_1);
    case 2:
      return f(*member_2);
    default:
      __builtin_unreachable();
    }
  }
  template <typename _f>
  decltype(auto) visit(_f const &f) const {
    switch (current) {
    case 0:
      return f(*member_0);
    case 1:
      return f(*member_1);
    case 2:
      return f(*member_2);
    default:
      __builtin_unreachable();
    }
  }
  ~heap_variant_t();
  size_t current;
  union {
    _0_t *member_0;
    _1_t *member_1;
    _2_t *member_2;
  };
};
template <typename _0_t, typename _1_t, typename _2_t, typename _3_t>
struct heap_variant_t<_0_t, _1_t, _2_t, _3_t> {
  heap_variant_t(heap_variant_t const &);
  heap_variant_t(heap_variant_t &&);
  heap_variant_t &operator=(heap_variant_t const &);
  heap_variant_t &operator=(heap_variant_t &&);
  heap_variant_t(_0_t const &x);
  heap_variant_t(_1_t const &x);
  heap_variant_t(_2_t const &x);
  heap_variant_t(_3_t const &x);
  heap_variant_t(_0_t &&x);
  heap_variant_t(_1_t &&x);
  heap_variant_t(_2_t &&x);
  heap_variant_t(_3_t &&x);
  bool is(_0_t *) const;
  bool is(_1_t *) const;
  bool is(_2_t *) const;
  bool is(_3_t *) const;
  template <typename _t>
  bool is() const {
    return is((_t *)nullptr);
  }
  _0_t const &as(_0_t *) const;
  _1_t const &as(_1_t *) const;
  _2_t const &as(_2_t *) const;
  _3_t const &as(_3_t *) const;
  template <typename _t>
  _t const &as() const {
    return as((_t *)nullptr);
  }
  _0_t &as(_0_t *);
  _1_t &as(_1_t *);
  _2_t &as(_2_t *);
  _3_t &as(_3_t *);
  template <typename _t>
  _t &as() {
    return as((_t *)nullptr);
  }
  _0_t const *as_ptr(_0_t *) const;
  _1_t const *as_ptr(_1_t *) const;
  _2_t const *as_ptr(_2_t *) const;
  _3_t const *as_ptr(_3_t *) const;
  template <typename _t>
  _t const *as_ptr() const {
    return as_ptr((_t *)nullptr);
  }
  _0_t *as_ptr(_0_t *);
  _1_t *as_ptr(_1_t *);
  _2_t *as_ptr(_2_t *);
  _3_t *as_ptr(_3_t *);
  template <typename _t>
  _t *as_ptr() {
    return as_ptr((_t *)nullptr);
  }
  template <typename _f>
  decltype(auto) visit(_f const &f) {
    switch (current) {
    case 0:
      return f(*member_0);
    case 1:
      return f(*member_1);
    case 2:
      return f(*member_2);
    case 3:
      return f(*member_3);
    default:
      __builtin_unreachable();
    }
  }
  template <typename _f>
  decltype(auto) visit(_f const &f) const {
    switch (current) {
    case 0:
      return f(*member_0);
    case 1:
      return f(*member_1);
    case 2:
      return f(*member_2);
    case 3:
      return f(*member_3);
    default:
      __builtin_unreachable();
    }
  }
  ~heap_variant_t();
  size_t current;
  union {
    _0_t *member_0;
    _1_t *member_1;
    _2_t *member_2;
    _3_t *member_3;
  };
};
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t>
struct heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t> {
  heap_variant_t(heap_variant_t const &);
  heap_variant_t(heap_variant_t &&);
  heap_variant_t &operator=(heap_variant_t const &);
  heap_variant_t &operator=(heap_variant_t &&);
  heap_variant_t(_0_t const &x);
  heap_variant_t(_1_t const &x);
  heap_variant_t(_2_t const &x);
  heap_variant_t(_3_t const &x);
  heap_variant_t(_4_t const &x);
  heap_variant_t(_0_t &&x);
  heap_variant_t(_1_t &&x);
  heap_variant_t(_2_t &&x);
  heap_variant_t(_3_t &&x);
  heap_variant_t(_4_t &&x);
  bool is(_0_t *) const;
  bool is(_1_t *) const;
  bool is(_2_t *) const;
  bool is(_3_t *) const;
  bool is(_4_t *) const;
  template <typename _t>
  bool is() const {
    return is((_t *)nullptr);
  }
  _0_t const &as(_0_t *) const;
  _1_t const &as(_1_t *) const;
  _2_t const &as(_2_t *) const;
  _3_t const &as(_3_t *) const;
  _4_t const &as(_4_t *) const;
  template <typename _t>
  _t const &as() const {
    return as((_t *)nullptr);
  }
  _0_t &as(_0_t *);
  _1_t &as(_1_t *);
  _2_t &as(_2_t *);
  _3_t &as(_3_t *);
  _4_t &as(_4_t *);
  template <typename _t>
  _t &as() {
    return as((_t *)nullptr);
  }
  _0_t const *as_ptr(_0_t *) const;
  _1_t const *as_ptr(_1_t *) const;
  _2_t const *as_ptr(_2_t *) const;
  _3_t const *as_ptr(_3_t *) const;
  _4_t const *as_ptr(_4_t *) const;
  template <typename _t>
  _t const *as_ptr() const {
    return as_ptr((_t *)nullptr);
  }
  _0_t *as_ptr(_0_t *);
  _1_t *as_ptr(_1_t *);
  _2_t *as_ptr(_2_t *);
  _3_t *as_ptr(_3_t *);
  _4_t *as_ptr(_4_t *);
  template <typename _t>
  _t *as_ptr() {
    return as_ptr((_t *)nullptr);
  }
  template <typename _f>
  decltype(auto) visit(_f const &f) {
    switch (current) {
    case 0:
      return f(*member_0);
    case 1:
      return f(*member_1);
    case 2:
      return f(*member_2);
    case 3:
      return f(*member_3);
    case 4:
      return f(*member_4);
    default:
      __builtin_unreachable();
    }
  }
  template <typename _f>
  decltype(auto) visit(_f const &f) const {
    switch (current) {
    case 0:
      return f(*member_0);
    case 1:
      return f(*member_1);
    case 2:
      return f(*member_2);
    case 3:
      return f(*member_3);
    case 4:
      return f(*member_4);
    default:
      __builtin_unreachable();
    }
  }
  ~heap_variant_t();
  size_t current;
  union {
    _0_t *member_0;
    _1_t *member_1;
    _2_t *member_2;
    _3_t *member_3;
    _4_t *member_4;
  };
};
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t>
struct heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t> {
  heap_variant_t(heap_variant_t const &);
  heap_variant_t(heap_variant_t &&);
  heap_variant_t &operator=(heap_variant_t const &);
  heap_variant_t &operator=(heap_variant_t &&);
  heap_variant_t(_0_t const &x);
  heap_variant_t(_1_t const &x);
  heap_variant_t(_2_t const &x);
  heap_variant_t(_3_t const &x);
  heap_variant_t(_4_t const &x);
  heap_variant_t(_5_t const &x);
  heap_variant_t(_0_t &&x);
  heap_variant_t(_1_t &&x);
  heap_variant_t(_2_t &&x);
  heap_variant_t(_3_t &&x);
  heap_variant_t(_4_t &&x);
  heap_variant_t(_5_t &&x);
  bool is(_0_t *) const;
  bool is(_1_t *) const;
  bool is(_2_t *) const;
  bool is(_3_t *) const;
  bool is(_4_t *) const;
  bool is(_5_t *) const;
  template <typename _t>
  bool is() const {
    return is((_t *)nullptr);
  }
  _0_t const &as(_0_t *) const;
  _1_t const &as(_1_t *) const;
  _2_t const &as(_2_t *) const;
  _3_t const &as(_3_t *) const;
  _4_t const &as(_4_t *) const;
  _5_t const &as(_5_t *) const;
  template <typename _t>
  _t const &as() const {
    return as((_t *)nullptr);
  }
  _0_t &as(_0_t *);
  _1_t &as(_1_t *);
  _2_t &as(_2_t *);
  _3_t &as(_3_t *);
  _4_t &as(_4_t *);
  _5_t &as(_5_t *);
  template <typename _t>
  _t &as() {
    return as((_t *)nullptr);
  }
  _0_t const *as_ptr(_0_t *) const;
  _1_t const *as_ptr(_1_t *) const;
  _2_t const *as_ptr(_2_t *) const;
  _3_t const *as_ptr(_3_t *) const;
  _4_t const *as_ptr(_4_t *) const;
  _5_t const *as_ptr(_5_t *) const;
  template <typename _t>
  _t const *as_ptr() const {
    return as_ptr((_t *)nullptr);
  }
  _0_t *as_ptr(_0_t *);
  _1_t *as_ptr(_1_t *);
  _2_t *as_ptr(_2_t *);
  _3_t *as_ptr(_3_t *);
  _4_t *as_ptr(_4_t *);
  _5_t *as_ptr(_5_t *);
  template <typename _t>
  _t *as_ptr() {
    return as_ptr((_t *)nullptr);
  }
  template <typename _f>
  decltype(auto) visit(_f const &f) {
    switch (current) {
    case 0:
      return f(*member_0);
    case 1:
      return f(*member_1);
    case 2:
      return f(*member_2);
    case 3:
      return f(*member_3);
    case 4:
      return f(*member_4);
    case 5:
      return f(*member_5);
    default:
      __builtin_unreachable();
    }
  }
  template <typename _f>
  decltype(auto) visit(_f const &f) const {
    switch (current) {
    case 0:
      return f(*member_0);
    case 1:
      return f(*member_1);
    case 2:
      return f(*member_2);
    case 3:
      return f(*member_3);
    case 4:
      return f(*member_4);
    case 5:
      return f(*member_5);
    default:
      __builtin_unreachable();
    }
  }
  ~heap_variant_t();
  size_t current;
  union {
    _0_t *member_0;
    _1_t *member_1;
    _2_t *member_2;
    _3_t *member_3;
    _4_t *member_4;
    _5_t *member_5;
  };
};
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t>
struct heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t> {
  heap_variant_t(heap_variant_t const &);
  heap_variant_t(heap_variant_t &&);
  heap_variant_t &operator=(heap_variant_t const &);
  heap_variant_t &operator=(heap_variant_t &&);
  heap_variant_t(_0_t const &x);
  heap_variant_t(_1_t const &x);
  heap_variant_t(_2_t const &x);
  heap_variant_t(_3_t const &x);
  heap_variant_t(_4_t const &x);
  heap_variant_t(_5_t const &x);
  heap_variant_t(_6_t const &x);
  heap_variant_t(_0_t &&x);
  heap_variant_t(_1_t &&x);
  heap_variant_t(_2_t &&x);
  heap_variant_t(_3_t &&x);
  heap_variant_t(_4_t &&x);
  heap_variant_t(_5_t &&x);
  heap_variant_t(_6_t &&x);
  bool is(_0_t *) const;
  bool is(_1_t *) const;
  bool is(_2_t *) const;
  bool is(_3_t *) const;
  bool is(_4_t *) const;
  bool is(_5_t *) const;
  bool is(_6_t *) const;
  template <typename _t>
  bool is() const {
    return is((_t *)nullptr);
  }
  _0_t const &as(_0_t *) const;
  _1_t const &as(_1_t *) const;
  _2_t const &as(_2_t *) const;
  _3_t const &as(_3_t *) const;
  _4_t const &as(_4_t *) const;
  _5_t const &as(_5_t *) const;
  _6_t const &as(_6_t *) const;
  template <typename _t>
  _t const &as() const {
    return as((_t *)nullptr);
  }
  _0_t &as(_0_t *);
  _1_t &as(_1_t *);
  _2_t &as(_2_t *);
  _3_t &as(_3_t *);
  _4_t &as(_4_t *);
  _5_t &as(_5_t *);
  _6_t &as(_6_t *);
  template <typename _t>
  _t &as() {
    return as((_t *)nullptr);
  }
  _0_t const *as_ptr(_0_t *) const;
  _1_t const *as_ptr(_1_t *) const;
  _2_t const *as_ptr(_2_t *) const;
  _3_t const *as_ptr(_3_t *) const;
  _4_t const *as_ptr(_4_t *) const;
  _5_t const *as_ptr(_5_t *) const;
  _6_t const *as_ptr(_6_t *) const;
  template <typename _t>
  _t const *as_ptr() const {
    return as_ptr((_t *)nullptr);
  }
  _0_t *as_ptr(_0_t *);
  _1_t *as_ptr(_1_t *);
  _2_t *as_ptr(_2_t *);
  _3_t *as_ptr(_3_t *);
  _4_t *as_ptr(_4_t *);
  _5_t *as_ptr(_5_t *);
  _6_t *as_ptr(_6_t *);
  template <typename _t>
  _t *as_ptr() {
    return as_ptr((_t *)nullptr);
  }
  template <typename _f>
  decltype(auto) visit(_f const &f) {
    switch (current) {
    case 0:
      return f(*member_0);
    case 1:
      return f(*member_1);
    case 2:
      return f(*member_2);
    case 3:
      return f(*member_3);
    case 4:
      return f(*member_4);
    case 5:
      return f(*member_5);
    case 6:
      return f(*member_6);
    default:
      __builtin_unreachable();
    }
  }
  template <typename _f>
  decltype(auto) visit(_f const &f) const {
    switch (current) {
    case 0:
      return f(*member_0);
    case 1:
      return f(*member_1);
    case 2:
      return f(*member_2);
    case 3:
      return f(*member_3);
    case 4:
      return f(*member_4);
    case 5:
      return f(*member_5);
    case 6:
      return f(*member_6);
    default:
      __builtin_unreachable();
    }
  }
  ~heap_variant_t();
  size_t current;
  union {
    _0_t *member_0;
    _1_t *member_1;
    _2_t *member_2;
    _3_t *member_3;
    _4_t *member_4;
    _5_t *member_5;
    _6_t *member_6;
  };
};
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t>
struct heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t> {
  heap_variant_t(heap_variant_t const &);
  heap_variant_t(heap_variant_t &&);
  heap_variant_t &operator=(heap_variant_t const &);
  heap_variant_t &operator=(heap_variant_t &&);
  heap_variant_t(_0_t const &x);
  heap_variant_t(_1_t const &x);
  heap_variant_t(_2_t const &x);
  heap_variant_t(_3_t const &x);
  heap_variant_t(_4_t const &x);
  heap_variant_t(_5_t const &x);
  heap_variant_t(_6_t const &x);
  heap_variant_t(_7_t const &x);
  heap_variant_t(_0_t &&x);
  heap_variant_t(_1_t &&x);
  heap_variant_t(_2_t &&x);
  heap_variant_t(_3_t &&x);
  heap_variant_t(_4_t &&x);
  heap_variant_t(_5_t &&x);
  heap_variant_t(_6_t &&x);
  heap_variant_t(_7_t &&x);
  bool is(_0_t *) const;
  bool is(_1_t *) const;
  bool is(_2_t *) const;
  bool is(_3_t *) const;
  bool is(_4_t *) const;
  bool is(_5_t *) const;
  bool is(_6_t *) const;
  bool is(_7_t *) const;
  template <typename _t>
  bool is() const {
    return is((_t *)nullptr);
  }
  _0_t const &as(_0_t *) const;
  _1_t const &as(_1_t *) const;
  _2_t const &as(_2_t *) const;
  _3_t const &as(_3_t *) const;
  _4_t const &as(_4_t *) const;
  _5_t const &as(_5_t *) const;
  _6_t const &as(_6_t *) const;
  _7_t const &as(_7_t *) const;
  template <typename _t>
  _t const &as() const {
    return as((_t *)nullptr);
  }
  _0_t &as(_0_t *);
  _1_t &as(_1_t *);
  _2_t &as(_2_t *);
  _3_t &as(_3_t *);
  _4_t &as(_4_t *);
  _5_t &as(_5_t *);
  _6_t &as(_6_t *);
  _7_t &as(_7_t *);
  template <typename _t>
  _t &as() {
    return as((_t *)nullptr);
  }
  _0_t const *as_ptr(_0_t *) const;
  _1_t const *as_ptr(_1_t *) const;
  _2_t const *as_ptr(_2_t *) const;
  _3_t const *as_ptr(_3_t *) const;
  _4_t const *as_ptr(_4_t *) const;
  _5_t const *as_ptr(_5_t *) const;
  _6_t const *as_ptr(_6_t *) const;
  _7_t const *as_ptr(_7_t *) const;
  template <typename _t>
  _t const *as_ptr() const {
    return as_ptr((_t *)nullptr);
  }
  _0_t *as_ptr(_0_t *);
  _1_t *as_ptr(_1_t *);
  _2_t *as_ptr(_2_t *);
  _3_t *as_ptr(_3_t *);
  _4_t *as_ptr(_4_t *);
  _5_t *as_ptr(_5_t *);
  _6_t *as_ptr(_6_t *);
  _7_t *as_ptr(_7_t *);
  template <typename _t>
  _t *as_ptr() {
    return as_ptr((_t *)nullptr);
  }
  template <typename _f>
  decltype(auto) visit(_f const &f) {
    switch (current) {
    case 0:
      return f(*member_0);
    case 1:
      return f(*member_1);
    case 2:
      return f(*member_2);
    case 3:
      return f(*member_3);
    case 4:
      return f(*member_4);
    case 5:
      return f(*member_5);
    case 6:
      return f(*member_6);
    case 7:
      return f(*member_7);
    default:
      __builtin_unreachable();
    }
  }
  template <typename _f>
  decltype(auto) visit(_f const &f) const {
    switch (current) {
    case 0:
      return f(*member_0);
    case 1:
      return f(*member_1);
    case 2:
      return f(*member_2);
    case 3:
      return f(*member_3);
    case 4:
      return f(*member_4);
    case 5:
      return f(*member_5);
    case 6:
      return f(*member_6);
    case 7:
      return f(*member_7);
    default:
      __builtin_unreachable();
    }
  }
  ~heap_variant_t();
  size_t current;
  union {
    _0_t *member_0;
    _1_t *member_1;
    _2_t *member_2;
    _3_t *member_3;
    _4_t *member_4;
    _5_t *member_5;
    _6_t *member_6;
    _7_t *member_7;
  };
};
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
struct heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t> {
  heap_variant_t(heap_variant_t const &);
  heap_variant_t(heap_variant_t &&);
  heap_variant_t &operator=(heap_variant_t const &);
  heap_variant_t &operator=(heap_variant_t &&);
  heap_variant_t(_0_t const &x);
  heap_variant_t(_1_t const &x);
  heap_variant_t(_2_t const &x);
  heap_variant_t(_3_t const &x);
  heap_variant_t(_4_t const &x);
  heap_variant_t(_5_t const &x);
  heap_variant_t(_6_t const &x);
  heap_variant_t(_7_t const &x);
  heap_variant_t(_8_t const &x);
  heap_variant_t(_0_t &&x);
  heap_variant_t(_1_t &&x);
  heap_variant_t(_2_t &&x);
  heap_variant_t(_3_t &&x);
  heap_variant_t(_4_t &&x);
  heap_variant_t(_5_t &&x);
  heap_variant_t(_6_t &&x);
  heap_variant_t(_7_t &&x);
  heap_variant_t(_8_t &&x);
  bool is(_0_t *) const;
  bool is(_1_t *) const;
  bool is(_2_t *) const;
  bool is(_3_t *) const;
  bool is(_4_t *) const;
  bool is(_5_t *) const;
  bool is(_6_t *) const;
  bool is(_7_t *) const;
  bool is(_8_t *) const;
  template <typename _t>
  bool is() const {
    return is((_t *)nullptr);
  }
  _0_t const &as(_0_t *) const;
  _1_t const &as(_1_t *) const;
  _2_t const &as(_2_t *) const;
  _3_t const &as(_3_t *) const;
  _4_t const &as(_4_t *) const;
  _5_t const &as(_5_t *) const;
  _6_t const &as(_6_t *) const;
  _7_t const &as(_7_t *) const;
  _8_t const &as(_8_t *) const;
  template <typename _t>
  _t const &as() const {
    return as((_t *)nullptr);
  }
  _0_t &as(_0_t *);
  _1_t &as(_1_t *);
  _2_t &as(_2_t *);
  _3_t &as(_3_t *);
  _4_t &as(_4_t *);
  _5_t &as(_5_t *);
  _6_t &as(_6_t *);
  _7_t &as(_7_t *);
  _8_t &as(_8_t *);
  template <typename _t>
  _t &as() {
    return as((_t *)nullptr);
  }
  _0_t const *as_ptr(_0_t *) const;
  _1_t const *as_ptr(_1_t *) const;
  _2_t const *as_ptr(_2_t *) const;
  _3_t const *as_ptr(_3_t *) const;
  _4_t const *as_ptr(_4_t *) const;
  _5_t const *as_ptr(_5_t *) const;
  _6_t const *as_ptr(_6_t *) const;
  _7_t const *as_ptr(_7_t *) const;
  _8_t const *as_ptr(_8_t *) const;
  template <typename _t>
  _t const *as_ptr() const {
    return as_ptr((_t *)nullptr);
  }
  _0_t *as_ptr(_0_t *);
  _1_t *as_ptr(_1_t *);
  _2_t *as_ptr(_2_t *);
  _3_t *as_ptr(_3_t *);
  _4_t *as_ptr(_4_t *);
  _5_t *as_ptr(_5_t *);
  _6_t *as_ptr(_6_t *);
  _7_t *as_ptr(_7_t *);
  _8_t *as_ptr(_8_t *);
  template <typename _t>
  _t *as_ptr() {
    return as_ptr((_t *)nullptr);
  }
  template <typename _f>
  decltype(auto) visit(_f const &f) {
    switch (current) {
    case 0:
      return f(*member_0);
    case 1:
      return f(*member_1);
    case 2:
      return f(*member_2);
    case 3:
      return f(*member_3);
    case 4:
      return f(*member_4);
    case 5:
      return f(*member_5);
    case 6:
      return f(*member_6);
    case 7:
      return f(*member_7);
    case 8:
      return f(*member_8);
    default:
      __builtin_unreachable();
    }
  }
  template <typename _f>
  decltype(auto) visit(_f const &f) const {
    switch (current) {
    case 0:
      return f(*member_0);
    case 1:
      return f(*member_1);
    case 2:
      return f(*member_2);
    case 3:
      return f(*member_3);
    case 4:
      return f(*member_4);
    case 5:
      return f(*member_5);
    case 6:
      return f(*member_6);
    case 7:
      return f(*member_7);
    case 8:
      return f(*member_8);
    default:
      __builtin_unreachable();
    }
  }
  ~heap_variant_t();
  size_t current;
  union {
    _0_t *member_0;
    _1_t *member_1;
    _2_t *member_2;
    _3_t *member_3;
    _4_t *member_4;
    _5_t *member_5;
    _6_t *member_6;
    _7_t *member_7;
    _8_t *member_8;
  };
};
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t,
          typename _9_t>
struct heap_variant_t<_0_t,
                      _1_t,
                      _2_t,
                      _3_t,
                      _4_t,
                      _5_t,
                      _6_t,
                      _7_t,
                      _8_t,
                      _9_t> {
  heap_variant_t(heap_variant_t const &);
  heap_variant_t(heap_variant_t &&);
  heap_variant_t &operator=(heap_variant_t const &);
  heap_variant_t &operator=(heap_variant_t &&);
  heap_variant_t(_0_t const &x);
  heap_variant_t(_1_t const &x);
  heap_variant_t(_2_t const &x);
  heap_variant_t(_3_t const &x);
  heap_variant_t(_4_t const &x);
  heap_variant_t(_5_t const &x);
  heap_variant_t(_6_t const &x);
  heap_variant_t(_7_t const &x);
  heap_variant_t(_8_t const &x);
  heap_variant_t(_9_t const &x);
  heap_variant_t(_0_t &&x);
  heap_variant_t(_1_t &&x);
  heap_variant_t(_2_t &&x);
  heap_variant_t(_3_t &&x);
  heap_variant_t(_4_t &&x);
  heap_variant_t(_5_t &&x);
  heap_variant_t(_6_t &&x);
  heap_variant_t(_7_t &&x);
  heap_variant_t(_8_t &&x);
  heap_variant_t(_9_t &&x);
  bool is(_0_t *) const;
  bool is(_1_t *) const;
  bool is(_2_t *) const;
  bool is(_3_t *) const;
  bool is(_4_t *) const;
  bool is(_5_t *) const;
  bool is(_6_t *) const;
  bool is(_7_t *) const;
  bool is(_8_t *) const;
  bool is(_9_t *) const;
  template <typename _t>
  bool is() const {
    return is((_t *)nullptr);
  }
  _0_t const &as(_0_t *) const;
  _1_t const &as(_1_t *) const;
  _2_t const &as(_2_t *) const;
  _3_t const &as(_3_t *) const;
  _4_t const &as(_4_t *) const;
  _5_t const &as(_5_t *) const;
  _6_t const &as(_6_t *) const;
  _7_t const &as(_7_t *) const;
  _8_t const &as(_8_t *) const;
  _9_t const &as(_9_t *) const;
  template <typename _t>
  _t const &as() const {
    return as((_t *)nullptr);
  }
  _0_t &as(_0_t *);
  _1_t &as(_1_t *);
  _2_t &as(_2_t *);
  _3_t &as(_3_t *);
  _4_t &as(_4_t *);
  _5_t &as(_5_t *);
  _6_t &as(_6_t *);
  _7_t &as(_7_t *);
  _8_t &as(_8_t *);
  _9_t &as(_9_t *);
  template <typename _t>
  _t &as() {
    return as((_t *)nullptr);
  }
  _0_t const *as_ptr(_0_t *) const;
  _1_t const *as_ptr(_1_t *) const;
  _2_t const *as_ptr(_2_t *) const;
  _3_t const *as_ptr(_3_t *) const;
  _4_t const *as_ptr(_4_t *) const;
  _5_t const *as_ptr(_5_t *) const;
  _6_t const *as_ptr(_6_t *) const;
  _7_t const *as_ptr(_7_t *) const;
  _8_t const *as_ptr(_8_t *) const;
  _9_t const *as_ptr(_9_t *) const;
  template <typename _t>
  _t const *as_ptr() const {
    return as_ptr((_t *)nullptr);
  }
  _0_t *as_ptr(_0_t *);
  _1_t *as_ptr(_1_t *);
  _2_t *as_ptr(_2_t *);
  _3_t *as_ptr(_3_t *);
  _4_t *as_ptr(_4_t *);
  _5_t *as_ptr(_5_t *);
  _6_t *as_ptr(_6_t *);
  _7_t *as_ptr(_7_t *);
  _8_t *as_ptr(_8_t *);
  _9_t *as_ptr(_9_t *);
  template <typename _t>
  _t *as_ptr() {
    return as_ptr((_t *)nullptr);
  }
  template <typename _f>
  decltype(auto) visit(_f const &f) {
    switch (current) {
    case 0:
      return f(*member_0);
    case 1:
      return f(*member_1);
    case 2:
      return f(*member_2);
    case 3:
      return f(*member_3);
    case 4:
      return f(*member_4);
    case 5:
      return f(*member_5);
    case 6:
      return f(*member_6);
    case 7:
      return f(*member_7);
    case 8:
      return f(*member_8);
    case 9:
      return f(*member_9);
    default:
      __builtin_unreachable();
    }
  }
  template <typename _f>
  decltype(auto) visit(_f const &f) const {
    switch (current) {
    case 0:
      return f(*member_0);
    case 1:
      return f(*member_1);
    case 2:
      return f(*member_2);
    case 3:
      return f(*member_3);
    case 4:
      return f(*member_4);
    case 5:
      return f(*member_5);
    case 6:
      return f(*member_6);
    case 7:
      return f(*member_7);
    case 8:
      return f(*member_8);
    case 9:
      return f(*member_9);
    default:
      __builtin_unreachable();
    }
  }
  ~heap_variant_t();
  size_t current;
  union {
    _0_t *member_0;
    _1_t *member_1;
    _2_t *member_2;
    _3_t *member_3;
    _4_t *member_4;
    _5_t *member_5;
    _6_t *member_6;
    _7_t *member_7;
    _8_t *member_8;
    _9_t *member_9;
  };
};
}//[mto.module-end]
namespace mto::no_stl::variant {//[mto.ns-compatibility]
  using namespace mto::no_stl::variant::heap_variant;//[mto]
}//[mto]
