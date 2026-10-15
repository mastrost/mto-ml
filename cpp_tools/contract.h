#pragma once

#include <cassert>

/**
 * la macro CHECK_PRECONDITIONS doit être défini pour activer les check
 */
#include "cpp_tools/defines.h"//[mto]
namespace mto::cpp_tools {//[mto.ns_begin]

#ifdef CHECK_PRECONDITIONS

#define REQUIRES(expr) CHECK(expr)
#define ASSERT(expr) CHECK(expr)
#define GHOST(statement) statement

#else

#define REQUIRES(expr) \
  do {                 \
  } while (false)
#define ASSERT(expr) \
  do {               \
  } while (false)
#define GHOST(statement)

#endif

}//[mto.ns_end]
