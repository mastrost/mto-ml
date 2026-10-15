#pragma once

//[mto.import traits/index_trait]
//[mto.import no_stl/span/span]
//[mto.import no_stl/span/uninitialized_buffer:uninitialized_buffer_t]
//[mto.import no_stl/utility as no_stl_utility]
#include <cstdlib>
#include <initializer_list>

//[mto-gen.begin]
#include "traits/index_trait.h"
#include "no_stl/span/span.h"
#include "no_stl/span/uninitialized_buffer.h"
#include "no_stl/utility.h"
namespace mto::no_stl::vector::vector {
namespace index_trait = mto::traits::index_trait;
namespace span = mto::no_stl::span::span;
using mto::no_stl::span::uninitialized_buffer::uninitialized_buffer_t;
namespace no_stl_utility = mto::no_stl::utility;
}
#include "cpp_tools/defines.h"
//[mto-gen.end]
//[mto]
namespace mto::no_stl::vector::vector {//[mto.module-begin]

template <typename tag_t>
using value_trait_t = index_trait::c_array_value_trait_t<tag_t>;

template <typename tag_t>
using index_trait_t = index_trait::c_array_iterator_trait_t<tag_t>;

template <typename value_trait_t, typename index_trait_t = size_t>
struct vector_t {
public:
  typedef value_trait_t value_type;
  typedef index_trait_t index_type;
  typedef uninitialized_buffer_t<value_trait_t, index_trait_t> buffer_t;

  vector_t() : _size(index_type(0)),
               _buffer_size(index_type(0)),
               buffer{nullptr} {
  }

  template <typename src_value_trait_t, typename src_index_trait_t>
  explicit vector_t(span::span_t<src_value_trait_t const, src_index_trait_t> src)
      : vector_t() {
    for (let src_i : src.foreach_index()) {
      let dst_i = static_cast<src_index_trait_t>(src_i);
      (void)dst_i;
      push_back(static_cast<value_trait_t>(src[src_i]));
    }
  }

  template <typename src_value_trait_t, typename src_index_trait_t>
  explicit vector_t(vector_t<src_value_trait_t, src_index_trait_t> const &src)
      : vector_t(src.const_span_of()) {
  }

  vector_t(index_type init_size, value_type value) : vector_t() {
    while (size() < init_size) {
      push_back(value);
    }
  }

  /**
   * initialization en mode impératif
   */
  static vector_t create_uninitialized(index_type init_size) {
    return vector_t{uninit_t{init_size}};
  }

  void copy_initialize(index_type i, value_type const &x) {
    buffer.copy_initialize(i, x);
  }

  void move_initialize(index_type i, value_type &&x) {
    buffer.move_initialize(i, no_stl_utility::move(x));
  }

  vector_t(std::initializer_list<value_type> const &u) : vector_t() {
    for (let &elt : u) {
      push_back(elt);
    }
  }

  vector_t(vector_t const &u) : vector_t() {
    (*this) = u;
  }

  void operator=(vector_t const &u) {
    _free(_size, buffer);
    _size = u._size;
    _buffer_size = u._buffer_size;
    buffer = buffer_t{
        (char *)malloc(sizeof(value_type) * static_cast<size_t>(_buffer_size))};
    for (size_t i = 0; i < static_cast<size_t>(_size); ++i) {
      let index = index_type(i);
      buffer.init(index, u[index]);
    }
  }

  vector_t(vector_t &&u) : vector_t() {
    (*this) = no_stl_utility::move(u);
  }

  template <typename f_t>
  vector_t &apply(f_t const &f) & {
    for (auto &x : *this) {
      x = f(x);
    }
    return *this;
  }

  template <typename f_t>
  vector_t &&apply(f_t const &f) && {
    for (auto &x : *this) {
      x = f(x);
    }
    return no_stl_utility::move(*this);
  }

  template <typename dst_value_t, typename f_t>
  vector_t<dst_value_t, index_type> transform(f_t const &f) const {
    vector_t<dst_value_t, index_type> res;
    for (let &x : *this) {
      res.push_back(f(x));
    }
    return res;
  }

  void operator=(vector_t &&u) {
    _free(_size, buffer);

    _size = u._size;
    _buffer_size = u._buffer_size;
    buffer = u.buffer;

    u._size = index_type(0);
    u._buffer_size = index_type(0);
    u.buffer = buffer_t{nullptr};
  }

  ~vector_t() {
    _free(_size, buffer);
  }

  void push_back(value_type const &x) {
    let new_size = static_cast<size_t>(_size) + 1;
    adapt_buffer_size(new_size);
    buffer.init(_size, x);
    _size = index_type(new_size);
  }

  void push_back(value_type &&x) {
    let new_size = static_cast<size_t>(_size) + 1;
    adapt_buffer_size(new_size);
    buffer.init(_size, no_stl_utility::move(x));
    _size = index_type(new_size);
  }

  void pop_back() {
    REQUIRES(static_cast<size_t>(size()) > 0);
    buffer.as_initialized()[static_cast<size_t>(size()) - 1].~value_type();
    _size = index_type(static_cast<size_t>(size()) - 1);
  }

  value_type const &back() const {
    REQUIRES(static_cast<size_t>(_size) > 0);
    return buffer.as_initialized()[static_cast<size_t>(_size) - 1];
  }

  value_type &front() {
    REQUIRES(static_cast<size_t>(_size) > 0);
    return buffer.as_initialized()[static_cast<size_t>(0)];
  }

  value_type const &front() const {
    REQUIRES(static_cast<size_t>(_size) > 0);
    return buffer.as_initialized()[static_cast<size_t>(0)];
  }

  value_type &back() {
    REQUIRES(static_cast<size_t>(_size) > 0);
    return buffer.as_initialized()[static_cast<size_t>(_size) - 1];
  }

  value_type &operator[](index_type i) {
    REQUIRES(static_cast<size_t>(i) < static_cast<size_t>(_size));
    return buffer.as_initialized()[static_cast<size_t>(i)];
  }

  value_type const &operator[](index_type i) const {
    REQUIRES(static_cast<size_t>(i) < static_cast<size_t>(_size));
    return buffer.as_initialized()[static_cast<size_t>(i)];
  }

  value_type *data() {
    return buffer.as_initialized();
  }

  value_type const *data() const {
    return buffer.as_initialized();
  }

  index_type size() const {
    return _size;
  }

  index_type buffer_size() const {
    return _buffer_size;
  }

  bool is_empty() const {
    return size() == index_type(0);
  }

  value_type const *begin() const { return &buffer.as_initialized()[0]; }
  value_type const *end() const {
    return &buffer.as_initialized()[static_cast<size_t>(_size)];
  }

  value_type *begin() { return &buffer.as_initialized()[0]; }
  value_type *end() {
    return &buffer.as_initialized()[static_cast<size_t>(_size)];
  }

  span::foreach_index_t<index_type> foreach_index() const { return {_size}; }

  span::span_t<value_type const, index_type> const_span_of() const {
    return {buffer.as_initialized(), _size};
  }

  span::span_t<value_type const, index_type> span_of() const {
    return {buffer.as_initialized(), _size};
  }

  span::span_t<value_type, index_type> span_of() {
    return {buffer.as_initialized(), _size};
  }

  operator span::span_t<value_type const, index_type>() const {
    return {buffer.as_initialized(), _size};
  }

  operator span::span_t<value_type, index_type>() {
    return {buffer.as_initialized(), _size};
  }

private:
  struct uninit_t {
    index_type init_size;
  };

  vector_t(uninit_t uninit) : _size(uninit.init_size),
                              _buffer_size(uninit.init_size),
                              buffer{nullptr} {
    buffer = buffer_t{
        (char *)malloc(sizeof(value_type) * static_cast<size_t>(_buffer_size))};
  }

  void adapt_buffer_size(size_t new_size) {
    if (new_size > static_cast<size_t>(_buffer_size)) {
      let new_buffer_size = new_size * 2;
      auto new_buffer = buffer_t{
          (char *)malloc(sizeof(value_type) * new_buffer_size)};
      for (size_t i = 0; i < static_cast<size_t>(_size); ++i) {
        let index = index_type(i);
        new_buffer.init(index, no_stl_utility::move(buffer.as_initialized()[i]));
      }
      _free(_size, buffer);
      buffer = new_buffer;
      _buffer_size = index_type(new_buffer_size);
    }
    ASSERT(static_cast<size_t>(new_size) <= static_cast<size_t>(_buffer_size));
  }

  static void _free(index_type size, buffer_t buffer) {
    for (size_t i = 0; i < static_cast<size_t>(size); ++i) {
      buffer.as_initialized()[i].~value_type();
    }
    free(buffer.buffer);
  }

  index_type _size;
  index_type _buffer_size;
  buffer_t buffer;
};

#ifdef IDE
template struct vector_t<value_trait_t<struct value>, index_trait_t<struct index>>;
#endif

/**
 * comparison operators
 */
template <typename _t, typename i_t>
bool operator==(vector_t<_t, i_t> const &a,
                vector_t<_t, i_t> const &b) {
  if (static_cast<size_t>(a.size()) != static_cast<size_t>(b.size()))
    return false;

  for (size_t i = 0; i < static_cast<size_t>(a.size()); ++i) {
    let index = i_t(i);
    if (!(a[index] == b[index]))
      return false;
  }
  return true;
}

template <typename _t, typename i_t>
bool operator<(vector_t<_t, i_t> const &a,
               vector_t<_t, i_t> const &b) {
  let a_size = static_cast<size_t>(a.size());
  let b_size = static_cast<size_t>(b.size());

  size_t i = 0;
  while (i < a_size && i < b_size) {
    let index = i_t(i);
    if (a[index] < b[index])
      return true;
    else if (b[index] < a[index])
      return false;
    ++i;
  }

  return a_size < b_size;
}

template <typename _t, typename i_t>
bool operator!=(vector_t<_t, i_t> const &a,
                vector_t<_t, i_t> const &b) {
  return !(a == b);
}

/**
 * conversion depuis par exemple std::vector
 */
template <typename _t, typename i_t, typename iterator_t>
vector_t<_t, i_t> to_vector(iterator_t begin, iterator_t end) {
  vector_t<_t, i_t> res;
  for (auto it = begin; it != end; ++it) {
    res.push_back(*it);
  }
  return res;
}

template <typename _t, typename i_t = size_t, typename container_t>
vector_t<_t, i_t> container_to_vector(container_t const &u) {
  return to_vector<_t, i_t>(u.begin(), u.end());
}

// let std_u = to_std_vector<std::vector>(w);
template <template <class... _ts> class std_vector, typename _t, typename i_t>
std_vector<_t> to_std_vector(vector_t<_t, i_t> const &u) {
  std_vector<_t> res;
  for (let &x : u) {
    res.push_back(x);
  }
  return res;
}

template <typename dst_elt_t, typename src_elt_t, typename i_t = size_t>
vector_t<dst_elt_t>
cast_elements(vector_t<src_elt_t, i_t> const &src) {
  vector_t<dst_elt_t> dst;
  for (let &x : src) {
    dst.push_back(static_cast<dst_elt_t>(x));
  }
  return dst;
}

}//[mto.ns_end]

namespace mto::no_stl::vector {//[mto.ns-compatibility]
  using namespace mto::no_stl::vector::vector;//[mto]
}//[mto]
