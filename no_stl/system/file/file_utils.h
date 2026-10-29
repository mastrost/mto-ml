#pragma once

//[mto.import no_stl/result/error:result_t]
//[mto.import no_stl/vector/vector:vector_t]
//[mto.import no_stl/string/string:string_t]

//[mto-gen.begin]
#include "no_stl/result/error.h"
#include "no_stl/vector/vector.h"
#include "no_stl/string/string.h"
namespace mto::no_stl::system::file::file_utils {
using mto::no_stl::result::error::result_t;
using mto::no_stl::vector::vector::vector_t;
using mto::no_stl::string::string::string_t;
}
#include "cpp_tools/defines.h"
//[mto-gen.end]
//[mto]
namespace mto::no_stl::system::file::file_utils {//[mto.module-begin]

result_t<vector_t<string_t>>
read_lines(string_t const &path);

}//[mto.module-end]
