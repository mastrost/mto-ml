#pragma once

//[mto-gen.begin]
namespace mto::no_stl::tools::static_for {
}
#include "cpp_tools/defines.h"
//[mto-gen.end]
//[mto]
namespace mto::no_stl::tools::static_for {//[mto.module-begin]

/**
 * Usage:
 * static_for_<begin, end>([&]<size_t i>() { });
 */
template <size_t begin, size_t end, typename on_index_t>
void static_for_(on_index_t const &on_index);

/**
 * Usage:
 * static_foreach<_ts...>([&]<typename _t>() { })
 */
template <typename... _ts, typename f_t>
void static_foreach(f_t const &f);

/**
 * Usage:
 * static_foreach_idx<_ts...>([&]<size_t idx, typename _t>() { })
 */
template <typename... _ts, typename f_t>
void static_foreach_idx(f_t const &f);

/**
 * Usage:
 * switch_type<_ts...>(3, [&]<typename _t>() { })
 */
template <typename... _ts, typename f_t>
void switch_type(size_t type_idx, f_t const &f);

/**
 * impl
 */
namespace impl {

template <size_t cur, typename... _ts>
struct static_foreach_idx_t;

template <size_t cur, typename _0_t, typename... _ts>
struct static_foreach_idx_t<cur, _0_t, _ts...> {
  template <typename f_t>
  static void apply(f_t const &f) {
    f.template operator()<cur, _0_t>();
    static_foreach_idx_t<cur + 1, _ts...>::apply(f);
  }
};

template <size_t cur>
struct static_foreach_idx_t<cur> {
  template <typename f_t>
  static void apply(f_t const &f) {
  }
};

}

template <size_t begin, size_t end, typename on_index_t>
void static_for_(on_index_t const &on_index) {
  if constexpr (begin < end) {
    on_index.template operator()<begin>();
    static_for_<begin + 1, end>(on_index);
  }
}

template <typename... _ts, typename f_t>
void static_foreach(f_t const &f) {
  let f_idx = [&]<size_t cur, typename _t>() {
    f.template operator()<_t>();
  };
  return static_foreach_idx<_ts...>(f_idx);
}

template <typename... _ts, typename f_t>
void static_foreach_idx(f_t const &f) {
  return impl::static_foreach_idx_t<0, _ts...>::apply(f);
}

template <typename... _ts, typename f_t>
void switch_type(size_t type_idx, f_t const &f) {
  let f_idx = [&]<size_t cur, typename _t>() {
    if (cur == type_idx) {
      f.template operator()<_t>();
    }
  };
  return static_foreach_idx<_ts...>(f_idx);
}

}//[mto.module-end]

namespace mto::no_stl::tools {//[mto.ns-compatibility]
  using namespace mto::no_stl::tools::static_for;//[mto]
}//[mto]
