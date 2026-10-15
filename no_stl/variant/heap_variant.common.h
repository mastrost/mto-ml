#pragma once

namespace mto::no_stl::variant::heap_variant {
}
#include "cpp_tools/defines.h"
namespace mto::no_stl::variant::heap_variant {
template <typename... _ts>
struct heap_variant_t;
}
namespace mto::no_stl::variant {
  using namespace mto::no_stl::variant::heap_variant;
}
template <typename T>
struct _remove_reference {
  typedef T type;
};
template <typename T>
struct _remove_reference<T &> {
  typedef T type;
};
template <typename T>
struct _remove_reference<T &&> {
  typedef T type;
};
template <typename T>
constexpr typename _remove_reference<T>::type &&
_move(T &&arg) noexcept {
  return static_cast<typename _remove_reference<T>::type &&>(arg);
}
