#pragma once

#include "traits/index_trait.h"
//[mto.import no_stl/utility]
#include <new>

/**
 * TODO: refactorer/deplacer dans no_stl/uninitialized
 */
//[mto-gen.begin]
#include "no_stl/utility.h"
namespace mto::no_stl::span::uninitialized_buffer {
namespace utility = mto::no_stl::utility;
}
#include "cpp_tools/defines.h"
//[mto-gen.end]
//[mto]
namespace mto::no_stl::span::uninitialized_buffer {//[mto.module-begin]

template <typename c_array_value_trait_t, typename c_array_index_trait_t>
struct uninitialized_buffer_t {
  typedef c_array_value_trait_t value_type;
  typedef c_array_index_trait_t index_type;

  template <typename... args_t>
  inline void init(index_type i, args_t &&...args) const {
    new (buffer + static_cast<size_t>(i) * sizeof(value_type)) value_type(utility::forward<args_t>(args)...);
  }

  inline void copy_initialize(index_type i, value_type const &x) const {
    new (buffer + static_cast<size_t>(i) * sizeof(value_type)) value_type(x);
  }

  inline void move_initialize(index_type i, value_type &&x) const {
    new (buffer + static_cast<size_t>(i) * sizeof(value_type)) value_type(utility::move(x));
  }

  value_type *as_initialized() const {
    return reinterpret_cast<value_type *>(buffer);
  }

  char *buffer;
};

#ifdef IDE
template struct uninitialized_buffer_t<traits::c_array_value_trait_t<struct value>,
                                       traits::c_array_index_trait_t<struct index>>;
#endif

}//[mto.ns_end]
