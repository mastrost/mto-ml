#pragma once

#include "./string_view.h"
//[mto.import ../vector/vector:vector_t]

//[mto-gen.begin]
#include "./../vector/vector.h"
namespace mto::no_stl::string::c_str_host {
using mto::no_stl::vector::vector::vector_t;
}
#include "cpp_tools/defines.h"
//[mto-gen.end]
//[mto]
namespace mto::no_stl::string::c_str_host {//[mto.module-begin]


struct c_str_host_t {
  char const *c_str() const {
    return buf.data();
  }

  operator char const *() const {
    return c_str();
  }

  vector_t<char> buf;
};

c_str_host_t c_str_host(string_view_t str);

}//[mto.module-end]
