#pragma once

#include "cpp_tools/defines.h"
namespace mto::traits {

template <typename value_trait_t>
struct iterable_trait_t {
  typedef value_trait_t const *iterator_trait_t;

  iterator_trait_t begin() const;
  iterator_trait_t end() const;
};

}
