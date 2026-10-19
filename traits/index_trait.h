#pragma once

//[mto-gen.begin]
namespace mto::traits::index_trait {
}
#include "cpp_tools/defines.h"
//[mto-gen.end]
//[mto]
namespace mto::traits::index_trait {//[mto.module-begin]

/**
 * utilisable pour indexer une zone memoire C.
 */
template <typename tag_t>
struct c_array_index_trait_t {
  explicit c_array_index_trait_t(size_t);
  explicit operator size_t() const;
};

/**
 * comme `c_array_index_trait_base_t` mais utilisable en plus
 * comme iterateur
 */
template <typename tag_t>
struct c_array_iterator_trait_t : c_array_index_trait_t<tag_t> {
  explicit c_array_iterator_trait_t(size_t);
  void operator++();
  void operator--();
  c_array_iterator_trait_t operator++(int);
  c_array_iterator_trait_t operator--(int);
  c_array_iterator_trait_t operator+(c_array_iterator_trait_t const &) const;
  c_array_iterator_trait_t operator-(c_array_iterator_trait_t const &) const;
  void operator+=(c_array_iterator_trait_t);
  void operator-=(c_array_iterator_trait_t);
  bool operator==(c_array_iterator_trait_t<tag_t> const &b) const;
  bool operator<(c_array_iterator_trait_t<tag_t> const &b) const;
  bool operator!=(c_array_iterator_trait_t<tag_t> const &b) const;
  bool operator>(c_array_iterator_trait_t<tag_t> const &b) const;
};

template <typename tag_t>
using index_trait_t = c_array_iterator_trait_t<tag_t>;

/**
 * sizeof devrait suffir en pratique
 */
template <typename tag_t>
struct c_array_value_trait_t {};

}//[mto.module-end]

namespace mto::traits {//[mto.ns-compatibility]
  using namespace mto::traits::index_trait;//[mto]
}//[mto]
