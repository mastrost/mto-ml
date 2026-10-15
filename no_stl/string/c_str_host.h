#pragma once

#include "./string_view.h"

#include "./../vector/vector.h"
namespace mto::no_stl::string::c_str_host {
using mto::no_stl::vector::vector::vector_t;
}
#include "cpp_tools/defines.h"
namespace mto::no_stl::string::c_str_host {


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

}
