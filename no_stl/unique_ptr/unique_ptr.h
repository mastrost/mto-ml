#pragma once

namespace mto::no_stl::unique_ptr::unique_ptr {
}
#include "cpp_tools/defines.h"
namespace mto::no_stl::unique_ptr::unique_ptr {

template <typename _t>
struct unique_ptr_t {
public:
  unique_ptr_t() : p(nullptr) {}
  unique_ptr_t(unique_ptr_t<_t> const &) = delete;
  unique_ptr_t<_t> &operator=(unique_ptr_t<_t> const &) = delete;

  unique_ptr_t(_t *p) : p(p) {}

  template <typename _s>
  unique_ptr_t(unique_ptr_t<_s> &&o) {
    p = o.get();
    o.release();
  }

  template <typename _s>
  unique_ptr_t &operator=(unique_ptr_t<_s> &&o) {
    delete p;
    p = o.get();
    o.release();
    return *this;
  }

  bool operator==(unique_ptr_t const &o) const {
    if (!get() && !o.get())
      return true;
    if (!get() && o.get())
      return false;
    if (get() && !o.get())
      return false;
    return (**this) == *o;
  }

  explicit operator bool() const {
    return p != nullptr;
  }

  ~unique_ptr_t() { delete p; }

  _t &operator*() const { return *p; }
  _t *operator->() const { return p; }
  _t *get() const { return p; }
  void release() { p = nullptr; }

private:
  _t *p;
};

}

namespace mto::no_stl::unique_ptr {
  using namespace mto::no_stl::unique_ptr::unique_ptr;
}
