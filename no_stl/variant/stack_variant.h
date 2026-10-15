#pragma once
#include "./heap_variant.h"

//[mto-gen.begin]
namespace mto::no_stl::variant::stack_variant {
}
#include "cpp_tools/defines.h"
//[mto-gen.end]
//[mto]
namespace mto::no_stl::variant::stack_variant {//[mto.module-begin]

/**
 * TODO: meme code généré que heap_variant, sauf
 *  - ajout d'un membre char data[max(sizoef(T...))];
 *  - new remplacé par placement new
 *  - delete remplacé par appel au destructeur explicite
 *  -> l'union des pointeurs ne change pas, et donc le reste du code non plus
 */
template <typename... _ts>
using stack_variant_t = heap_variant_t<_ts...>;

}//[mto.module-end]

namespace mto::no_stl::variant {//[mto.ns-compatibility]
  using namespace mto::no_stl::variant::stack_variant;//[mto]
}//[mto]
