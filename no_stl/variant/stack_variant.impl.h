#pragma once

#include "./heap_variant.impl.h"
#include "./stack_variant.h"

#define NO_STL_STACK_VARIANT_NS \
mto::no_stl::variant::stack_variant

#define INSTANCIATE_STACK_VARIANT(...) INSTANCIATE_HEAP_VARIANT(__VA_ARGS__)

namespace mto::no_stl::variant::stack_variant {
}
#include "cpp_tools/defines.h"
namespace mto::no_stl::variant::stack_variant {
}
