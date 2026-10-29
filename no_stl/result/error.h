#pragma once

//[mto.import ./result]
//[mto.import no_stl/string/string:string_t]
//[mto.import no_stl/vector/vector:vector_t]

//[mto-gen.begin]
#include "./result.h"
#include "no_stl/string/string.h"
#include "no_stl/vector/vector.h"
namespace mto::no_stl::result::error {
namespace result = mto::no_stl::result::result;
using mto::no_stl::string::string::string_t;
using mto::no_stl::vector::vector::vector_t;
}
#include "cpp_tools/defines.h"
//[mto-gen.end]
//[mto]
namespace mto::no_stl::result::error {//[mto.module-begin]

/**
 * generic error type with a message string, for when specific
 * type is not required.
 */
struct error_t {
  string_t msg;
};

struct empty_t {};

template <typename _t = empty_t>
using result_t = result::result_t<_t, error_t>;

/**
 * helpers
 */
struct arg_t {
  string_t name;
  string_t value;
};

error_t
func_error(string_t const &func_name, vector_t<arg_t> const &args);

}//[mto.module-end]
