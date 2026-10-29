//[mto.import ./error]

//[mto-gen.begin]
#include "./error.h"
namespace mto::no_stl::result::error {
namespace error = mto::no_stl::result::error;
}
#include "cpp_tools/defines.h"
//[mto-gen.end]
//[mto]
namespace mto::no_stl::result::error {//[mto.module-begin]

error_t
func_error(string_t const &func_name, vector_t<arg_t> const &args) {
  string_t msg;
  msg += func_name + "(";
  for (let i : args.foreach_index()) {
    if (i > 0) {
      msg += ", ";
    }
    msg += args[i].name + "=" + args[i].value;
  }
  msg += ") failed";
  return {msg};
}

}//[mto.module-end]
