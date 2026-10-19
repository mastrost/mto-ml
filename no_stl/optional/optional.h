#pragma once

//[mto.import ./uninitialized:uninitialized_t]
//[mto.import ../utility as utility]
#include "cpp_tools/contract.h"

//[mto-gen.begin]
#include "./uninitialized.h"
#include "./../utility.h"
namespace mto::no_stl::optional::optional {
using mto::no_stl::optional::uninitialized::uninitialized_t;
namespace utility = mto::no_stl::utility;
}
#include "cpp_tools/defines.h"
//[mto-gen.end]
//[mto]
namespace mto::no_stl::optional::optional {//[mto.module-begin]

struct nullopt_t {};
inline constexpr auto nullopt = nullopt_t{};

template <typename _t>
struct [[nodiscard]] optional_t {
  static constexpr auto nullopt = nullopt_t{};

  optional_t() : is_initialized(false) {
  }

  ~optional_t() {
    if (is_initialized) {
      value._delete();
    }
  }

  optional_t(optional_t const &x) : optional_t() {
    (*this) = x;
  }

  optional_t(optional_t &&x) : optional_t() {
    (*this) = utility::move(x);
  }

  void operator=(optional_t const &x) {
    if (x.is_initialized) {
      (*this) = *x;
    } else {
      (*this) = nullopt_t{};
    }
  }

  void operator=(optional_t &&x) {
    if (x.is_initialized) {
      (*this) = utility::move(*x);
    } else {
      (*this) = nullopt_t{};
    }
  }

  optional_t(nullopt_t const &x) : optional_t() {
    (*this) = x;
  }

  optional_t(_t const &x) : optional_t() {
    (*this) = x;
  }

  optional_t(_t &&x) : optional_t() {
    (*this) = utility::move(x);
  }

  template <typename _s>
  optional_t(optional_t<_s> const &o) : optional_t() {
    if (o)
      (*this) = *o;
  }

  void operator=(_t &&o) {
    if (!is_initialized) {
      value.move_initialize(utility::move(o));
      is_initialized = true;
    } else {
      value._delete();
      value.move_initialize(utility::move(o));
    }
  }

  void operator=(_t const &o) {
    if (!is_initialized) {
      value.copy_initialize(o);
      is_initialized = true;
    } else {
      value._delete();
      value.copy_initialize(o);
    }
  }

  void operator=(nullopt_t const &o) {
    if (is_initialized) {
      value._delete();
      is_initialized = false;
    }
  }

  _t &operator*() {
    REQUIRES(is_initialized);
    return *value.get();
  }

  _t const &operator*() const {
    REQUIRES(is_initialized);
    return *value.get();
  }

  _t *operator->() {
    REQUIRES(is_initialized);
    return value.get();
  }

  _t const *operator->() const {
    REQUIRES(is_initialized);
    return value.get();
  }

  explicit operator bool() const {
    return is_initialized;
  }

  bool operator==(optional_t const &o) const {
    if (!is_initialized && !o.is_initialized)
      return true;
    if (is_initialized != o.is_initialized)
      return false;
    return (**this) == *o;
  }

  bool operator<(optional_t const &o) const {
    if (!is_initialized && !o.is_initialized)
      return false;

    if (!is_initialized && o.is_initialized)
      return true;

    if (is_initialized && !o.is_initialized)
      return false;

    return (**this) < (*o);
  }

  bool operator!=(optional_t const &o) const {
    return !((*this) == o);
  }

  _t const *as_ptr() const {
    if (is_initialized) {
      return value.get();
    } else {
      return nullptr;
    }
  }

  _t *as_ptr() {
    if (is_initialized) {
      return value.get();
    } else {
      return nullptr;
    }
  }

  bool is_initialized;
  uninitialized_t<_t> value;
};

#ifdef IDE
template struct optional_t<int>;
#endif

/**
 * Warning!
 * Prefer not to use GET_OPT in sub expresssions.
 * In particular, a 'return' from the GET_OPT "expression statement"
 * may not call the destructors of variables of other sibling GET_OPT.
 * i.e. in the following example, the destructor of the variable returned
 * from 'f()' is never called when 'g()' returns an error.
 * return a_t {
 *   f(),
 *   GET_OPT(g()),
 * }
 */
#define MTO_NO_STL_OPTIONAL_NS \
mto::no_stl::optional::optional//[mto.module-namespace]

#define NOSTL_GET_OPT(expr)                   \
  ({                                          \
    let var##__res = (expr);                  \
    if (!(var##__res))                        \
      return MTO_NO_STL_OPTIONAL_NS::nullopt; \
    *var##__res;                              \
  })

}//[mto.module-end]

namespace mto::no_stl::optional {//[mto.ns-compatibility]
  using namespace mto::no_stl::optional::optional;//[mto]
}//[mto]
