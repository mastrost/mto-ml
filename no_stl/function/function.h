#pragma once
//[mto.import no_stl/utility:enable_if_t,is_pointer_v]
//[mto.import no_stl/tools/function_traits:has_signature]

//[mto-gen.begin]
#include "no_stl/utility.h"
#include "no_stl/tools/function_traits.h"
namespace mto::no_stl::function::function {
using mto::no_stl::utility::enable_if_t;
using mto::no_stl::utility::is_pointer_v;
using mto::no_stl::tools::function_traits::has_signature;
}
#include "cpp_tools/defines.h"
//[mto-gen.end]
//[mto]
namespace mto::no_stl::function::function {//[mto.module-begin]

template <typename f_t>
struct function_t;

template <typename r_t, typename... p_ts>
struct function_t<r_t(p_ts...)> {
private:
  // Note: la vérification de la signature (pour message d'erreur
  //       compilateur et IDE a l'appelant), n'est pas compatible
  //       avec une fonction (ou lambda) template.
  template <typename f_t>
  static constexpr bool has_good_signature() {
    return has_signature<f_t, r_t, p_ts...>();
  }

  template <typename f_t>
  static constexpr bool has_good_non_pointer_signature() {
    if constexpr (is_pointer_v<f_t>)
      return false;
    else
      return has_good_signature<f_t>();
  }

public:
  // creation sans vérification de la signature depuis l'appelant
  template <typename f_t>
  static function_t create(f_t const &f) {
    return function_t(no_check_t{}, f);
  }

  template <typename f_t>
  static function_t create_from_ptr(f_t *p_f) {
    return function_t(ptr_no_check_t{}, p_f);
  }

  // creation avec vérification de la signature depuis l'appelant
  template <typename f_t, enable_if_t<has_good_non_pointer_signature<f_t>(), int>
                              dummy = 0>
  function_t(f_t const &f) : function_t(no_check_t{}, f) {
  }

  template <typename f_t, enable_if_t<has_good_signature<f_t>(), int>
                              dummy = 0>
  function_t(f_t *p_f) : function_t(ptr_no_check_t{}, p_f) {
  }

  function_t(function_t const &o) {
    p = o.p->copy();
  }
  void operator=(function_t const &o) {
    delete p;
    p = o.p->copy();
  }

  ~function_t() {
    delete p;
  }

  r_t operator()(p_ts... params) const {
    return p->call(params...);
  }

private:
  struct no_check_t {};
  struct ptr_no_check_t {};

  template <typename f_t>
  function_t(no_check_t, f_t const &f) {
    struct call_impl_t : callable_t {
      call_impl_t(f_t const &_f) : f(_f) {}

      r_t call(p_ts... params) {
        return f(params...);
      }

      callable_t *copy() {
        return new call_impl_t(f);
      }

      f_t f;
    };

    p = new call_impl_t(f);
  }

  template <typename f_t>
  function_t(ptr_no_check_t, f_t *p_f) {
    struct call_impl_t : callable_t {
      call_impl_t(f_t *&_f) : p_f(_f) {}

      r_t call(p_ts... params) {
        return (*p_f)(params...);
      }

      callable_t *copy() {
        return new call_impl_t(p_f);
      }

      f_t *p_f;
    };

    p = new call_impl_t(p_f);
  }

  struct callable_t {
    virtual r_t call(p_ts... params) = 0;
    virtual callable_t *copy() = 0;
    virtual ~callable_t(){};
  };
  callable_t *p;
};

template <typename f_t>
auto to_function(f_t *p) {
  let f = [p](auto... xs) {
    return (*p)(xs...);
  };
}

}//[mto.module-end]

namespace mto::no_stl::function {//[mto.ns-compatibility]
  using namespace mto::no_stl::function::function;//[mto]
}//[mto]
