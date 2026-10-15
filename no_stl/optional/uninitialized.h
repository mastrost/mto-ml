#pragma once

#include <new>

/**
 * TODO: refactorer/deplacer dans no_stl/uninitialized
 */

#include "./../utility.h"
namespace mto::no_stl::optional::uninitialized {
using mto::no_stl::utility::move;
}
#include "cpp_tools/defines.h"
namespace mto::no_stl::optional::uninitialized {

template <typename _t>
struct uninitialized_t {

  _t *get() {
    return reinterpret_cast<_t *>(data);
  }

  _t const *get() const {
    return reinterpret_cast<_t const *>(data);
  }

  void copy_initialize(_t x) {
    new (data) _t(x);
  }

  void move_initialize(_t &&x) {
    new (data) _t(no_stl::move(x));
  }

  void _delete() {
    (*get()).~_t();
  }

  uninitialized_t() {}
  uninitialized_t(uninitialized_t const &) = delete;
  uninitialized_t(uninitialized_t &&) = delete;
  void operator=(uninitialized_t const &) = delete;
  void operator=(uninitialized_t &&) = delete;

  alignas(alignof(_t)) char data[sizeof(_t)];
};

#ifdef IDE
template struct uninitialized_t<int>;
#endif

}
