#pragma once

#include "cpp_tools/defines.h"//[mto]
namespace mto::traits {//[mto.ns_begin]

template <typename value_trait_t>
struct iterable_trait_t {
  typedef value_trait_t const *iterator_trait_t;

  iterator_trait_t begin() const;
  iterator_trait_t end() const;
};

}//[mto.ns_end]
