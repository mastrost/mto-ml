#pragma once
#include "./heap_variant.h"

namespace mto::no_stl::variant::stack_variant {
}
#include "cpp_tools/defines.h"
namespace mto::no_stl::variant::stack_variant {

/**
 * TODO: meme code généré que heap_variant, sauf
 *  - ajout d'un membre char data[max(sizoef(T...))];
 *  - new remplacé par placement new
 *  - delete remplacé par appel au destructeur explicite
 *  -> l'union des pointeurs ne change pas, et donc le reste du code non plus
 */
template <typename... _ts>
using stack_variant_t = heap_variant_t<_ts...>;

}

namespace mto::no_stl::variant {
  using namespace mto::no_stl::variant::stack_variant;
}
