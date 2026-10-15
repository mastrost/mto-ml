//[mto.import ./string_view]

//[mto-gen.begin]
#include "./string_view.h"
namespace mto::no_stl::string::string_view {
namespace string_view = mto::no_stl::string::string_view;
}
#include "cpp_tools/defines.h"
//[mto-gen.end]
//[mto]
namespace mto::no_stl::string::string_view {//[mto.module-begin]

bool string_view_t::operator==(string_view_t o) const {
  if (size() != o.size())
    return false;

  for (size_t i = 0; i < size(); ++i) {
    if ((*this)[i] != o[i])
      return false;
  }

  return true;
}

namespace literals {

string_view_t operator""_sv(char const *str, size_t size) {
  return {str, size};
}

}

}//[mto.module-end]
