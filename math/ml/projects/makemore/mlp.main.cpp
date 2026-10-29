//[mto.import cpp_tools/main:MAIN#]

//[mto.import no_stl/result/error:result_t,error_t,empty_t]

#include <cstdio>

//[mto-gen.begin]
#include "cpp_tools/main.h"
#include "no_stl/result/error.h"
namespace mto::math::ml::projects::makemore::mlp {
using mto::no_stl::result::error::result_t;
using mto::no_stl::result::error::error_t;
using mto::no_stl::result::error::empty_t;
}
#include "cpp_tools/defines.h"
//[mto-gen.end]
//[mto]
namespace mto::math::ml::projects::makemore::mlp {//[mto.module-begin]

result_t<> run(int argc, char const **argv) {
  // model:
  //  - lookup (= 3)
  //  - embedding of letters in 'n_embd' dimensions
  //   -> same embedding whatever the position of the letter (k,k-1,k-2 ..)
  //  - embeddings of letters k,k-1,k-2,... concatanated as input of
  //    the hidden layer (i.e. `n_embd * 3` inputs)
  //  - hidden layer: 200 tanh neurons (n_embd * lookup -> 200)
  //  - output layer: linear projection (linear neurons, no bias) -> 27 logits
  //  - softmax 
  //  - nll loss
  return empty_t{};
}

MAIN(argc, argv) {
  let res = run(argc, argv);
  if (!res) {
    fprintf(stderr, "Error: %s\n", res.get_error().msg.c_str_host().c_str());
    return 1;
  }
  return 0;
}

}//[mto.module-end]
