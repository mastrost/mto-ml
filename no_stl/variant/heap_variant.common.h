#pragma once

//[mto-gen.begin]
namespace mto::no_stl::variant::heap_variant {
}
#include "cpp_tools/defines.h"
//[mto-gen.end]
//[mto]
namespace mto::no_stl::variant::heap_variant {//[mto.module-begin]
template <typename... _ts>
struct heap_variant_t;
}//[mto.module-end]
namespace mto::no_stl::variant {//[mto.ns-compatibility]
  using namespace mto::no_stl::variant::heap_variant;//[mto]
}//[mto]
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
