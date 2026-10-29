//[mto.import ./file_utils]
//[mto.import no_stl/result/error]

#include <fstream>

//[mto-gen.begin]
#include "./file_utils.h"
#include "no_stl/result/error.h"
namespace mto::no_stl::system::file::file_utils {
namespace file_utils = mto::no_stl::system::file::file_utils;
namespace error = mto::no_stl::result::error;
}
#include "cpp_tools/defines.h"
//[mto-gen.end]
//[mto]
namespace mto::no_stl::system::file::file_utils {//[mto.module-begin]

result_t<vector_t<string_t>>
read_lines(string_t const &path) {
  vector_t<string_t> lines;
  std::ifstream file(path.c_str_host().c_str());
  if (!file.good()) {
    return error::func_error("read_lines", {{"path", path}});
  }
  // return func_error("read_lines", {"path", path});
  REQUIRES(file.good());
  std::string line;
  while (std::getline(file, line)) {
    lines.push_back(line.c_str());
  }
  return lines;
}

}//[mto.module-end]
