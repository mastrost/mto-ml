#pragma once

//[mto.import no_stl/optional/optional:optional_t]
//[mto.import no_stl/utility]
#include "cpp_tools/contract.h"

//[mto-gen.begin]
#include "no_stl/optional/optional.h"
#include "no_stl/utility.h"
namespace mto::no_stl::result::result {
using mto::no_stl::optional::optional::optional_t;
namespace utility = mto::no_stl::utility;
}
#include "cpp_tools/defines.h"
//[mto-gen.end]
//[mto]
namespace mto::no_stl::result::result {//[mto.module-begin]

template <typename _t, typename error_t>
struct [[nodiscard]] result_t {
  result_t(result_t const &o) : opt_success(o.opt_success), opt_error(o.opt_error) {}
  result_t(result_t &&o) : opt_success(utility::move(o.opt_success)), opt_error(utility::move(o.opt_error)) {}

  result_t(_t const &x) : opt_success(x) {}
  result_t(_t &&x) : opt_success(utility::move(x)) {}
  result_t(error_t const &e) : opt_error(e) {}
  result_t(error_t &&e) : opt_error(utility::move(e)) {}

  result_t &operator=(result_t const &o) {
    opt_success = o.opt_success;
    opt_error = o.opt_error;
    return *this;
  }

  result_t &operator=(result_t &&o) {
    opt_success = utility::move(o.opt_success);
    opt_error = utility::move(o.opt_error);
    return *this;
  }

  _t &operator*() & {
    REQUIRES(opt_success);
    return *opt_success;
  }

  _t &&operator*() && {
    REQUIRES(opt_success);
    return utility::move(*opt_success);
  }

  _t const &operator*() const & {
    REQUIRES(opt_success);
    return *opt_success;
  }

  _t const &get() const {
    REQUIRES(opt_success);
    return *opt_success;
  }

  error_t const &get_error() const {
    REQUIRES(opt_error);
    return *opt_error;
  }

  _t const *get_ptr() const {
    if (opt_success)
      return &(*opt_success);
    else
      return nullptr;
  }

  error_t const *get_error_ptr() const {
    if (opt_error)
      return &(*opt_error);
    else
      return nullptr;
  }

  explicit operator bool() const {
    return bool(opt_success);
  }

  // TODO: use a stack variant
  optional_t<_t> opt_success;
  optional_t<error_t> opt_error;
};

/**
 * Warning!
 * Prefer not to use GET_RES in sub expresssions.
 * In particular, a 'return' from the GET_RES "expression statement"
 * may not call the destructors of variables of other sibling GET_RES.
 * i.e. in the following example, the destructor of the variable returned
 * from 'f()' is never called when 'g()' returns an error.
 * return a_t {
 *   f(),
 *   GET_RES(g()),
 * }
 */
#define GET_RES(expr)                \
  ({                                 \
    let var##__res = (expr);         \
    if (!(var##__res))               \
      return var##__res.get_error(); \
    *var##__res;                     \
  })

// idem GET_RES, avec enrichissement/conversion de l'erreur
// error := (error_expr)(error)
#define GET_RES_EXT(expr, error_expr)              \
  ({                                               \
    let var##__res = (expr);                       \
    if (!(var##__res))                             \
      return (error_expr)(var##__res.get_error()); \
    *var##__res;                                   \
  })

}//[mto.module-end]

namespace mto::no_stl::result {//[mto.ns-compatibility]
  using namespace mto::no_stl::result::result;//[mto]
}//[mto]
