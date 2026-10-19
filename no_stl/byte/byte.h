#pragma once

#include <cstddef>

//[mto-gen.begin]
namespace mto::no_stl::byte::byte {
}
#include "cpp_tools/defines.h"
//[mto-gen.end]
//[mto]
namespace mto::no_stl::byte::byte {//[mto.module-begin]

using byte_t = std::byte;

}//[mto.module-end]
 
namespace mto::no_stl::byte {//[mto.ns-compatibility]
  using namespace mto::no_stl::byte::byte;//[mto]
}//[mto]
