#pragma once

//[mto-gen.begin]
namespace mto::no_stl::utility {
}
#include "cpp_tools/defines.h"
//[mto-gen.end]
//[mto]
namespace mto::no_stl::utility {//[mto.module-begin]

#define NO_STL_UTILITY_NS \
mto::no_stl::utility//[mto.module-namespace]

template <typename... _ts>
struct type_list_t {
};

/**
 * remove_reference
 */
template <typename T>
struct remove_reference {
  typedef T type;
};

template <typename T>
struct remove_reference<T &> {
  typedef T type;
};

template <typename T>
struct remove_reference<T &&> {
  typedef T type;
};

template <class T>
using remove_reference_t = typename remove_reference<T>::type;

template <typename T>
constexpr typename remove_reference<T>::type &&
move(T &&arg) noexcept {
  return static_cast<typename remove_reference<T>::type &&>(arg);
}

template <class T>
inline T &&forward(typename remove_reference<T>::type &t) noexcept {
  return static_cast<T &&>(t);
}

template <class T>
inline T &&forward(typename remove_reference<T>::type &&t) noexcept {
  return static_cast<T &&>(t);
}

/**
 * remove_cv
 */
template <class T>
struct remove_cv { typedef T type; };
template <class T>
struct remove_cv<const T> { typedef T type; };
template <class T>
struct remove_cv<volatile T> { typedef T type; };
template <class T>
struct remove_cv<const volatile T> { typedef T type; };

template <class T>
using remove_cv_t = typename remove_cv<T>::type;

template <class T>
struct remove_const { typedef T type; };
template <class T>
struct remove_const<const T> { typedef T type; };

template <class T>
struct remove_volatile { typedef T type; };
template <class T>
struct remove_volatile<volatile T> { typedef T type; };

/**
 * is_pointer
 */
template <typename _t>
struct is_pointer;

template <typename _t>
struct is_pointer {
  static constexpr bool value = false;
};

template <typename _t>
struct is_pointer<_t *> {
  static constexpr bool value = true;
};

template <typename _t>
inline auto constexpr is_pointer_v = is_pointer<_t>::value;

/**
 * is_same
 */
template <typename T0, typename T1>
struct is_same { static bool constexpr value = false; };
template <typename T>
struct is_same<T, T> { static bool constexpr value = true; };

template <typename _t, typename _s>
inline auto constexpr is_same_v = is_same<_t, _s>::value;

/**
 * enable_if
 */
template <bool allowed, typename forward_type>
struct enable_if;

template <typename forward_type>
struct enable_if<false, forward_type> {};

template <typename forward_type>
struct enable_if<true, forward_type> {
  typedef forward_type type;
};

template <bool allowed, typename forward_type = void>
using enable_if_t = typename enable_if<allowed, forward_type>::type;

/**
 * is_complete_type
 */
template <typename _t>
constexpr bool is_complete_type();

namespace impl {
template <typename _t>
constexpr auto _is_complete_type(...) -> bool {
  return false;
}

template <typename _t>
constexpr auto _is_complete_type(int) -> decltype(decltype(sizeof(_t))(), bool()) {
  return true;
}
}

template <typename _t>
constexpr bool is_complete_type() {
  return impl::_is_complete_type<_t>(0);
}

template <typename _t, typename match_t = void>
using enable_if_complete_t = enable_if_t<is_complete_type<_t>(), match_t>;

#define TYPE_MAP_APPEND(DST, SRC)                                              \
  template <typename _t>                                                       \
  struct DST<_t, NO_STL_UTILITY_NS::enable_if_complete_t<SRC<_t>>> : SRC<_t> { \
  }

/**
 * is_template_instance_v
 * ex: is_template_instance_v<vector_t<int>, vector_t>
 */
template <typename _t,
          template <typename...> typename _template>
struct is_template_instance_t {
  static constexpr auto value = false;
};

template <template <typename...> typename _template,
          typename elt_t, typename... _ts>
struct is_template_instance_t<_template<elt_t, _ts...>, _template> {
  static constexpr auto value = true;
};

template <
    typename _t,
    template <typename...> typename _template>
inline auto constexpr is_template_instance_v = is_template_instance_t<_t, _template>::value;

/**
 * test if template type is specialized for given type
 */

template <template <typename...> class template_type, typename... _t>
constexpr bool is_specialized_for() {
  return is_complete_type<template_type<_t...>>();
}

/**
 * For variant visitors
 */
#define IS_A(_value_, _base_t) \
  no_stl::is_same<             \
      typename no_stl::remove_cv_t<no_stl::remove_reference_t<decltype(_value_)>>, _base_t>::value

/**
 * for static_assert(false)
 */
template <typename _t>
struct false_t {
  constexpr operator bool() {
    return false;
  }
};

/**
 */

template <typename _t, _t i>
struct integral_constant {
  static constexpr _t value = i;
};

template <typename _t, _t i>
constexpr auto integral_constant_v = integral_constant<_t, i>::value;

/**********************************************************
 * parameter pack helpers:
 *********************************************************/

template <size_t index, typename... _ts>
struct get_parameter_pack_type;

template <size_t index, typename... _ts>
using get_parameter_pack_type_t = typename get_parameter_pack_type<index, _ts...>::type;

template <typename head_t, typename... _ts>
struct get_parameter_pack_type<0, head_t, _ts...> {
  typedef head_t type;
};

template <size_t index, typename head_t, typename... _ts>
struct get_parameter_pack_type<index, head_t, _ts...> {
  typedef get_parameter_pack_type_t<index - 1, _ts...> type;
};

/**
 * type_sequence_t (describe a parameter pack in single type)
 */
template <typename... _ts>
struct type_sequence_t {};

template <size_t index, typename type_sequence_t>
struct get_type_sequence_type;

template <size_t index, typename type_sequence_t>
using get_type_sequence_type_t = typename get_type_sequence_type<index, type_sequence_t>::type;

template <size_t index, typename... _ts>
struct get_type_sequence_type<index, type_sequence_t<_ts...>> {
  typedef get_parameter_pack_type_t<index, _ts...> type;
};

/**
 * integer/index sequence
 */
template <class T, T... Ints>
class integer_sequence {};

template <std::size_t... Ints>
using index_sequence = integer_sequence<std::size_t, Ints...>;

template <size_t cur, size_t size, size_t... head>
struct make_index_sequence_impl {
  typedef typename make_index_sequence_impl<cur + 1, size, head..., cur>::type type;
};

template <size_t size, size_t... head>
struct make_index_sequence_impl<size, size, head...> {
  typedef index_sequence<head...> type;
};

template <size_t size>
using make_index_sequence = typename make_index_sequence_impl<0, size>::type;

template <class... T>
using index_sequence_for = make_index_sequence<sizeof...(T)>;

}//[mto.ns_end]

namespace mto::no_stl {//[mto.ns-compatibility]
  using namespace mto::no_stl::utility;//[mto]
}//[mto]
