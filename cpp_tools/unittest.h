#pragma once

#include "cpp_tools/defines.h"//[mto]
namespace mto::cpp_tools {//[mto.ns_begin]

struct test_t {
  test_t(void (*f)(), char const *test_name);
};

#define UNITTEST3(name)                                                                                           \
  void __unittest_##name();                                                                                       \
  ::mto::cpp_tools::test_t __unittest_type_##name(__unittest_##name, #name); \
  void __unittest_##name()

#define UNITTEST2(line) \
  UNITTEST3(line)

#define UNITTEST() \
  UNITTEST2(__LINE__)

}//[mto.ns_end]

int main();
