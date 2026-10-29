#pragma once

#include "cpp_tools/defines.h"//[mto]
namespace mto::cpp_tools {//[mto.ns_begin]

struct main_function_registerer_t {
  main_function_registerer_t(int (*f)(int argc, char const **argv));
};

#define MAIN3(name, argc_name, argv_name)                                               \
  int __main_##name(int argc_name, char const **argv_name);                             \
  ::mto::cpp_tools::main_function_registerer_t __main_registerer_##name(__main_##name); \
  int __main_##name(int argc_name, char const **argv_name)

#define MAIN2(line, argc_name, argv_name) \
  MAIN3(line, argc_name, argv_name)

#define MAIN(argc_name, argv_name) \
  MAIN2(__LINE__, argc_name, argv_name)

}//[mto.ns_end]
