#include "defines.h"

#include <string>
#include <stdexcept>
#include <iostream>
using namespace std;

void throw_ensure_exception(char const *expression, char const *file, int line) {
  // mto::system::stack_trace::write_stack_trace(stderr);
  throw ::std::runtime_error(::std::string(expression) + " at " + file + ":" + ::std::to_string(line) + " is false");
}

void throw_ensure_throws_exception(char const *expression, char const *file, int line) {
  // mto::system::stack_trace::write_stack_trace(stderr);
  throw ::std::runtime_error(::std::string(expression) + " at " + file + ":" + ::std::to_string(line) + " should throw");
}

void throw_check_exception(char const *expression, char const *file, int line) {
  // mto::system::stack_trace::write_stack_trace(stderr);
  throw ::std::runtime_error(
      "Precondition error at:\n"s + file + ":" + ::std::to_string(line) + ":\n" + ::std::string(expression));
}

void throw_check_exception(char const *expression, char const *message, char const *file, int line) {
  // mto::system::stack_trace::write_stack_trace(stderr);
  throw ::std::runtime_error(
      "Precondition error at:\n"s + file + ":" + ::std::to_string(line) + ":\n" + ::std::string(message));
}

void exit_not_impl(char const *file, int line) {
  std::cerr << "NOT IMPLEMENTED at " << file << ":" << line << std::endl;
  exit(1);
}
