#pragma once

#define let auto const
#define let_mutable auto

#include <cstddef>
#include <cstdint>

using std::size_t;
using std::int8_t;
using std::uint8_t;
using std::int16_t;
using std::uint16_t;
using std::int32_t;
using std::uint32_t;
using std::int64_t;
using std::uint64_t;

void throw_ensure_exception(char const *expression, char const *file, int line);

#define ENSURE(expr) \
  if (!(expr))       \
  throw_ensure_exception(#expr, __FILE__, __LINE__)

void throw_ensure_throws_exception(char const *expression, char const *file, int line);

#define ENSURE_THROWS(expr)                                     \
  {                                                             \
    bool hasThrown = false;                                     \
    try {                                                       \
      (expr);                                                   \
    } catch (...) {                                             \
      hasThrown = true;                                         \
    }                                                           \
    if (!hasThrown)                                             \
      throw_ensure_throws_exception(#expr, __FILE__, __LINE__); \
  }

void throw_check_exception(char const *expression, char const *file, int line);
void throw_check_exception(char const *expression, char const *message, char const *file, int line);

#define CHECK(expr) \
  if (!(expr))      \
  throw_check_exception(#expr, __FILE__, __LINE__)

#define CHECK_2(expr, msg) \
  if (!(expr))             \
  throw_check_exception(#expr, msg, __FILE__, __LINE__)

void exit_not_impl(char const *file, int line);

#define EXIT_NOT_IMPL()                \
  do {                                 \
    exit_not_impl(__FILE__, __LINE__); \
    __builtin_unreachable();           \
  } while (false)
