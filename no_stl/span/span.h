#pragma once

//[mto.import ./index_iterator:foreach_index_t,foreach_rindex_t]
#include "traits/span_trait.h"
#include "traits/index_trait.h"
//[mto.import no_stl/utility:remove_cv]
#include "cpp_tools/contract.h"

//[mto-gen.begin]
#include "./index_iterator.h"
#include "no_stl/utility.h"
namespace mto::no_stl::span::span {
using mto::no_stl::span::index_iterator::foreach_index_t;
using mto::no_stl::span::index_iterator::foreach_rindex_t;
using mto::no_stl::utility::remove_cv;
}
#include "cpp_tools/defines.h"
//[mto-gen.end]
//[mto]
namespace mto::no_stl::span::span {//[mto.module-begin]

template <typename c_array_value_trait_t, typename c_array_iterator_trait_t = size_t>
struct span_t {
  typedef c_array_value_trait_t element_type;
  typedef c_array_iterator_trait_t index_type;
  typedef typename remove_cv<element_type>::type value_type;

  element_type &operator[](index_type index) const {
    REQUIRES(static_cast<size_t>(index) < static_cast<size_t>(_size));
    return _data[static_cast<size_t>(index)];
  }

  element_type &back() {
    REQUIRES(static_cast<size_t>(_size) > 0);
    return _data[static_cast<size_t>(_size) - 1];
  }

  element_type const &back() const {
    REQUIRES(static_cast<size_t>(_size) > 0);
    return _data[static_cast<size_t>(_size) - 1];
  }

  element_type *data() const {
    return _data;
  }

  index_type size() const {
    return _size;
  }

  bool is_empty() const {
    return _size == index_type(0);
  }

  span_t slice(index_type first) const {
    REQUIRES(static_cast<size_t>(first) <= static_cast<size_t>(_size));
    return {
        _data + static_cast<size_t>(first),
        index_type(static_cast<size_t>(_size) - static_cast<size_t>(first)),
    };
  }

  span_t slice(index_type first, index_type size) const {
    REQUIRES(static_cast<size_t>(first) <= static_cast<size_t>(_size));
    REQUIRES(static_cast<size_t>(first + size) <= static_cast<size_t>(_size));
    return {
        _data + static_cast<size_t>(first),
        size,
    };
  }

  element_type *begin() const { return _data; }
  element_type *end() const { return _data + static_cast<size_t>(_size); }

  foreach_index_t<index_type> foreach_index() const { return {_size}; }
  foreach_rindex_t<index_type> foreach_rindex() const { return {_size}; }

  element_type *_data;
  index_type _size;

  template <typename span_trait_t>
  static span_t create(span_trait_t const &span) {
    return {span.data(), span.size()};
  }

  operator span_t<value_type const, index_type>() const {
    return {data(), size()};
  }

  template <typename value_t, typename index_t>
  static span_t create_with_reinterpret_cast(value_t *p, index_t size) {
    static_assert(sizeof(value_t) == sizeof(value_type));
    return {
        reinterpret_cast<element_type *>(p),
        static_cast<index_type>(size)};
  }

  template <typename x_t, typename i_t>
  static span_t create_with_reinterpret_cast(span_t<x_t, i_t> span) {
    static_assert(sizeof(*span.data()) == sizeof(value_type), "Cannot cast to desired span type");
    return {
        reinterpret_cast<element_type *>(span.data()),
        static_cast<index_type>(span.size()),
    };
  }

  // static cast
  template <typename dst_value_t, typename dst_index_t>
  explicit operator span_t<dst_value_t, dst_index_t>() const {
    static_assert(sizeof(dst_value_t) == sizeof(value_type), "Cannot cast to desired span type");
    return {
        static_cast<dst_value_t *>(data()),
        static_cast<dst_index_t>(size()),
    };
  }
};

template <typename value_t, typename index_t = size_t>
using cspan_t = span_t<value_t const, index_t>;

#ifdef IDE
template struct span_t<
    traits::c_array_value_trait_t<struct value>,
    traits::c_array_iterator_trait_t<struct index>>;
#endif

/**
 * utile pour convertir std::vector<> en span_t
 */
template <template <typename, typename...> class container, typename value_t, typename... other>
span_t<value_t const, size_t> span_of(container<value_t, other...> const &u) {
  return {u.data(), u.size()};
}

}//[mto.module-end]

namespace mto::no_stl::span {//[mto.ns-compatibility]
  using namespace mto::no_stl::span::span;//[mto]
}//[mto]
