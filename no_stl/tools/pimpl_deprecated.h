#pragma once

#include <utility>

#include "cpp_tools/defines.h"//[mto]
namespace mto::no_stl::tools {//[mto.ns_begin]


// suppose que l'impl est dans le champ 'impl'
template <typename itf_t, typename impl_t>
itf_t pimpl_to_itf(impl_t &&impl) {
  itf_t itf;
  new (itf.impl)(impl_t)(std::forward<impl_t>(impl));
  return itf;
}

} // namespace mto::no_stl::tools
