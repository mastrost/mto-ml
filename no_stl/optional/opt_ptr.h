#pragma once

//[mto.import cpp_tools/contract:REQUIRES#]

//[mto-gen.begin]
#include "cpp_tools/contract.h"
namespace mto::no_stl::optional::opt_ptr {
}
#include "cpp_tools/defines.h"
//[mto-gen.end]
//[mto]
namespace mto::no_stl::optional::opt_ptr {//[mto.module-begin]

template <typename _t>
struct opt_ptr_t {
public:
  opt_ptr_t(_t *_p) : p(_p) {
  }

  template <typename _s>
  opt_ptr_t(opt_ptr_t<_s> _q) : p(_q.p) {
  }

  void operator=(_t *_p) {
    p = _p;
  }

  template <typename _s>
  void operator=(opt_ptr_t<_s> _q) {
    p = _q.p;
  }

  _t *get_if() const {
    return p;
  }

  _t *operator*() const {
    REQUIRES(p);
    return p;
  }

  operator bool() const {
    return p != nullptr;
  }

  bool operator==(_t *_p) const {
    return p == _p;
  }

  template <typename _s>
  bool operator==(opt_ptr_t<_s> _q) const {
    return p == _q.p;
  }

  _t *p;
};

}//[mto.module-end]
