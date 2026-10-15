#pragma once

//[mto.import no_stl/utility:,type_list_t,is_same_v]

//[mto-gen.begin]
#include "no_stl/utility.h"
namespace mto::no_stl::tools::function_traits {
namespace utility = mto::no_stl::utility;
using mto::no_stl::utility::type_list_t;
using mto::no_stl::utility::is_same_v;
}
#include "cpp_tools/defines.h"
//[mto-gen.end]
//[mto]
namespace mto::no_stl::tools::function_traits {//[mto.module-begin]

template <typename _t>
constexpr bool is_functor();

/**
 * function_traits_t {
 *   typedef type_list_t<...> parameters_t;
 *   typedef r_t result_t;
 * }
 */
template <typename f_t, typename match = int>
struct function_traits_t;

template <typename r_t, typename... p_t>
struct function_traits_t<r_t(p_t...)> {
  typedef type_list_t<p_t...> parameters_t;
  typedef r_t result_t;
};

template <typename r_t, typename... p_t>
struct function_traits_t<r_t (*)(p_t...)> {
  typedef type_list_t<p_t...> parameters_t;
  typedef r_t result_t;
};

template <typename r_t, typename obj_t, typename... p_t>
struct function_traits_t<r_t (obj_t::*)(p_t...)> {
  typedef type_list_t<p_t...> parameters_t;
  typedef r_t result_t;
};

template <typename r_t, typename obj_t, typename... p_t>
struct function_traits_t<r_t (obj_t::*)(p_t...) const> {
  typedef type_list_t<p_t...> parameters_t;
  typedef r_t result_t;
};

template <typename f_t>
struct function_traits_t<f_t, enable_if_t<is_functor<f_t>(), int>> {
  typedef decltype((&f_t::operator())) call_type;

  typedef typename function_traits_t<call_type>::parameters_t parameters_t;
  typedef typename function_traits_t<call_type>::result_t result_t;
};

/**
 */
template <typename f_t, typename r_t, typename... p_ts>
constexpr bool has_signature() {
  if constexpr (is_complete_type<function_traits_t<f_t>>()) {
    typedef typename function_traits_t<f_t>::result_t result_t;
    typedef typename function_traits_t<f_t>::parameters_t params_t;
    let same_result = is_same_v<result_t, r_t>;
    let same_params = is_same_v<params_t, type_list_t<p_ts...>>;
    return same_result && same_params;
  } else {
    return false;
  }
}

/**
 * impl
 */
namespace impl {

template <typename f_t>
constexpr auto is_functor(...) -> bool {
  return false;
}

template <typename f_t>
constexpr auto is_functor(int) -> decltype(decltype((&f_t::operator()))(), bool()) {
  return true;
}

}

template <typename _t>
constexpr bool is_functor() {
  return impl::is_functor<_t>(0);
}

}//[mto.module-end]
