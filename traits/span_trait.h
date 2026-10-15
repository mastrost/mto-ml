#pragma once

#include "./iterable_trait.h"

#include "cpp_tools/defines.h"//[mto]
namespace mto::traits {//[mto.ns_begin]

template <typename value_trait_t, typename index_trait_t>
struct span_trait_t : iterable_trait_t<value_trait_t>{
    value_trait_t & operator[](index_trait_t) const;
    index_trait_t size() const;
};

}//[mto.ns_end]

