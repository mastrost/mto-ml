#pragma once
#include "./heap_variant.h"

// clang-format off
#define NO_STL_HEAP_VARIANT_NS \
mto::no_stl::variant::heap_variant//[mto.module-namespace]
// clang-format on

#define INSTANCIATE_HEAP_VARIANT(...) \
  template struct NO_STL_HEAP_VARIANT_NS::heap_variant_t<__VA_ARGS__>

//[mto-gen.begin]
namespace mto::no_stl::variant::heap_variant {
}
#include "cpp_tools/defines.h"
//[mto-gen.end]
//[mto]
namespace mto::no_stl::variant::heap_variant {//[mto.module-begin]
template <typename _0_t>
heap_variant_t<_0_t>::heap_variant_t(heap_variant_t const &o)
    : current(o.current) {
  switch (current) {
  case 0:
    member_0 = new _0_t(*o.member_0);
    break;
  }
}
template <typename _0_t>
heap_variant_t<_0_t>::heap_variant_t(heap_variant_t &&o)
    : current(o.current) {
  switch (current) {
  case 0:
    member_0 = new _0_t(_move(*o.member_0));
    break;
  }
}
template <typename _0_t>
heap_variant_t<_0_t> &
heap_variant_t<_0_t>::operator=(heap_variant_t const &o) {
  switch (current) {
  case 0:
    delete member_0;
    break;
  };
  current = o.current;
  switch (current) {
  case 0:
    member_0 = new _0_t(*o.member_0);
    break;
  };
  return *this;
}
template <typename _0_t>
heap_variant_t<_0_t> &
heap_variant_t<_0_t>::operator=(heap_variant_t &&o) {
  switch (current) {
  case 0:
    delete member_0;
    break;
  };
  current = o.current;
  switch (current) {
  case 0:
    member_0 = new _0_t(_move(*o.member_0));
    break;
  };
  return *this;
}
template <typename _0_t>
heap_variant_t<_0_t>::heap_variant_t(_0_t const &x)
    : current(0), member_0(new _0_t(x)) {
}
template <typename _0_t>
heap_variant_t<_0_t>::heap_variant_t(_0_t &&x)
    : current(0), member_0(new _0_t(_move(x))) {
}
template <typename _0_t>
bool heap_variant_t<_0_t>::is(_0_t *) const {
  return current == 0;
}
template <typename _0_t>
_0_t const &
heap_variant_t<_0_t>::as(_0_t *) const {
  return *member_0;
}
template <typename _0_t>
_0_t &
heap_variant_t<_0_t>::as(_0_t *) {
  return *member_0;
}
template <typename _0_t>
_0_t const *
heap_variant_t<_0_t>::as_ptr(_0_t *) const {
  if (current != 0)
    return nullptr;
  return member_0;
}
template <typename _0_t>
_0_t *
heap_variant_t<_0_t>::as_ptr(_0_t *) {
  if (current != 0)
    return nullptr;
  return member_0;
}
template <typename _0_t>
heap_variant_t<_0_t>::~heap_variant_t() {
  switch (current) {
  case 0:
    delete member_0;
    break;
  };
}
template <typename _0_t, typename _1_t>
heap_variant_t<_0_t, _1_t>::heap_variant_t(heap_variant_t const &o)
    : current(o.current) {
  switch (current) {
  case 0:
    member_0 = new _0_t(*o.member_0);
    break;
  case 1:
    member_1 = new _1_t(*o.member_1);
    break;
  }
}
template <typename _0_t, typename _1_t>
heap_variant_t<_0_t, _1_t>::heap_variant_t(heap_variant_t &&o)
    : current(o.current) {
  switch (current) {
  case 0:
    member_0 = new _0_t(_move(*o.member_0));
    break;
  case 1:
    member_1 = new _1_t(_move(*o.member_1));
    break;
  }
}
template <typename _0_t, typename _1_t>
heap_variant_t<_0_t, _1_t> &
heap_variant_t<_0_t, _1_t>::operator=(heap_variant_t const &o) {
  switch (current) {
  case 0:
    delete member_0;
    break;
  case 1:
    delete member_1;
    break;
  };
  current = o.current;
  switch (current) {
  case 0:
    member_0 = new _0_t(*o.member_0);
    break;
  case 1:
    member_1 = new _1_t(*o.member_1);
    break;
  };
  return *this;
}
template <typename _0_t, typename _1_t>
heap_variant_t<_0_t, _1_t> &
heap_variant_t<_0_t, _1_t>::operator=(heap_variant_t &&o) {
  switch (current) {
  case 0:
    delete member_0;
    break;
  case 1:
    delete member_1;
    break;
  };
  current = o.current;
  switch (current) {
  case 0:
    member_0 = new _0_t(_move(*o.member_0));
    break;
  case 1:
    member_1 = new _1_t(_move(*o.member_1));
    break;
  };
  return *this;
}
template <typename _0_t, typename _1_t>
heap_variant_t<_0_t, _1_t>::heap_variant_t(_0_t const &x)
    : current(0), member_0(new _0_t(x)) {
}
template <typename _0_t, typename _1_t>
heap_variant_t<_0_t, _1_t>::heap_variant_t(_1_t const &x)
    : current(1), member_1(new _1_t(x)) {
}
template <typename _0_t, typename _1_t>
heap_variant_t<_0_t, _1_t>::heap_variant_t(_0_t &&x)
    : current(0), member_0(new _0_t(_move(x))) {
}
template <typename _0_t, typename _1_t>
heap_variant_t<_0_t, _1_t>::heap_variant_t(_1_t &&x)
    : current(1), member_1(new _1_t(_move(x))) {
}
template <typename _0_t, typename _1_t>
bool heap_variant_t<_0_t, _1_t>::is(_0_t *) const {
  return current == 0;
}
template <typename _0_t, typename _1_t>
bool heap_variant_t<_0_t, _1_t>::is(_1_t *) const {
  return current == 1;
}
template <typename _0_t, typename _1_t>
_0_t const &
heap_variant_t<_0_t, _1_t>::as(_0_t *) const {
  return *member_0;
}
template <typename _0_t, typename _1_t>
_1_t const &
heap_variant_t<_0_t, _1_t>::as(_1_t *) const {
  return *member_1;
}
template <typename _0_t, typename _1_t>
_0_t &
heap_variant_t<_0_t, _1_t>::as(_0_t *) {
  return *member_0;
}
template <typename _0_t, typename _1_t>
_1_t &
heap_variant_t<_0_t, _1_t>::as(_1_t *) {
  return *member_1;
}
template <typename _0_t, typename _1_t>
_0_t const *
heap_variant_t<_0_t, _1_t>::as_ptr(_0_t *) const {
  if (current != 0)
    return nullptr;
  return member_0;
}
template <typename _0_t, typename _1_t>
_1_t const *
heap_variant_t<_0_t, _1_t>::as_ptr(_1_t *) const {
  if (current != 1)
    return nullptr;
  return member_1;
}
template <typename _0_t, typename _1_t>
_0_t *
heap_variant_t<_0_t, _1_t>::as_ptr(_0_t *) {
  if (current != 0)
    return nullptr;
  return member_0;
}
template <typename _0_t, typename _1_t>
_1_t *
heap_variant_t<_0_t, _1_t>::as_ptr(_1_t *) {
  if (current != 1)
    return nullptr;
  return member_1;
}
template <typename _0_t, typename _1_t>
heap_variant_t<_0_t, _1_t>::~heap_variant_t() {
  switch (current) {
  case 0:
    delete member_0;
    break;
  case 1:
    delete member_1;
    break;
  };
}
template <typename _0_t, typename _1_t, typename _2_t>
heap_variant_t<_0_t, _1_t, _2_t>::heap_variant_t(heap_variant_t const &o)
    : current(o.current) {
  switch (current) {
  case 0:
    member_0 = new _0_t(*o.member_0);
    break;
  case 1:
    member_1 = new _1_t(*o.member_1);
    break;
  case 2:
    member_2 = new _2_t(*o.member_2);
    break;
  }
}
template <typename _0_t, typename _1_t, typename _2_t>
heap_variant_t<_0_t, _1_t, _2_t>::heap_variant_t(heap_variant_t &&o)
    : current(o.current) {
  switch (current) {
  case 0:
    member_0 = new _0_t(_move(*o.member_0));
    break;
  case 1:
    member_1 = new _1_t(_move(*o.member_1));
    break;
  case 2:
    member_2 = new _2_t(_move(*o.member_2));
    break;
  }
}
template <typename _0_t, typename _1_t, typename _2_t>
heap_variant_t<_0_t, _1_t, _2_t> &
heap_variant_t<_0_t, _1_t, _2_t>::operator=(heap_variant_t const &o) {
  switch (current) {
  case 0:
    delete member_0;
    break;
  case 1:
    delete member_1;
    break;
  case 2:
    delete member_2;
    break;
  };
  current = o.current;
  switch (current) {
  case 0:
    member_0 = new _0_t(*o.member_0);
    break;
  case 1:
    member_1 = new _1_t(*o.member_1);
    break;
  case 2:
    member_2 = new _2_t(*o.member_2);
    break;
  };
  return *this;
}
template <typename _0_t, typename _1_t, typename _2_t>
heap_variant_t<_0_t, _1_t, _2_t> &
heap_variant_t<_0_t, _1_t, _2_t>::operator=(heap_variant_t &&o) {
  switch (current) {
  case 0:
    delete member_0;
    break;
  case 1:
    delete member_1;
    break;
  case 2:
    delete member_2;
    break;
  };
  current = o.current;
  switch (current) {
  case 0:
    member_0 = new _0_t(_move(*o.member_0));
    break;
  case 1:
    member_1 = new _1_t(_move(*o.member_1));
    break;
  case 2:
    member_2 = new _2_t(_move(*o.member_2));
    break;
  };
  return *this;
}
template <typename _0_t, typename _1_t, typename _2_t>
heap_variant_t<_0_t, _1_t, _2_t>::heap_variant_t(_0_t const &x)
    : current(0), member_0(new _0_t(x)) {
}
template <typename _0_t, typename _1_t, typename _2_t>
heap_variant_t<_0_t, _1_t, _2_t>::heap_variant_t(_1_t const &x)
    : current(1), member_1(new _1_t(x)) {
}
template <typename _0_t, typename _1_t, typename _2_t>
heap_variant_t<_0_t, _1_t, _2_t>::heap_variant_t(_2_t const &x)
    : current(2), member_2(new _2_t(x)) {
}
template <typename _0_t, typename _1_t, typename _2_t>
heap_variant_t<_0_t, _1_t, _2_t>::heap_variant_t(_0_t &&x)
    : current(0), member_0(new _0_t(_move(x))) {
}
template <typename _0_t, typename _1_t, typename _2_t>
heap_variant_t<_0_t, _1_t, _2_t>::heap_variant_t(_1_t &&x)
    : current(1), member_1(new _1_t(_move(x))) {
}
template <typename _0_t, typename _1_t, typename _2_t>
heap_variant_t<_0_t, _1_t, _2_t>::heap_variant_t(_2_t &&x)
    : current(2), member_2(new _2_t(_move(x))) {
}
template <typename _0_t, typename _1_t, typename _2_t>
bool heap_variant_t<_0_t, _1_t, _2_t>::is(_0_t *) const {
  return current == 0;
}
template <typename _0_t, typename _1_t, typename _2_t>
bool heap_variant_t<_0_t, _1_t, _2_t>::is(_1_t *) const {
  return current == 1;
}
template <typename _0_t, typename _1_t, typename _2_t>
bool heap_variant_t<_0_t, _1_t, _2_t>::is(_2_t *) const {
  return current == 2;
}
template <typename _0_t, typename _1_t, typename _2_t>
_0_t const &
heap_variant_t<_0_t, _1_t, _2_t>::as(_0_t *) const {
  return *member_0;
}
template <typename _0_t, typename _1_t, typename _2_t>
_1_t const &
heap_variant_t<_0_t, _1_t, _2_t>::as(_1_t *) const {
  return *member_1;
}
template <typename _0_t, typename _1_t, typename _2_t>
_2_t const &
heap_variant_t<_0_t, _1_t, _2_t>::as(_2_t *) const {
  return *member_2;
}
template <typename _0_t, typename _1_t, typename _2_t>
_0_t &
heap_variant_t<_0_t, _1_t, _2_t>::as(_0_t *) {
  return *member_0;
}
template <typename _0_t, typename _1_t, typename _2_t>
_1_t &
heap_variant_t<_0_t, _1_t, _2_t>::as(_1_t *) {
  return *member_1;
}
template <typename _0_t, typename _1_t, typename _2_t>
_2_t &
heap_variant_t<_0_t, _1_t, _2_t>::as(_2_t *) {
  return *member_2;
}
template <typename _0_t, typename _1_t, typename _2_t>
_0_t const *
heap_variant_t<_0_t, _1_t, _2_t>::as_ptr(_0_t *) const {
  if (current != 0)
    return nullptr;
  return member_0;
}
template <typename _0_t, typename _1_t, typename _2_t>
_1_t const *
heap_variant_t<_0_t, _1_t, _2_t>::as_ptr(_1_t *) const {
  if (current != 1)
    return nullptr;
  return member_1;
}
template <typename _0_t, typename _1_t, typename _2_t>
_2_t const *
heap_variant_t<_0_t, _1_t, _2_t>::as_ptr(_2_t *) const {
  if (current != 2)
    return nullptr;
  return member_2;
}
template <typename _0_t, typename _1_t, typename _2_t>
_0_t *
heap_variant_t<_0_t, _1_t, _2_t>::as_ptr(_0_t *) {
  if (current != 0)
    return nullptr;
  return member_0;
}
template <typename _0_t, typename _1_t, typename _2_t>
_1_t *
heap_variant_t<_0_t, _1_t, _2_t>::as_ptr(_1_t *) {
  if (current != 1)
    return nullptr;
  return member_1;
}
template <typename _0_t, typename _1_t, typename _2_t>
_2_t *
heap_variant_t<_0_t, _1_t, _2_t>::as_ptr(_2_t *) {
  if (current != 2)
    return nullptr;
  return member_2;
}
template <typename _0_t, typename _1_t, typename _2_t>
heap_variant_t<_0_t, _1_t, _2_t>::~heap_variant_t() {
  switch (current) {
  case 0:
    delete member_0;
    break;
  case 1:
    delete member_1;
    break;
  case 2:
    delete member_2;
    break;
  };
}
template <typename _0_t, typename _1_t, typename _2_t, typename _3_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t>::heap_variant_t(heap_variant_t const &o)
    : current(o.current) {
  switch (current) {
  case 0:
    member_0 = new _0_t(*o.member_0);
    break;
  case 1:
    member_1 = new _1_t(*o.member_1);
    break;
  case 2:
    member_2 = new _2_t(*o.member_2);
    break;
  case 3:
    member_3 = new _3_t(*o.member_3);
    break;
  }
}
template <typename _0_t, typename _1_t, typename _2_t, typename _3_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t>::heap_variant_t(heap_variant_t &&o)
    : current(o.current) {
  switch (current) {
  case 0:
    member_0 = new _0_t(_move(*o.member_0));
    break;
  case 1:
    member_1 = new _1_t(_move(*o.member_1));
    break;
  case 2:
    member_2 = new _2_t(_move(*o.member_2));
    break;
  case 3:
    member_3 = new _3_t(_move(*o.member_3));
    break;
  }
}
template <typename _0_t, typename _1_t, typename _2_t, typename _3_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t> &
heap_variant_t<_0_t, _1_t, _2_t, _3_t>::operator=(heap_variant_t const &o) {
  switch (current) {
  case 0:
    delete member_0;
    break;
  case 1:
    delete member_1;
    break;
  case 2:
    delete member_2;
    break;
  case 3:
    delete member_3;
    break;
  };
  current = o.current;
  switch (current) {
  case 0:
    member_0 = new _0_t(*o.member_0);
    break;
  case 1:
    member_1 = new _1_t(*o.member_1);
    break;
  case 2:
    member_2 = new _2_t(*o.member_2);
    break;
  case 3:
    member_3 = new _3_t(*o.member_3);
    break;
  };
  return *this;
}
template <typename _0_t, typename _1_t, typename _2_t, typename _3_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t> &
heap_variant_t<_0_t, _1_t, _2_t, _3_t>::operator=(heap_variant_t &&o) {
  switch (current) {
  case 0:
    delete member_0;
    break;
  case 1:
    delete member_1;
    break;
  case 2:
    delete member_2;
    break;
  case 3:
    delete member_3;
    break;
  };
  current = o.current;
  switch (current) {
  case 0:
    member_0 = new _0_t(_move(*o.member_0));
    break;
  case 1:
    member_1 = new _1_t(_move(*o.member_1));
    break;
  case 2:
    member_2 = new _2_t(_move(*o.member_2));
    break;
  case 3:
    member_3 = new _3_t(_move(*o.member_3));
    break;
  };
  return *this;
}
template <typename _0_t, typename _1_t, typename _2_t, typename _3_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t>::heap_variant_t(_0_t const &x)
    : current(0), member_0(new _0_t(x)) {
}
template <typename _0_t, typename _1_t, typename _2_t, typename _3_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t>::heap_variant_t(_1_t const &x)
    : current(1), member_1(new _1_t(x)) {
}
template <typename _0_t, typename _1_t, typename _2_t, typename _3_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t>::heap_variant_t(_2_t const &x)
    : current(2), member_2(new _2_t(x)) {
}
template <typename _0_t, typename _1_t, typename _2_t, typename _3_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t>::heap_variant_t(_3_t const &x)
    : current(3), member_3(new _3_t(x)) {
}
template <typename _0_t, typename _1_t, typename _2_t, typename _3_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t>::heap_variant_t(_0_t &&x)
    : current(0), member_0(new _0_t(_move(x))) {
}
template <typename _0_t, typename _1_t, typename _2_t, typename _3_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t>::heap_variant_t(_1_t &&x)
    : current(1), member_1(new _1_t(_move(x))) {
}
template <typename _0_t, typename _1_t, typename _2_t, typename _3_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t>::heap_variant_t(_2_t &&x)
    : current(2), member_2(new _2_t(_move(x))) {
}
template <typename _0_t, typename _1_t, typename _2_t, typename _3_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t>::heap_variant_t(_3_t &&x)
    : current(3), member_3(new _3_t(_move(x))) {
}
template <typename _0_t, typename _1_t, typename _2_t, typename _3_t>
bool heap_variant_t<_0_t, _1_t, _2_t, _3_t>::is(_0_t *) const {
  return current == 0;
}
template <typename _0_t, typename _1_t, typename _2_t, typename _3_t>
bool heap_variant_t<_0_t, _1_t, _2_t, _3_t>::is(_1_t *) const {
  return current == 1;
}
template <typename _0_t, typename _1_t, typename _2_t, typename _3_t>
bool heap_variant_t<_0_t, _1_t, _2_t, _3_t>::is(_2_t *) const {
  return current == 2;
}
template <typename _0_t, typename _1_t, typename _2_t, typename _3_t>
bool heap_variant_t<_0_t, _1_t, _2_t, _3_t>::is(_3_t *) const {
  return current == 3;
}
template <typename _0_t, typename _1_t, typename _2_t, typename _3_t>
_0_t const &
heap_variant_t<_0_t, _1_t, _2_t, _3_t>::as(_0_t *) const {
  return *member_0;
}
template <typename _0_t, typename _1_t, typename _2_t, typename _3_t>
_1_t const &
heap_variant_t<_0_t, _1_t, _2_t, _3_t>::as(_1_t *) const {
  return *member_1;
}
template <typename _0_t, typename _1_t, typename _2_t, typename _3_t>
_2_t const &
heap_variant_t<_0_t, _1_t, _2_t, _3_t>::as(_2_t *) const {
  return *member_2;
}
template <typename _0_t, typename _1_t, typename _2_t, typename _3_t>
_3_t const &
heap_variant_t<_0_t, _1_t, _2_t, _3_t>::as(_3_t *) const {
  return *member_3;
}
template <typename _0_t, typename _1_t, typename _2_t, typename _3_t>
_0_t &
heap_variant_t<_0_t, _1_t, _2_t, _3_t>::as(_0_t *) {
  return *member_0;
}
template <typename _0_t, typename _1_t, typename _2_t, typename _3_t>
_1_t &
heap_variant_t<_0_t, _1_t, _2_t, _3_t>::as(_1_t *) {
  return *member_1;
}
template <typename _0_t, typename _1_t, typename _2_t, typename _3_t>
_2_t &
heap_variant_t<_0_t, _1_t, _2_t, _3_t>::as(_2_t *) {
  return *member_2;
}
template <typename _0_t, typename _1_t, typename _2_t, typename _3_t>
_3_t &
heap_variant_t<_0_t, _1_t, _2_t, _3_t>::as(_3_t *) {
  return *member_3;
}
template <typename _0_t, typename _1_t, typename _2_t, typename _3_t>
_0_t const *
heap_variant_t<_0_t, _1_t, _2_t, _3_t>::as_ptr(_0_t *) const {
  if (current != 0)
    return nullptr;
  return member_0;
}
template <typename _0_t, typename _1_t, typename _2_t, typename _3_t>
_1_t const *
heap_variant_t<_0_t, _1_t, _2_t, _3_t>::as_ptr(_1_t *) const {
  if (current != 1)
    return nullptr;
  return member_1;
}
template <typename _0_t, typename _1_t, typename _2_t, typename _3_t>
_2_t const *
heap_variant_t<_0_t, _1_t, _2_t, _3_t>::as_ptr(_2_t *) const {
  if (current != 2)
    return nullptr;
  return member_2;
}
template <typename _0_t, typename _1_t, typename _2_t, typename _3_t>
_3_t const *
heap_variant_t<_0_t, _1_t, _2_t, _3_t>::as_ptr(_3_t *) const {
  if (current != 3)
    return nullptr;
  return member_3;
}
template <typename _0_t, typename _1_t, typename _2_t, typename _3_t>
_0_t *
heap_variant_t<_0_t, _1_t, _2_t, _3_t>::as_ptr(_0_t *) {
  if (current != 0)
    return nullptr;
  return member_0;
}
template <typename _0_t, typename _1_t, typename _2_t, typename _3_t>
_1_t *
heap_variant_t<_0_t, _1_t, _2_t, _3_t>::as_ptr(_1_t *) {
  if (current != 1)
    return nullptr;
  return member_1;
}
template <typename _0_t, typename _1_t, typename _2_t, typename _3_t>
_2_t *
heap_variant_t<_0_t, _1_t, _2_t, _3_t>::as_ptr(_2_t *) {
  if (current != 2)
    return nullptr;
  return member_2;
}
template <typename _0_t, typename _1_t, typename _2_t, typename _3_t>
_3_t *
heap_variant_t<_0_t, _1_t, _2_t, _3_t>::as_ptr(_3_t *) {
  if (current != 3)
    return nullptr;
  return member_3;
}
template <typename _0_t, typename _1_t, typename _2_t, typename _3_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t>::~heap_variant_t() {
  switch (current) {
  case 0:
    delete member_0;
    break;
  case 1:
    delete member_1;
    break;
  case 2:
    delete member_2;
    break;
  case 3:
    delete member_3;
    break;
  };
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t>::heap_variant_t(
    heap_variant_t const &o)
    : current(o.current) {
  switch (current) {
  case 0:
    member_0 = new _0_t(*o.member_0);
    break;
  case 1:
    member_1 = new _1_t(*o.member_1);
    break;
  case 2:
    member_2 = new _2_t(*o.member_2);
    break;
  case 3:
    member_3 = new _3_t(*o.member_3);
    break;
  case 4:
    member_4 = new _4_t(*o.member_4);
    break;
  }
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t>::heap_variant_t(heap_variant_t &&o)
    : current(o.current) {
  switch (current) {
  case 0:
    member_0 = new _0_t(_move(*o.member_0));
    break;
  case 1:
    member_1 = new _1_t(_move(*o.member_1));
    break;
  case 2:
    member_2 = new _2_t(_move(*o.member_2));
    break;
  case 3:
    member_3 = new _3_t(_move(*o.member_3));
    break;
  case 4:
    member_4 = new _4_t(_move(*o.member_4));
    break;
  }
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t> &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t>::operator=(heap_variant_t const &o) {
  switch (current) {
  case 0:
    delete member_0;
    break;
  case 1:
    delete member_1;
    break;
  case 2:
    delete member_2;
    break;
  case 3:
    delete member_3;
    break;
  case 4:
    delete member_4;
    break;
  };
  current = o.current;
  switch (current) {
  case 0:
    member_0 = new _0_t(*o.member_0);
    break;
  case 1:
    member_1 = new _1_t(*o.member_1);
    break;
  case 2:
    member_2 = new _2_t(*o.member_2);
    break;
  case 3:
    member_3 = new _3_t(*o.member_3);
    break;
  case 4:
    member_4 = new _4_t(*o.member_4);
    break;
  };
  return *this;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t> &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t>::operator=(heap_variant_t &&o) {
  switch (current) {
  case 0:
    delete member_0;
    break;
  case 1:
    delete member_1;
    break;
  case 2:
    delete member_2;
    break;
  case 3:
    delete member_3;
    break;
  case 4:
    delete member_4;
    break;
  };
  current = o.current;
  switch (current) {
  case 0:
    member_0 = new _0_t(_move(*o.member_0));
    break;
  case 1:
    member_1 = new _1_t(_move(*o.member_1));
    break;
  case 2:
    member_2 = new _2_t(_move(*o.member_2));
    break;
  case 3:
    member_3 = new _3_t(_move(*o.member_3));
    break;
  case 4:
    member_4 = new _4_t(_move(*o.member_4));
    break;
  };
  return *this;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t>::heap_variant_t(_0_t const &x)
    : current(0), member_0(new _0_t(x)) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t>::heap_variant_t(_1_t const &x)
    : current(1), member_1(new _1_t(x)) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t>::heap_variant_t(_2_t const &x)
    : current(2), member_2(new _2_t(x)) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t>::heap_variant_t(_3_t const &x)
    : current(3), member_3(new _3_t(x)) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t>::heap_variant_t(_4_t const &x)
    : current(4), member_4(new _4_t(x)) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t>::heap_variant_t(_0_t &&x)
    : current(0), member_0(new _0_t(_move(x))) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t>::heap_variant_t(_1_t &&x)
    : current(1), member_1(new _1_t(_move(x))) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t>::heap_variant_t(_2_t &&x)
    : current(2), member_2(new _2_t(_move(x))) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t>::heap_variant_t(_3_t &&x)
    : current(3), member_3(new _3_t(_move(x))) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t>::heap_variant_t(_4_t &&x)
    : current(4), member_4(new _4_t(_move(x))) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t>
bool heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t>::is(_0_t *) const {
  return current == 0;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t>
bool heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t>::is(_1_t *) const {
  return current == 1;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t>
bool heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t>::is(_2_t *) const {
  return current == 2;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t>
bool heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t>::is(_3_t *) const {
  return current == 3;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t>
bool heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t>::is(_4_t *) const {
  return current == 4;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t>
_0_t const &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t>::as(_0_t *) const {
  return *member_0;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t>
_1_t const &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t>::as(_1_t *) const {
  return *member_1;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t>
_2_t const &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t>::as(_2_t *) const {
  return *member_2;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t>
_3_t const &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t>::as(_3_t *) const {
  return *member_3;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t>
_4_t const &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t>::as(_4_t *) const {
  return *member_4;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t>
_0_t &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t>::as(_0_t *) {
  return *member_0;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t>
_1_t &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t>::as(_1_t *) {
  return *member_1;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t>
_2_t &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t>::as(_2_t *) {
  return *member_2;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t>
_3_t &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t>::as(_3_t *) {
  return *member_3;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t>
_4_t &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t>::as(_4_t *) {
  return *member_4;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t>
_0_t const *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t>::as_ptr(_0_t *) const {
  if (current != 0)
    return nullptr;
  return member_0;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t>
_1_t const *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t>::as_ptr(_1_t *) const {
  if (current != 1)
    return nullptr;
  return member_1;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t>
_2_t const *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t>::as_ptr(_2_t *) const {
  if (current != 2)
    return nullptr;
  return member_2;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t>
_3_t const *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t>::as_ptr(_3_t *) const {
  if (current != 3)
    return nullptr;
  return member_3;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t>
_4_t const *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t>::as_ptr(_4_t *) const {
  if (current != 4)
    return nullptr;
  return member_4;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t>
_0_t *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t>::as_ptr(_0_t *) {
  if (current != 0)
    return nullptr;
  return member_0;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t>
_1_t *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t>::as_ptr(_1_t *) {
  if (current != 1)
    return nullptr;
  return member_1;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t>
_2_t *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t>::as_ptr(_2_t *) {
  if (current != 2)
    return nullptr;
  return member_2;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t>
_3_t *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t>::as_ptr(_3_t *) {
  if (current != 3)
    return nullptr;
  return member_3;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t>
_4_t *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t>::as_ptr(_4_t *) {
  if (current != 4)
    return nullptr;
  return member_4;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t>::~heap_variant_t() {
  switch (current) {
  case 0:
    delete member_0;
    break;
  case 1:
    delete member_1;
    break;
  case 2:
    delete member_2;
    break;
  case 3:
    delete member_3;
    break;
  case 4:
    delete member_4;
    break;
  };
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t>::heap_variant_t(
    heap_variant_t const &o)
    : current(o.current) {
  switch (current) {
  case 0:
    member_0 = new _0_t(*o.member_0);
    break;
  case 1:
    member_1 = new _1_t(*o.member_1);
    break;
  case 2:
    member_2 = new _2_t(*o.member_2);
    break;
  case 3:
    member_3 = new _3_t(*o.member_3);
    break;
  case 4:
    member_4 = new _4_t(*o.member_4);
    break;
  case 5:
    member_5 = new _5_t(*o.member_5);
    break;
  }
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t>::heap_variant_t(
    heap_variant_t &&o)
    : current(o.current) {
  switch (current) {
  case 0:
    member_0 = new _0_t(_move(*o.member_0));
    break;
  case 1:
    member_1 = new _1_t(_move(*o.member_1));
    break;
  case 2:
    member_2 = new _2_t(_move(*o.member_2));
    break;
  case 3:
    member_3 = new _3_t(_move(*o.member_3));
    break;
  case 4:
    member_4 = new _4_t(_move(*o.member_4));
    break;
  case 5:
    member_5 = new _5_t(_move(*o.member_5));
    break;
  }
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t> &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t>::operator=(
    heap_variant_t const &o) {
  switch (current) {
  case 0:
    delete member_0;
    break;
  case 1:
    delete member_1;
    break;
  case 2:
    delete member_2;
    break;
  case 3:
    delete member_3;
    break;
  case 4:
    delete member_4;
    break;
  case 5:
    delete member_5;
    break;
  };
  current = o.current;
  switch (current) {
  case 0:
    member_0 = new _0_t(*o.member_0);
    break;
  case 1:
    member_1 = new _1_t(*o.member_1);
    break;
  case 2:
    member_2 = new _2_t(*o.member_2);
    break;
  case 3:
    member_3 = new _3_t(*o.member_3);
    break;
  case 4:
    member_4 = new _4_t(*o.member_4);
    break;
  case 5:
    member_5 = new _5_t(*o.member_5);
    break;
  };
  return *this;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t> &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t>::operator=(
    heap_variant_t &&o) {
  switch (current) {
  case 0:
    delete member_0;
    break;
  case 1:
    delete member_1;
    break;
  case 2:
    delete member_2;
    break;
  case 3:
    delete member_3;
    break;
  case 4:
    delete member_4;
    break;
  case 5:
    delete member_5;
    break;
  };
  current = o.current;
  switch (current) {
  case 0:
    member_0 = new _0_t(_move(*o.member_0));
    break;
  case 1:
    member_1 = new _1_t(_move(*o.member_1));
    break;
  case 2:
    member_2 = new _2_t(_move(*o.member_2));
    break;
  case 3:
    member_3 = new _3_t(_move(*o.member_3));
    break;
  case 4:
    member_4 = new _4_t(_move(*o.member_4));
    break;
  case 5:
    member_5 = new _5_t(_move(*o.member_5));
    break;
  };
  return *this;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t>::heap_variant_t(
    _0_t const &x)
    : current(0), member_0(new _0_t(x)) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t>::heap_variant_t(
    _1_t const &x)
    : current(1), member_1(new _1_t(x)) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t>::heap_variant_t(
    _2_t const &x)
    : current(2), member_2(new _2_t(x)) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t>::heap_variant_t(
    _3_t const &x)
    : current(3), member_3(new _3_t(x)) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t>::heap_variant_t(
    _4_t const &x)
    : current(4), member_4(new _4_t(x)) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t>::heap_variant_t(
    _5_t const &x)
    : current(5), member_5(new _5_t(x)) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t>::heap_variant_t(_0_t &&x)
    : current(0), member_0(new _0_t(_move(x))) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t>::heap_variant_t(_1_t &&x)
    : current(1), member_1(new _1_t(_move(x))) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t>::heap_variant_t(_2_t &&x)
    : current(2), member_2(new _2_t(_move(x))) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t>::heap_variant_t(_3_t &&x)
    : current(3), member_3(new _3_t(_move(x))) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t>::heap_variant_t(_4_t &&x)
    : current(4), member_4(new _4_t(_move(x))) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t>::heap_variant_t(_5_t &&x)
    : current(5), member_5(new _5_t(_move(x))) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t>
bool heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t>::is(_0_t *) const {
  return current == 0;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t>
bool heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t>::is(_1_t *) const {
  return current == 1;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t>
bool heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t>::is(_2_t *) const {
  return current == 2;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t>
bool heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t>::is(_3_t *) const {
  return current == 3;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t>
bool heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t>::is(_4_t *) const {
  return current == 4;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t>
bool heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t>::is(_5_t *) const {
  return current == 5;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t>
_0_t const &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t>::as(_0_t *) const {
  return *member_0;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t>
_1_t const &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t>::as(_1_t *) const {
  return *member_1;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t>
_2_t const &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t>::as(_2_t *) const {
  return *member_2;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t>
_3_t const &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t>::as(_3_t *) const {
  return *member_3;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t>
_4_t const &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t>::as(_4_t *) const {
  return *member_4;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t>
_5_t const &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t>::as(_5_t *) const {
  return *member_5;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t>
_0_t &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t>::as(_0_t *) {
  return *member_0;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t>
_1_t &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t>::as(_1_t *) {
  return *member_1;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t>
_2_t &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t>::as(_2_t *) {
  return *member_2;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t>
_3_t &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t>::as(_3_t *) {
  return *member_3;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t>
_4_t &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t>::as(_4_t *) {
  return *member_4;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t>
_5_t &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t>::as(_5_t *) {
  return *member_5;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t>
_0_t const *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t>::as_ptr(_0_t *) const {
  if (current != 0)
    return nullptr;
  return member_0;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t>
_1_t const *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t>::as_ptr(_1_t *) const {
  if (current != 1)
    return nullptr;
  return member_1;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t>
_2_t const *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t>::as_ptr(_2_t *) const {
  if (current != 2)
    return nullptr;
  return member_2;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t>
_3_t const *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t>::as_ptr(_3_t *) const {
  if (current != 3)
    return nullptr;
  return member_3;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t>
_4_t const *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t>::as_ptr(_4_t *) const {
  if (current != 4)
    return nullptr;
  return member_4;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t>
_5_t const *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t>::as_ptr(_5_t *) const {
  if (current != 5)
    return nullptr;
  return member_5;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t>
_0_t *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t>::as_ptr(_0_t *) {
  if (current != 0)
    return nullptr;
  return member_0;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t>
_1_t *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t>::as_ptr(_1_t *) {
  if (current != 1)
    return nullptr;
  return member_1;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t>
_2_t *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t>::as_ptr(_2_t *) {
  if (current != 2)
    return nullptr;
  return member_2;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t>
_3_t *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t>::as_ptr(_3_t *) {
  if (current != 3)
    return nullptr;
  return member_3;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t>
_4_t *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t>::as_ptr(_4_t *) {
  if (current != 4)
    return nullptr;
  return member_4;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t>
_5_t *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t>::as_ptr(_5_t *) {
  if (current != 5)
    return nullptr;
  return member_5;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t>::~heap_variant_t() {
  switch (current) {
  case 0:
    delete member_0;
    break;
  case 1:
    delete member_1;
    break;
  case 2:
    delete member_2;
    break;
  case 3:
    delete member_3;
    break;
  case 4:
    delete member_4;
    break;
  case 5:
    delete member_5;
    break;
  };
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t>::heap_variant_t(
    heap_variant_t const &o)
    : current(o.current) {
  switch (current) {
  case 0:
    member_0 = new _0_t(*o.member_0);
    break;
  case 1:
    member_1 = new _1_t(*o.member_1);
    break;
  case 2:
    member_2 = new _2_t(*o.member_2);
    break;
  case 3:
    member_3 = new _3_t(*o.member_3);
    break;
  case 4:
    member_4 = new _4_t(*o.member_4);
    break;
  case 5:
    member_5 = new _5_t(*o.member_5);
    break;
  case 6:
    member_6 = new _6_t(*o.member_6);
    break;
  }
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t>::heap_variant_t(
    heap_variant_t &&o)
    : current(o.current) {
  switch (current) {
  case 0:
    member_0 = new _0_t(_move(*o.member_0));
    break;
  case 1:
    member_1 = new _1_t(_move(*o.member_1));
    break;
  case 2:
    member_2 = new _2_t(_move(*o.member_2));
    break;
  case 3:
    member_3 = new _3_t(_move(*o.member_3));
    break;
  case 4:
    member_4 = new _4_t(_move(*o.member_4));
    break;
  case 5:
    member_5 = new _5_t(_move(*o.member_5));
    break;
  case 6:
    member_6 = new _6_t(_move(*o.member_6));
    break;
  }
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t> &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t>::operator=(
    heap_variant_t const &o) {
  switch (current) {
  case 0:
    delete member_0;
    break;
  case 1:
    delete member_1;
    break;
  case 2:
    delete member_2;
    break;
  case 3:
    delete member_3;
    break;
  case 4:
    delete member_4;
    break;
  case 5:
    delete member_5;
    break;
  case 6:
    delete member_6;
    break;
  };
  current = o.current;
  switch (current) {
  case 0:
    member_0 = new _0_t(*o.member_0);
    break;
  case 1:
    member_1 = new _1_t(*o.member_1);
    break;
  case 2:
    member_2 = new _2_t(*o.member_2);
    break;
  case 3:
    member_3 = new _3_t(*o.member_3);
    break;
  case 4:
    member_4 = new _4_t(*o.member_4);
    break;
  case 5:
    member_5 = new _5_t(*o.member_5);
    break;
  case 6:
    member_6 = new _6_t(*o.member_6);
    break;
  };
  return *this;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t> &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t>::operator=(
    heap_variant_t &&o) {
  switch (current) {
  case 0:
    delete member_0;
    break;
  case 1:
    delete member_1;
    break;
  case 2:
    delete member_2;
    break;
  case 3:
    delete member_3;
    break;
  case 4:
    delete member_4;
    break;
  case 5:
    delete member_5;
    break;
  case 6:
    delete member_6;
    break;
  };
  current = o.current;
  switch (current) {
  case 0:
    member_0 = new _0_t(_move(*o.member_0));
    break;
  case 1:
    member_1 = new _1_t(_move(*o.member_1));
    break;
  case 2:
    member_2 = new _2_t(_move(*o.member_2));
    break;
  case 3:
    member_3 = new _3_t(_move(*o.member_3));
    break;
  case 4:
    member_4 = new _4_t(_move(*o.member_4));
    break;
  case 5:
    member_5 = new _5_t(_move(*o.member_5));
    break;
  case 6:
    member_6 = new _6_t(_move(*o.member_6));
    break;
  };
  return *this;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t>::heap_variant_t(
    _0_t const &x)
    : current(0), member_0(new _0_t(x)) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t>::heap_variant_t(
    _1_t const &x)
    : current(1), member_1(new _1_t(x)) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t>::heap_variant_t(
    _2_t const &x)
    : current(2), member_2(new _2_t(x)) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t>::heap_variant_t(
    _3_t const &x)
    : current(3), member_3(new _3_t(x)) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t>::heap_variant_t(
    _4_t const &x)
    : current(4), member_4(new _4_t(x)) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t>::heap_variant_t(
    _5_t const &x)
    : current(5), member_5(new _5_t(x)) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t>::heap_variant_t(
    _6_t const &x)
    : current(6), member_6(new _6_t(x)) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t>::heap_variant_t(
    _0_t &&x)
    : current(0), member_0(new _0_t(_move(x))) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t>::heap_variant_t(
    _1_t &&x)
    : current(1), member_1(new _1_t(_move(x))) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t>::heap_variant_t(
    _2_t &&x)
    : current(2), member_2(new _2_t(_move(x))) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t>::heap_variant_t(
    _3_t &&x)
    : current(3), member_3(new _3_t(_move(x))) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t>::heap_variant_t(
    _4_t &&x)
    : current(4), member_4(new _4_t(_move(x))) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t>::heap_variant_t(
    _5_t &&x)
    : current(5), member_5(new _5_t(_move(x))) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t>::heap_variant_t(
    _6_t &&x)
    : current(6), member_6(new _6_t(_move(x))) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t>
bool heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t>::is(_0_t *) const {
  return current == 0;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t>
bool heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t>::is(_1_t *) const {
  return current == 1;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t>
bool heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t>::is(_2_t *) const {
  return current == 2;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t>
bool heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t>::is(_3_t *) const {
  return current == 3;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t>
bool heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t>::is(_4_t *) const {
  return current == 4;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t>
bool heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t>::is(_5_t *) const {
  return current == 5;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t>
bool heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t>::is(_6_t *) const {
  return current == 6;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t>
_0_t const &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t>::as(_0_t *) const {
  return *member_0;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t>
_1_t const &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t>::as(_1_t *) const {
  return *member_1;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t>
_2_t const &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t>::as(_2_t *) const {
  return *member_2;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t>
_3_t const &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t>::as(_3_t *) const {
  return *member_3;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t>
_4_t const &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t>::as(_4_t *) const {
  return *member_4;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t>
_5_t const &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t>::as(_5_t *) const {
  return *member_5;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t>
_6_t const &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t>::as(_6_t *) const {
  return *member_6;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t>
_0_t &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t>::as(_0_t *) {
  return *member_0;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t>
_1_t &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t>::as(_1_t *) {
  return *member_1;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t>
_2_t &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t>::as(_2_t *) {
  return *member_2;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t>
_3_t &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t>::as(_3_t *) {
  return *member_3;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t>
_4_t &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t>::as(_4_t *) {
  return *member_4;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t>
_5_t &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t>::as(_5_t *) {
  return *member_5;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t>
_6_t &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t>::as(_6_t *) {
  return *member_6;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t>
_0_t const *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t>::as_ptr(_0_t *) const {
  if (current != 0)
    return nullptr;
  return member_0;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t>
_1_t const *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t>::as_ptr(_1_t *) const {
  if (current != 1)
    return nullptr;
  return member_1;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t>
_2_t const *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t>::as_ptr(_2_t *) const {
  if (current != 2)
    return nullptr;
  return member_2;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t>
_3_t const *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t>::as_ptr(_3_t *) const {
  if (current != 3)
    return nullptr;
  return member_3;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t>
_4_t const *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t>::as_ptr(_4_t *) const {
  if (current != 4)
    return nullptr;
  return member_4;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t>
_5_t const *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t>::as_ptr(_5_t *) const {
  if (current != 5)
    return nullptr;
  return member_5;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t>
_6_t const *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t>::as_ptr(_6_t *) const {
  if (current != 6)
    return nullptr;
  return member_6;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t>
_0_t *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t>::as_ptr(_0_t *) {
  if (current != 0)
    return nullptr;
  return member_0;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t>
_1_t *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t>::as_ptr(_1_t *) {
  if (current != 1)
    return nullptr;
  return member_1;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t>
_2_t *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t>::as_ptr(_2_t *) {
  if (current != 2)
    return nullptr;
  return member_2;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t>
_3_t *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t>::as_ptr(_3_t *) {
  if (current != 3)
    return nullptr;
  return member_3;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t>
_4_t *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t>::as_ptr(_4_t *) {
  if (current != 4)
    return nullptr;
  return member_4;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t>
_5_t *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t>::as_ptr(_5_t *) {
  if (current != 5)
    return nullptr;
  return member_5;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t>
_6_t *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t>::as_ptr(_6_t *) {
  if (current != 6)
    return nullptr;
  return member_6;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t>::~heap_variant_t() {
  switch (current) {
  case 0:
    delete member_0;
    break;
  case 1:
    delete member_1;
    break;
  case 2:
    delete member_2;
    break;
  case 3:
    delete member_3;
    break;
  case 4:
    delete member_4;
    break;
  case 5:
    delete member_5;
    break;
  case 6:
    delete member_6;
    break;
  };
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t>::heap_variant_t(
    heap_variant_t const &o)
    : current(o.current) {
  switch (current) {
  case 0:
    member_0 = new _0_t(*o.member_0);
    break;
  case 1:
    member_1 = new _1_t(*o.member_1);
    break;
  case 2:
    member_2 = new _2_t(*o.member_2);
    break;
  case 3:
    member_3 = new _3_t(*o.member_3);
    break;
  case 4:
    member_4 = new _4_t(*o.member_4);
    break;
  case 5:
    member_5 = new _5_t(*o.member_5);
    break;
  case 6:
    member_6 = new _6_t(*o.member_6);
    break;
  case 7:
    member_7 = new _7_t(*o.member_7);
    break;
  }
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t>::heap_variant_t(
    heap_variant_t &&o)
    : current(o.current) {
  switch (current) {
  case 0:
    member_0 = new _0_t(_move(*o.member_0));
    break;
  case 1:
    member_1 = new _1_t(_move(*o.member_1));
    break;
  case 2:
    member_2 = new _2_t(_move(*o.member_2));
    break;
  case 3:
    member_3 = new _3_t(_move(*o.member_3));
    break;
  case 4:
    member_4 = new _4_t(_move(*o.member_4));
    break;
  case 5:
    member_5 = new _5_t(_move(*o.member_5));
    break;
  case 6:
    member_6 = new _6_t(_move(*o.member_6));
    break;
  case 7:
    member_7 = new _7_t(_move(*o.member_7));
    break;
  }
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t> &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t>::operator=(
    heap_variant_t const &o) {
  switch (current) {
  case 0:
    delete member_0;
    break;
  case 1:
    delete member_1;
    break;
  case 2:
    delete member_2;
    break;
  case 3:
    delete member_3;
    break;
  case 4:
    delete member_4;
    break;
  case 5:
    delete member_5;
    break;
  case 6:
    delete member_6;
    break;
  case 7:
    delete member_7;
    break;
  };
  current = o.current;
  switch (current) {
  case 0:
    member_0 = new _0_t(*o.member_0);
    break;
  case 1:
    member_1 = new _1_t(*o.member_1);
    break;
  case 2:
    member_2 = new _2_t(*o.member_2);
    break;
  case 3:
    member_3 = new _3_t(*o.member_3);
    break;
  case 4:
    member_4 = new _4_t(*o.member_4);
    break;
  case 5:
    member_5 = new _5_t(*o.member_5);
    break;
  case 6:
    member_6 = new _6_t(*o.member_6);
    break;
  case 7:
    member_7 = new _7_t(*o.member_7);
    break;
  };
  return *this;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t> &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t>::operator=(
    heap_variant_t &&o) {
  switch (current) {
  case 0:
    delete member_0;
    break;
  case 1:
    delete member_1;
    break;
  case 2:
    delete member_2;
    break;
  case 3:
    delete member_3;
    break;
  case 4:
    delete member_4;
    break;
  case 5:
    delete member_5;
    break;
  case 6:
    delete member_6;
    break;
  case 7:
    delete member_7;
    break;
  };
  current = o.current;
  switch (current) {
  case 0:
    member_0 = new _0_t(_move(*o.member_0));
    break;
  case 1:
    member_1 = new _1_t(_move(*o.member_1));
    break;
  case 2:
    member_2 = new _2_t(_move(*o.member_2));
    break;
  case 3:
    member_3 = new _3_t(_move(*o.member_3));
    break;
  case 4:
    member_4 = new _4_t(_move(*o.member_4));
    break;
  case 5:
    member_5 = new _5_t(_move(*o.member_5));
    break;
  case 6:
    member_6 = new _6_t(_move(*o.member_6));
    break;
  case 7:
    member_7 = new _7_t(_move(*o.member_7));
    break;
  };
  return *this;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t>::heap_variant_t(
    _0_t const &x)
    : current(0), member_0(new _0_t(x)) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t>::heap_variant_t(
    _1_t const &x)
    : current(1), member_1(new _1_t(x)) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t>::heap_variant_t(
    _2_t const &x)
    : current(2), member_2(new _2_t(x)) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t>::heap_variant_t(
    _3_t const &x)
    : current(3), member_3(new _3_t(x)) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t>::heap_variant_t(
    _4_t const &x)
    : current(4), member_4(new _4_t(x)) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t>::heap_variant_t(
    _5_t const &x)
    : current(5), member_5(new _5_t(x)) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t>::heap_variant_t(
    _6_t const &x)
    : current(6), member_6(new _6_t(x)) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t>::heap_variant_t(
    _7_t const &x)
    : current(7), member_7(new _7_t(x)) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t>::heap_variant_t(
    _0_t &&x)
    : current(0), member_0(new _0_t(_move(x))) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t>::heap_variant_t(
    _1_t &&x)
    : current(1), member_1(new _1_t(_move(x))) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t>::heap_variant_t(
    _2_t &&x)
    : current(2), member_2(new _2_t(_move(x))) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t>::heap_variant_t(
    _3_t &&x)
    : current(3), member_3(new _3_t(_move(x))) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t>::heap_variant_t(
    _4_t &&x)
    : current(4), member_4(new _4_t(_move(x))) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t>::heap_variant_t(
    _5_t &&x)
    : current(5), member_5(new _5_t(_move(x))) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t>::heap_variant_t(
    _6_t &&x)
    : current(6), member_6(new _6_t(_move(x))) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t>::heap_variant_t(
    _7_t &&x)
    : current(7), member_7(new _7_t(_move(x))) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t>
bool heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t>::is(_0_t *) const {
  return current == 0;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t>
bool heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t>::is(_1_t *) const {
  return current == 1;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t>
bool heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t>::is(_2_t *) const {
  return current == 2;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t>
bool heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t>::is(_3_t *) const {
  return current == 3;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t>
bool heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t>::is(_4_t *) const {
  return current == 4;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t>
bool heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t>::is(_5_t *) const {
  return current == 5;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t>
bool heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t>::is(_6_t *) const {
  return current == 6;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t>
bool heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t>::is(_7_t *) const {
  return current == 7;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t>
_0_t const &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t>::as(_0_t *) const {
  return *member_0;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t>
_1_t const &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t>::as(_1_t *) const {
  return *member_1;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t>
_2_t const &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t>::as(_2_t *) const {
  return *member_2;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t>
_3_t const &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t>::as(_3_t *) const {
  return *member_3;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t>
_4_t const &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t>::as(_4_t *) const {
  return *member_4;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t>
_5_t const &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t>::as(_5_t *) const {
  return *member_5;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t>
_6_t const &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t>::as(_6_t *) const {
  return *member_6;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t>
_7_t const &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t>::as(_7_t *) const {
  return *member_7;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t>
_0_t &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t>::as(_0_t *) {
  return *member_0;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t>
_1_t &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t>::as(_1_t *) {
  return *member_1;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t>
_2_t &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t>::as(_2_t *) {
  return *member_2;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t>
_3_t &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t>::as(_3_t *) {
  return *member_3;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t>
_4_t &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t>::as(_4_t *) {
  return *member_4;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t>
_5_t &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t>::as(_5_t *) {
  return *member_5;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t>
_6_t &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t>::as(_6_t *) {
  return *member_6;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t>
_7_t &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t>::as(_7_t *) {
  return *member_7;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t>
_0_t const *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t>::as_ptr(
    _0_t *) const {
  if (current != 0)
    return nullptr;
  return member_0;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t>
_1_t const *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t>::as_ptr(
    _1_t *) const {
  if (current != 1)
    return nullptr;
  return member_1;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t>
_2_t const *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t>::as_ptr(
    _2_t *) const {
  if (current != 2)
    return nullptr;
  return member_2;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t>
_3_t const *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t>::as_ptr(
    _3_t *) const {
  if (current != 3)
    return nullptr;
  return member_3;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t>
_4_t const *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t>::as_ptr(
    _4_t *) const {
  if (current != 4)
    return nullptr;
  return member_4;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t>
_5_t const *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t>::as_ptr(
    _5_t *) const {
  if (current != 5)
    return nullptr;
  return member_5;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t>
_6_t const *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t>::as_ptr(
    _6_t *) const {
  if (current != 6)
    return nullptr;
  return member_6;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t>
_7_t const *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t>::as_ptr(
    _7_t *) const {
  if (current != 7)
    return nullptr;
  return member_7;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t>
_0_t *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t>::as_ptr(_0_t *) {
  if (current != 0)
    return nullptr;
  return member_0;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t>
_1_t *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t>::as_ptr(_1_t *) {
  if (current != 1)
    return nullptr;
  return member_1;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t>
_2_t *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t>::as_ptr(_2_t *) {
  if (current != 2)
    return nullptr;
  return member_2;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t>
_3_t *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t>::as_ptr(_3_t *) {
  if (current != 3)
    return nullptr;
  return member_3;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t>
_4_t *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t>::as_ptr(_4_t *) {
  if (current != 4)
    return nullptr;
  return member_4;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t>
_5_t *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t>::as_ptr(_5_t *) {
  if (current != 5)
    return nullptr;
  return member_5;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t>
_6_t *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t>::as_ptr(_6_t *) {
  if (current != 6)
    return nullptr;
  return member_6;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t>
_7_t *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t>::as_ptr(_7_t *) {
  if (current != 7)
    return nullptr;
  return member_7;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t>::
    ~heap_variant_t() {
  switch (current) {
  case 0:
    delete member_0;
    break;
  case 1:
    delete member_1;
    break;
  case 2:
    delete member_2;
    break;
  case 3:
    delete member_3;
    break;
  case 4:
    delete member_4;
    break;
  case 5:
    delete member_5;
    break;
  case 6:
    delete member_6;
    break;
  case 7:
    delete member_7;
    break;
  };
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::
    heap_variant_t(heap_variant_t const &o)
    : current(o.current) {
  switch (current) {
  case 0:
    member_0 = new _0_t(*o.member_0);
    break;
  case 1:
    member_1 = new _1_t(*o.member_1);
    break;
  case 2:
    member_2 = new _2_t(*o.member_2);
    break;
  case 3:
    member_3 = new _3_t(*o.member_3);
    break;
  case 4:
    member_4 = new _4_t(*o.member_4);
    break;
  case 5:
    member_5 = new _5_t(*o.member_5);
    break;
  case 6:
    member_6 = new _6_t(*o.member_6);
    break;
  case 7:
    member_7 = new _7_t(*o.member_7);
    break;
  case 8:
    member_8 = new _8_t(*o.member_8);
    break;
  }
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::
    heap_variant_t(heap_variant_t &&o)
    : current(o.current) {
  switch (current) {
  case 0:
    member_0 = new _0_t(_move(*o.member_0));
    break;
  case 1:
    member_1 = new _1_t(_move(*o.member_1));
    break;
  case 2:
    member_2 = new _2_t(_move(*o.member_2));
    break;
  case 3:
    member_3 = new _3_t(_move(*o.member_3));
    break;
  case 4:
    member_4 = new _4_t(_move(*o.member_4));
    break;
  case 5:
    member_5 = new _5_t(_move(*o.member_5));
    break;
  case 6:
    member_6 = new _6_t(_move(*o.member_6));
    break;
  case 7:
    member_7 = new _7_t(_move(*o.member_7));
    break;
  case 8:
    member_8 = new _8_t(_move(*o.member_8));
    break;
  }
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t> &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::operator=(
    heap_variant_t const &o) {
  switch (current) {
  case 0:
    delete member_0;
    break;
  case 1:
    delete member_1;
    break;
  case 2:
    delete member_2;
    break;
  case 3:
    delete member_3;
    break;
  case 4:
    delete member_4;
    break;
  case 5:
    delete member_5;
    break;
  case 6:
    delete member_6;
    break;
  case 7:
    delete member_7;
    break;
  case 8:
    delete member_8;
    break;
  };
  current = o.current;
  switch (current) {
  case 0:
    member_0 = new _0_t(*o.member_0);
    break;
  case 1:
    member_1 = new _1_t(*o.member_1);
    break;
  case 2:
    member_2 = new _2_t(*o.member_2);
    break;
  case 3:
    member_3 = new _3_t(*o.member_3);
    break;
  case 4:
    member_4 = new _4_t(*o.member_4);
    break;
  case 5:
    member_5 = new _5_t(*o.member_5);
    break;
  case 6:
    member_6 = new _6_t(*o.member_6);
    break;
  case 7:
    member_7 = new _7_t(*o.member_7);
    break;
  case 8:
    member_8 = new _8_t(*o.member_8);
    break;
  };
  return *this;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t> &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::operator=(
    heap_variant_t &&o) {
  switch (current) {
  case 0:
    delete member_0;
    break;
  case 1:
    delete member_1;
    break;
  case 2:
    delete member_2;
    break;
  case 3:
    delete member_3;
    break;
  case 4:
    delete member_4;
    break;
  case 5:
    delete member_5;
    break;
  case 6:
    delete member_6;
    break;
  case 7:
    delete member_7;
    break;
  case 8:
    delete member_8;
    break;
  };
  current = o.current;
  switch (current) {
  case 0:
    member_0 = new _0_t(_move(*o.member_0));
    break;
  case 1:
    member_1 = new _1_t(_move(*o.member_1));
    break;
  case 2:
    member_2 = new _2_t(_move(*o.member_2));
    break;
  case 3:
    member_3 = new _3_t(_move(*o.member_3));
    break;
  case 4:
    member_4 = new _4_t(_move(*o.member_4));
    break;
  case 5:
    member_5 = new _5_t(_move(*o.member_5));
    break;
  case 6:
    member_6 = new _6_t(_move(*o.member_6));
    break;
  case 7:
    member_7 = new _7_t(_move(*o.member_7));
    break;
  case 8:
    member_8 = new _8_t(_move(*o.member_8));
    break;
  };
  return *this;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::
    heap_variant_t(_0_t const &x)
    : current(0), member_0(new _0_t(x)) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::
    heap_variant_t(_1_t const &x)
    : current(1), member_1(new _1_t(x)) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::
    heap_variant_t(_2_t const &x)
    : current(2), member_2(new _2_t(x)) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::
    heap_variant_t(_3_t const &x)
    : current(3), member_3(new _3_t(x)) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::
    heap_variant_t(_4_t const &x)
    : current(4), member_4(new _4_t(x)) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::
    heap_variant_t(_5_t const &x)
    : current(5), member_5(new _5_t(x)) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::
    heap_variant_t(_6_t const &x)
    : current(6), member_6(new _6_t(x)) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::
    heap_variant_t(_7_t const &x)
    : current(7), member_7(new _7_t(x)) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::
    heap_variant_t(_8_t const &x)
    : current(8), member_8(new _8_t(x)) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::
    heap_variant_t(_0_t &&x)
    : current(0), member_0(new _0_t(_move(x))) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::
    heap_variant_t(_1_t &&x)
    : current(1), member_1(new _1_t(_move(x))) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::
    heap_variant_t(_2_t &&x)
    : current(2), member_2(new _2_t(_move(x))) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::
    heap_variant_t(_3_t &&x)
    : current(3), member_3(new _3_t(_move(x))) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::
    heap_variant_t(_4_t &&x)
    : current(4), member_4(new _4_t(_move(x))) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::
    heap_variant_t(_5_t &&x)
    : current(5), member_5(new _5_t(_move(x))) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::
    heap_variant_t(_6_t &&x)
    : current(6), member_6(new _6_t(_move(x))) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::
    heap_variant_t(_7_t &&x)
    : current(7), member_7(new _7_t(_move(x))) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::
    heap_variant_t(_8_t &&x)
    : current(8), member_8(new _8_t(_move(x))) {
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
bool heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::is(
    _0_t *) const {
  return current == 0;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
bool heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::is(
    _1_t *) const {
  return current == 1;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
bool heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::is(
    _2_t *) const {
  return current == 2;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
bool heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::is(
    _3_t *) const {
  return current == 3;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
bool heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::is(
    _4_t *) const {
  return current == 4;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
bool heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::is(
    _5_t *) const {
  return current == 5;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
bool heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::is(
    _6_t *) const {
  return current == 6;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
bool heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::is(
    _7_t *) const {
  return current == 7;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
bool heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::is(
    _8_t *) const {
  return current == 8;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
_0_t const &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::as(
    _0_t *) const {
  return *member_0;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
_1_t const &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::as(
    _1_t *) const {
  return *member_1;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
_2_t const &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::as(
    _2_t *) const {
  return *member_2;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
_3_t const &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::as(
    _3_t *) const {
  return *member_3;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
_4_t const &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::as(
    _4_t *) const {
  return *member_4;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
_5_t const &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::as(
    _5_t *) const {
  return *member_5;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
_6_t const &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::as(
    _6_t *) const {
  return *member_6;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
_7_t const &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::as(
    _7_t *) const {
  return *member_7;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
_8_t const &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::as(
    _8_t *) const {
  return *member_8;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
_0_t &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::as(_0_t *) {
  return *member_0;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
_1_t &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::as(_1_t *) {
  return *member_1;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
_2_t &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::as(_2_t *) {
  return *member_2;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
_3_t &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::as(_3_t *) {
  return *member_3;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
_4_t &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::as(_4_t *) {
  return *member_4;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
_5_t &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::as(_5_t *) {
  return *member_5;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
_6_t &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::as(_6_t *) {
  return *member_6;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
_7_t &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::as(_7_t *) {
  return *member_7;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
_8_t &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::as(_8_t *) {
  return *member_8;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
_0_t const *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::as_ptr(
    _0_t *) const {
  if (current != 0)
    return nullptr;
  return member_0;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
_1_t const *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::as_ptr(
    _1_t *) const {
  if (current != 1)
    return nullptr;
  return member_1;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
_2_t const *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::as_ptr(
    _2_t *) const {
  if (current != 2)
    return nullptr;
  return member_2;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
_3_t const *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::as_ptr(
    _3_t *) const {
  if (current != 3)
    return nullptr;
  return member_3;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
_4_t const *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::as_ptr(
    _4_t *) const {
  if (current != 4)
    return nullptr;
  return member_4;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
_5_t const *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::as_ptr(
    _5_t *) const {
  if (current != 5)
    return nullptr;
  return member_5;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
_6_t const *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::as_ptr(
    _6_t *) const {
  if (current != 6)
    return nullptr;
  return member_6;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
_7_t const *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::as_ptr(
    _7_t *) const {
  if (current != 7)
    return nullptr;
  return member_7;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
_8_t const *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::as_ptr(
    _8_t *) const {
  if (current != 8)
    return nullptr;
  return member_8;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
_0_t *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::as_ptr(
    _0_t *) {
  if (current != 0)
    return nullptr;
  return member_0;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
_1_t *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::as_ptr(
    _1_t *) {
  if (current != 1)
    return nullptr;
  return member_1;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
_2_t *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::as_ptr(
    _2_t *) {
  if (current != 2)
    return nullptr;
  return member_2;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
_3_t *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::as_ptr(
    _3_t *) {
  if (current != 3)
    return nullptr;
  return member_3;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
_4_t *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::as_ptr(
    _4_t *) {
  if (current != 4)
    return nullptr;
  return member_4;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
_5_t *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::as_ptr(
    _5_t *) {
  if (current != 5)
    return nullptr;
  return member_5;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
_6_t *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::as_ptr(
    _6_t *) {
  if (current != 6)
    return nullptr;
  return member_6;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
_7_t *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::as_ptr(
    _7_t *) {
  if (current != 7)
    return nullptr;
  return member_7;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
_8_t *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::as_ptr(
    _8_t *) {
  if (current != 8)
    return nullptr;
  return member_8;
}
template <typename _0_t,
          typename _1_t,
          typename _2_t,
          typename _3_t,
          typename _4_t,
          typename _5_t,
          typename _6_t,
          typename _7_t,
          typename _8_t>
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t>::
    ~heap_variant_t() {
  switch (current) {
  case 0:
    delete member_0;
    break;
  case 1:
    delete member_1;
    break;
  case 2:
    delete member_2;
    break;
  case 3:
    delete member_3;
    break;
  case 4:
    delete member_4;
    break;
  case 5:
    delete member_5;
    break;
  case 6:
    delete member_6;
    break;
  case 7:
    delete member_7;
    break;
  case 8:
    delete member_8;
    break;
  };
}
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
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::
    heap_variant_t(heap_variant_t const &o)
    : current(o.current) {
  switch (current) {
  case 0:
    member_0 = new _0_t(*o.member_0);
    break;
  case 1:
    member_1 = new _1_t(*o.member_1);
    break;
  case 2:
    member_2 = new _2_t(*o.member_2);
    break;
  case 3:
    member_3 = new _3_t(*o.member_3);
    break;
  case 4:
    member_4 = new _4_t(*o.member_4);
    break;
  case 5:
    member_5 = new _5_t(*o.member_5);
    break;
  case 6:
    member_6 = new _6_t(*o.member_6);
    break;
  case 7:
    member_7 = new _7_t(*o.member_7);
    break;
  case 8:
    member_8 = new _8_t(*o.member_8);
    break;
  case 9:
    member_9 = new _9_t(*o.member_9);
    break;
  }
}
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
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::
    heap_variant_t(heap_variant_t &&o)
    : current(o.current) {
  switch (current) {
  case 0:
    member_0 = new _0_t(_move(*o.member_0));
    break;
  case 1:
    member_1 = new _1_t(_move(*o.member_1));
    break;
  case 2:
    member_2 = new _2_t(_move(*o.member_2));
    break;
  case 3:
    member_3 = new _3_t(_move(*o.member_3));
    break;
  case 4:
    member_4 = new _4_t(_move(*o.member_4));
    break;
  case 5:
    member_5 = new _5_t(_move(*o.member_5));
    break;
  case 6:
    member_6 = new _6_t(_move(*o.member_6));
    break;
  case 7:
    member_7 = new _7_t(_move(*o.member_7));
    break;
  case 8:
    member_8 = new _8_t(_move(*o.member_8));
    break;
  case 9:
    member_9 = new _9_t(_move(*o.member_9));
    break;
  }
}
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
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t> &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::
operator=(heap_variant_t const &o) {
  switch (current) {
  case 0:
    delete member_0;
    break;
  case 1:
    delete member_1;
    break;
  case 2:
    delete member_2;
    break;
  case 3:
    delete member_3;
    break;
  case 4:
    delete member_4;
    break;
  case 5:
    delete member_5;
    break;
  case 6:
    delete member_6;
    break;
  case 7:
    delete member_7;
    break;
  case 8:
    delete member_8;
    break;
  case 9:
    delete member_9;
    break;
  };
  current = o.current;
  switch (current) {
  case 0:
    member_0 = new _0_t(*o.member_0);
    break;
  case 1:
    member_1 = new _1_t(*o.member_1);
    break;
  case 2:
    member_2 = new _2_t(*o.member_2);
    break;
  case 3:
    member_3 = new _3_t(*o.member_3);
    break;
  case 4:
    member_4 = new _4_t(*o.member_4);
    break;
  case 5:
    member_5 = new _5_t(*o.member_5);
    break;
  case 6:
    member_6 = new _6_t(*o.member_6);
    break;
  case 7:
    member_7 = new _7_t(*o.member_7);
    break;
  case 8:
    member_8 = new _8_t(*o.member_8);
    break;
  case 9:
    member_9 = new _9_t(*o.member_9);
    break;
  };
  return *this;
}
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
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t> &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::
operator=(heap_variant_t &&o) {
  switch (current) {
  case 0:
    delete member_0;
    break;
  case 1:
    delete member_1;
    break;
  case 2:
    delete member_2;
    break;
  case 3:
    delete member_3;
    break;
  case 4:
    delete member_4;
    break;
  case 5:
    delete member_5;
    break;
  case 6:
    delete member_6;
    break;
  case 7:
    delete member_7;
    break;
  case 8:
    delete member_8;
    break;
  case 9:
    delete member_9;
    break;
  };
  current = o.current;
  switch (current) {
  case 0:
    member_0 = new _0_t(_move(*o.member_0));
    break;
  case 1:
    member_1 = new _1_t(_move(*o.member_1));
    break;
  case 2:
    member_2 = new _2_t(_move(*o.member_2));
    break;
  case 3:
    member_3 = new _3_t(_move(*o.member_3));
    break;
  case 4:
    member_4 = new _4_t(_move(*o.member_4));
    break;
  case 5:
    member_5 = new _5_t(_move(*o.member_5));
    break;
  case 6:
    member_6 = new _6_t(_move(*o.member_6));
    break;
  case 7:
    member_7 = new _7_t(_move(*o.member_7));
    break;
  case 8:
    member_8 = new _8_t(_move(*o.member_8));
    break;
  case 9:
    member_9 = new _9_t(_move(*o.member_9));
    break;
  };
  return *this;
}
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
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::
    heap_variant_t(_0_t const &x)
    : current(0), member_0(new _0_t(x)) {
}
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
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::
    heap_variant_t(_1_t const &x)
    : current(1), member_1(new _1_t(x)) {
}
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
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::
    heap_variant_t(_2_t const &x)
    : current(2), member_2(new _2_t(x)) {
}
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
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::
    heap_variant_t(_3_t const &x)
    : current(3), member_3(new _3_t(x)) {
}
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
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::
    heap_variant_t(_4_t const &x)
    : current(4), member_4(new _4_t(x)) {
}
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
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::
    heap_variant_t(_5_t const &x)
    : current(5), member_5(new _5_t(x)) {
}
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
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::
    heap_variant_t(_6_t const &x)
    : current(6), member_6(new _6_t(x)) {
}
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
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::
    heap_variant_t(_7_t const &x)
    : current(7), member_7(new _7_t(x)) {
}
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
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::
    heap_variant_t(_8_t const &x)
    : current(8), member_8(new _8_t(x)) {
}
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
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::
    heap_variant_t(_9_t const &x)
    : current(9), member_9(new _9_t(x)) {
}
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
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::
    heap_variant_t(_0_t &&x)
    : current(0), member_0(new _0_t(_move(x))) {
}
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
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::
    heap_variant_t(_1_t &&x)
    : current(1), member_1(new _1_t(_move(x))) {
}
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
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::
    heap_variant_t(_2_t &&x)
    : current(2), member_2(new _2_t(_move(x))) {
}
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
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::
    heap_variant_t(_3_t &&x)
    : current(3), member_3(new _3_t(_move(x))) {
}
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
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::
    heap_variant_t(_4_t &&x)
    : current(4), member_4(new _4_t(_move(x))) {
}
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
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::
    heap_variant_t(_5_t &&x)
    : current(5), member_5(new _5_t(_move(x))) {
}
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
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::
    heap_variant_t(_6_t &&x)
    : current(6), member_6(new _6_t(_move(x))) {
}
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
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::
    heap_variant_t(_7_t &&x)
    : current(7), member_7(new _7_t(_move(x))) {
}
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
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::
    heap_variant_t(_8_t &&x)
    : current(8), member_8(new _8_t(_move(x))) {
}
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
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::
    heap_variant_t(_9_t &&x)
    : current(9), member_9(new _9_t(_move(x))) {
}
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
bool heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::is(
    _0_t *) const {
  return current == 0;
}
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
bool heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::is(
    _1_t *) const {
  return current == 1;
}
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
bool heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::is(
    _2_t *) const {
  return current == 2;
}
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
bool heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::is(
    _3_t *) const {
  return current == 3;
}
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
bool heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::is(
    _4_t *) const {
  return current == 4;
}
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
bool heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::is(
    _5_t *) const {
  return current == 5;
}
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
bool heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::is(
    _6_t *) const {
  return current == 6;
}
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
bool heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::is(
    _7_t *) const {
  return current == 7;
}
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
bool heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::is(
    _8_t *) const {
  return current == 8;
}
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
bool heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::is(
    _9_t *) const {
  return current == 9;
}
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
_0_t const &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::as(
    _0_t *) const {
  return *member_0;
}
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
_1_t const &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::as(
    _1_t *) const {
  return *member_1;
}
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
_2_t const &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::as(
    _2_t *) const {
  return *member_2;
}
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
_3_t const &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::as(
    _3_t *) const {
  return *member_3;
}
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
_4_t const &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::as(
    _4_t *) const {
  return *member_4;
}
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
_5_t const &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::as(
    _5_t *) const {
  return *member_5;
}
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
_6_t const &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::as(
    _6_t *) const {
  return *member_6;
}
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
_7_t const &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::as(
    _7_t *) const {
  return *member_7;
}
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
_8_t const &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::as(
    _8_t *) const {
  return *member_8;
}
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
_9_t const &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::as(
    _9_t *) const {
  return *member_9;
}
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
_0_t &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::as(
    _0_t *) {
  return *member_0;
}
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
_1_t &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::as(
    _1_t *) {
  return *member_1;
}
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
_2_t &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::as(
    _2_t *) {
  return *member_2;
}
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
_3_t &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::as(
    _3_t *) {
  return *member_3;
}
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
_4_t &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::as(
    _4_t *) {
  return *member_4;
}
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
_5_t &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::as(
    _5_t *) {
  return *member_5;
}
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
_6_t &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::as(
    _6_t *) {
  return *member_6;
}
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
_7_t &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::as(
    _7_t *) {
  return *member_7;
}
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
_8_t &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::as(
    _8_t *) {
  return *member_8;
}
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
_9_t &
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::as(
    _9_t *) {
  return *member_9;
}
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
_0_t const *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::
    as_ptr(_0_t *) const {
  if (current != 0)
    return nullptr;
  return member_0;
}
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
_1_t const *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::
    as_ptr(_1_t *) const {
  if (current != 1)
    return nullptr;
  return member_1;
}
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
_2_t const *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::
    as_ptr(_2_t *) const {
  if (current != 2)
    return nullptr;
  return member_2;
}
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
_3_t const *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::
    as_ptr(_3_t *) const {
  if (current != 3)
    return nullptr;
  return member_3;
}
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
_4_t const *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::
    as_ptr(_4_t *) const {
  if (current != 4)
    return nullptr;
  return member_4;
}
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
_5_t const *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::
    as_ptr(_5_t *) const {
  if (current != 5)
    return nullptr;
  return member_5;
}
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
_6_t const *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::
    as_ptr(_6_t *) const {
  if (current != 6)
    return nullptr;
  return member_6;
}
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
_7_t const *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::
    as_ptr(_7_t *) const {
  if (current != 7)
    return nullptr;
  return member_7;
}
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
_8_t const *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::
    as_ptr(_8_t *) const {
  if (current != 8)
    return nullptr;
  return member_8;
}
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
_9_t const *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::
    as_ptr(_9_t *) const {
  if (current != 9)
    return nullptr;
  return member_9;
}
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
_0_t *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::
    as_ptr(_0_t *) {
  if (current != 0)
    return nullptr;
  return member_0;
}
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
_1_t *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::
    as_ptr(_1_t *) {
  if (current != 1)
    return nullptr;
  return member_1;
}
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
_2_t *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::
    as_ptr(_2_t *) {
  if (current != 2)
    return nullptr;
  return member_2;
}
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
_3_t *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::
    as_ptr(_3_t *) {
  if (current != 3)
    return nullptr;
  return member_3;
}
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
_4_t *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::
    as_ptr(_4_t *) {
  if (current != 4)
    return nullptr;
  return member_4;
}
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
_5_t *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::
    as_ptr(_5_t *) {
  if (current != 5)
    return nullptr;
  return member_5;
}
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
_6_t *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::
    as_ptr(_6_t *) {
  if (current != 6)
    return nullptr;
  return member_6;
}
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
_7_t *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::
    as_ptr(_7_t *) {
  if (current != 7)
    return nullptr;
  return member_7;
}
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
_8_t *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::
    as_ptr(_8_t *) {
  if (current != 8)
    return nullptr;
  return member_8;
}
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
_9_t *
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::
    as_ptr(_9_t *) {
  if (current != 9)
    return nullptr;
  return member_9;
}
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
heap_variant_t<_0_t, _1_t, _2_t, _3_t, _4_t, _5_t, _6_t, _7_t, _8_t, _9_t>::
    ~heap_variant_t() {
  switch (current) {
  case 0:
    delete member_0;
    break;
  case 1:
    delete member_1;
    break;
  case 2:
    delete member_2;
    break;
  case 3:
    delete member_3;
    break;
  case 4:
    delete member_4;
    break;
  case 5:
    delete member_5;
    break;
  case 6:
    delete member_6;
    break;
  case 7:
    delete member_7;
    break;
  case 8:
    delete member_8;
    break;
  case 9:
    delete member_9;
    break;
  };
}
}//[mto.module-end]
namespace mto::no_stl::variant {//[mto.ns-compatibility]
  using namespace mto::no_stl::variant::heap_variant;//[mto]
}//[mto]
