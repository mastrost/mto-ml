#pragma once

//[mto.import no_stl/byte/byte:byte_t]
//[mto.import no_stl/utility]
//[mto.import no_stl/tools/static_for:static_for_]
#include <new>

//[mto-gen.begin]
#include "no_stl/byte/byte.h"
#include "no_stl/utility.h"
#include "no_stl/tools/static_for.h"
namespace mto::no_stl::uninitialized::uninitialized_static_array {
using mto::no_stl::byte::byte::byte_t;
namespace utility = mto::no_stl::utility;
using mto::no_stl::tools::static_for::static_for_;
}
#include "cpp_tools/defines.h"
//[mto-gen.end]
//[mto]
namespace mto::no_stl::uninitialized::uninitialized_static_array {//[mto.module-begin]

/**
 * uninitialized_static_array_itf_t est un mixin utilisé pour
 *  - uninitialized_static_array_view_t et
 *  - uninitialized_static_array_t
 */
template <typename _t, size_t size, typename byte_ptr_t, size_t alignment>
struct uninitialized_static_array_itf_t {
  /**
   * get(i)
   */
  template <size_t i>
  _t &get() {
    return reinterpret_cast<_t &>(*data_of<i>());
  }

  _t &get(size_t i) {
    return reinterpret_cast<_t &>(*data_of(i));
  }

  template <size_t i>
  _t const &get() const {
    return reinterpret_cast<_t const &>(*data_of<i>());
  }

  _t const &get(size_t i) const {
    return reinterpret_cast<_t const &>(*data_of(i));
  }

  _t const * begin() const {
    return reinterpret_cast<_t const *>(data_of<0>());
  }

  _t const * end() const {
    let * p = data + sizeof(_t) * size;
    return reinterpret_cast<_t const *>(p);
  }

  _t * begin() {
    return reinterpret_cast<_t *>(data_of<0>());
  }

  _t * end() {
    auto * p = data + sizeof(_t) * size;
    return reinterpret_cast<_t *>(p);
  }

  /**
   * [copy,move]_initialize(i)
   */

  template <size_t i>
  void default_initialize() {
    new (data_of<i>()) _t;
  }

  void default_initialize(size_t i) {
    new (data_of(i)) _t;
  }

  template <size_t i>
  void copy_initialize(_t const& x) {
    new (data_of<i>()) _t(x);
  }

  void copy_initialize(size_t i, _t const& x) {
    new (data_of(i)) _t(x);
  }

  template <size_t i>
  void move_initialize(_t &&x) {
    new (data_of<i>()) _t(utility::move(x));
  }

  void move_initialize(size_t i, _t &&x) {
    new (data_of(i)) _t(utility::move(x));
  }

  /**
   */
  void _delete() {
    static_for_<0, size>([this]<size_t i>() {
      (this->get<size - 1 - i>()).~_t();
    });
  }

  alignas(alignment) byte_ptr_t data;

private:
  template <size_t i>
  byte_t *data_of() {
    static_assert(i < size);
    return data + sizeof(_t) * i;
  }

  template <size_t i>
  byte_t const *data_of() const {
    static_assert(i < size, "static array out of range");
    return data + sizeof(_t) * i;
  }

  byte_t *data_of(size_t i) {
    return data + sizeof(_t) * i;
  }

  byte_t const *data_of(size_t i) const {
    return data + sizeof(_t) * i;
  }
};

template <typename _t, size_t size>
struct uninitialized_static_array_view_t : uninitialized_static_array_itf_t<_t, size, byte_t *, alignof(byte_t *)> {
};

template <typename _t, size_t size>
struct uninitialized_static_array_t : uninitialized_static_array_itf_t<_t, size, byte_t[sizeof(_t) * size], alignof(_t)> {
public:
  uninitialized_static_array_view_t<_t, size> view_of() {
    return uninitialized_static_array_view_t<_t, size>{{this->data}};
  }

  uninitialized_static_array_t get_initialized_copy_of() const {
    uninitialized_static_array_t res;
    static_for_<0, size>([&res, this]<size_t i>() {
      res.template copy_initialize<i>(this->template get<i>());
    });
    return res;
  }

  uninitialized_static_array_t get_initialized_move_of() {
    uninitialized_static_array_t res;
    static_for_<0, size>([&res, this]<size_t i>() {
      res.template move_initialize<i>(utility::move(this->template get<i>()));
    });
    return res;
  }

  uninitialized_static_array_t() {}

private:
  uninitialized_static_array_t(uninitialized_static_array_t const &) = default;
  uninitialized_static_array_t(uninitialized_static_array_t &&) = default;
  uninitialized_static_array_t &operator=(uninitialized_static_array_t const &) = default;
  uninitialized_static_array_t &operator=(uninitialized_static_array_t &&) = default;
};

#ifdef IDE
template struct uninitialized_static_array_t<float, 12>;
#endif

}//[mto.module-end]
 
namespace mto::no_stl::uninitialized {//[mto.ns-compatibility]
  using namespace mto::no_stl::uninitialized::uninitialized_static_array;//[mto]
}//[mto]
