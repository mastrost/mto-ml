#pragma once

//[mto.import no_stl/utility]
//[mto.import no_stl/uninitialized/uninitialized_static_array:uninitialized_static_array_t,uninitialized_static_array_view_t]
//[mto.import no_stl/tools/static_for:static_for_]
//[mto.import no_stl/span/span:foreach_index_t]
#include "cpp_tools/contract.h"
#include <initializer_list>

//[mto-gen.begin]
#include "no_stl/utility.h"
#include "no_stl/uninitialized/uninitialized_static_array.h"
#include "no_stl/tools/static_for.h"
#include "no_stl/span/span.h"
namespace mto::no_stl::array::array {
namespace utility = mto::no_stl::utility;
using mto::no_stl::uninitialized::uninitialized_static_array::uninitialized_static_array_t;
using mto::no_stl::uninitialized::uninitialized_static_array::uninitialized_static_array_view_t;
using mto::no_stl::tools::static_for::static_for_;
using mto::no_stl::span::span::foreach_index_t;
}
#include "cpp_tools/defines.h"
//[mto-gen.end]
//[mto]
namespace mto::no_stl::array::array {//[mto.module-begin]

struct value_trait_t {
  bool operator<(value_trait_t const &) const;
  bool operator==(value_trait_t const &) const;
};

struct index_trait_t {
  explicit index_trait_t(int _x);
  operator int() const;
};

template <typename value_trait_t, typename index_trait_t, size_t _size>
struct array_t {
public:
  typedef value_trait_t value_type;

  array_t(std::initializer_list<value_trait_t> init_elts) {
    REQUIRES(init_elts.size() == _size);
    size_t i = 0;
    for (let &elt : init_elts) {
      _data.copy_initialize(i, elt);
      ++i;
    }
  }

  array_t() {
    static_for_<0, _size>([this]<size_t i>() {
      this->_data.default_initialize(i);
    });
  }

  ~array_t() {
    _data._delete();
  }

  array_t(array_t const &o) : _data(o._data.get_initialized_copy_of()) {}

  array_t(array_t &&o) : _data(o._data.get_initialized_move_of()) {}

  void operator=(array_t const &o) {
    static_for_<0, _size>([this, &o]<size_t i>() {
      this->get<i>() = o.template get<i>();
    });
  }

  void operator=(array_t &&o) {
    static_for_<0, _size>([this, &o]<size_t i>() {
      this->get<i>() = utility::move(o.template get<i>());
    });
  }

  /**
   * initialization en mode impératif
   **/
  static array_t create_uninitialized() {
    return array_t{uninit_t{}};
  }

  void copy_initialize(index_trait_t i, value_type const &x) {
    _data.copy_initialize(static_cast<size_t>(i), x);
  }

  void move_initialize(index_trait_t i, value_type &&x) {
    _data.move_initialize(static_cast<size_t>(i), utility::move(x));
  }

  template <size_t i>
  void copy_initialize(value_type const &x) {
    _data.template copy_initialize<i>(x);
  }

  template <size_t i>
  void move_initialize(value_type &&x) {
    _data.template move_initialize<i>(utility::move(x));
  }

  uninitialized_static_array_view_t<value_trait_t, _size> get_uninitialized_data() {
    return _data.view_of();
  }

  /**
   * iterators
   */
  inline value_trait_t const *begin() const { return _data.begin(); }
  inline value_trait_t const *end() const { return _data.end(); }

  inline value_trait_t *begin() { return _data.begin(); }
  inline value_trait_t *end() { return _data.end(); }

  static constexpr index_trait_t size() {
    return index_trait_t(_size);
  }

  inline int8_t compare(array_t const &o) const {
    for (size_t i = 0; i < _size; ++i) {
      if ((*this)[index_trait_t(i)] < o[index_trait_t(i)])
        return -1;
      else if ((*this)[index_trait_t(i)] == o[index_trait_t(i)])
        continue;
      else
        return 1;
    }
    return 0;
  }

  inline bool operator==(array_t const &o) const {
    for (size_t i = 0; i < _size; ++i) {
      if ((*this)[index_trait_t(i)] != o[index_trait_t(i)]) {
        return false;
      }
    }
    return true;
  }

  inline bool operator!=(array_t const &o) const {
    return compare(o) != 0;
  }

  inline bool operator<(array_t const &o) const {
    return compare(o) < 0;
  }

  inline bool operator>(array_t const &o) const {
    return compare(o) > 0;
  }

#if 0
  // c++20
  // (il faut que (le constructeur de) index_trait_t soit constexpr)

  template <index_trait_t i>
  inline value_trait_t const &get() const;

  template <size_t i>
  inline value_trait_t &get();

#else
  template <size_t i>
  inline value_trait_t const &get() const {
    return _data.template get<i>();
  }

  template <size_t i>
  inline value_trait_t &get() {
    return _data.template get<i>();
  }
#endif

  inline value_trait_t const &operator[](index_trait_t i) const {
    return _data.get(i);
  }

  inline value_trait_t &operator[](index_trait_t i) {
    return _data.get(i);
  }

  value_trait_t const *data() const {
    return &get<0>();
  }

  value_trait_t *data() {
    return &get<0>();
  }

  span::foreach_index_t<index_trait_t> foreach_index() const {
    return {size()};
  }

  template <typename dst_value_trait_t, typename dst_index_trait_t>
  explicit operator array_t<dst_value_trait_t, dst_index_trait_t, _size>() const {
    typedef array_t<dst_value_trait_t, dst_index_trait_t, _size> dst_t;
    auto dst = dst_t::create_uninitialized();
    auto uninit = dst.get_uninitialized_data();
    for (let i : foreach_index()) {
      let dst_i = static_cast<dst_index_trait_t>(i);
      uninit.copy_initialize(static_cast<size_t>(dst_i),
                             static_cast<dst_value_trait_t>((*this)[i]));
    }
    return dst;
  }

private:
  struct uninit_t {};
  array_t(uninit_t) {}

  uninitialized_static_array_t<value_trait_t, _size> _data;
};

template <size_t i, typename v_t, typename i_t, size_t size>
v_t const &get(array_t<v_t, i_t, size> const &array) {
  return array.template get<i>();
}

template <size_t i, typename v_t, typename i_t, size_t size>
v_t &get(array_t<v_t, i_t, size> &array) {
  return array.template get<i>();
}

#ifdef IDE
template struct array_t<value_trait_t, index_trait_t, 3>;
template value_trait_t &array_t<value_trait_t, index_trait_t, 3>::get<1>();
#endif

}//[mto.module-end]

namespace mto::no_stl::array {//[mto.ns-compatibility]
  using namespace mto::no_stl::array::array;//[mto]
}//[mto]
