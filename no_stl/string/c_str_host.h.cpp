#include "./c_str_host.h"

namespace mto::no_stl::string::c_str_host {
}
#include "cpp_tools/defines.h"
namespace mto::no_stl::string::c_str_host {

c_str_host_t c_str_host(string_view_t str) {
  vector::vector_t<char> c_str_buf;
  for (let c : str) {
    c_str_buf.push_back(c);
  }
  c_str_buf.push_back(0);
  return {no_stl::move(c_str_buf)};
}

}
