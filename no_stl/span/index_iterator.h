#pragma once

#include "traits/index_trait.h"

//[mto-gen.begin]
namespace mto::no_stl::span::index_iterator {
}
#include "cpp_tools/defines.h"
//[mto-gen.end]
//[mto]
namespace mto::no_stl::span::index_iterator {//[mto.module-begin]

/**
 * index
 */
template <typename c_array_iterator_trait_t>
struct index_iterator_t {
  c_array_iterator_trait_t index;

  void operator++() { ++index; }
  bool operator!=(index_iterator_t o) { return index != o.index; };
  c_array_iterator_trait_t operator*() { return index; }
};

template <typename c_array_iterator_trait_t>
struct foreach_index_t {
  using iterator_t = index_iterator_t<c_array_iterator_trait_t>;
  iterator_t begin() const { return {c_array_iterator_trait_t{0}}; }
  iterator_t end() const { return {size}; }
  c_array_iterator_trait_t size;
};

/**
 * rindex
 */
template <typename c_array_iterator_trait_t>
struct rindex_iterator_t {
  c_array_iterator_trait_t index;

  void operator++() { --index; }
  bool operator!=(rindex_iterator_t o) { return index != o.index; };
  c_array_iterator_trait_t operator*() { return index; }
};

template <typename c_array_iterator_trait_t>
struct foreach_rindex_t {
  using iterator_t = rindex_iterator_t<c_array_iterator_trait_t>;
  iterator_t begin() const { return {size - c_array_iterator_trait_t{1}}; }
  iterator_t end() const { return {c_array_iterator_trait_t(-1)}; }
  c_array_iterator_trait_t size;
};

#ifdef IDE
template struct index_iterator_t<traits::c_array_iterator_trait_t<struct index>>;
template struct foreach_index_t<traits::c_array_iterator_trait_t<struct index>>;

template struct rindex_iterator_t<traits::c_array_iterator_trait_t<struct index>>;
template struct foreach_rindex_t<traits::c_array_iterator_trait_t<struct index>>;
#endif

}//[mto.module-end]
