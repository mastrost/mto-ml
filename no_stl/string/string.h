#pragma once

//[mto.import ./c_str_host:c_str_host_t]
//[mto.import ./string_view:string_view_t]
//[mto.import ../vector/vector:vector_t]
//[mto.import no_stl/span/index_iterator:foreach_index_t]

//[mto-gen.begin]
#include "./c_str_host.h"
#include "./string_view.h"
#include "./../vector/vector.h"
#include "no_stl/span/index_iterator.h"
namespace mto::no_stl::string::string {
using mto::no_stl::string::c_str_host::c_str_host_t;
using mto::no_stl::string::string_view::string_view_t;
using mto::no_stl::vector::vector::vector_t;
using mto::no_stl::span::index_iterator::foreach_index_t;
}
#include "cpp_tools/defines.h"
//[mto-gen.end]
//[mto]
namespace mto::no_stl::string::string {//[mto.module-begin]

struct string_t {
  string_t();
  string_t(string_t const &);
  string_t(string_t &&);
  string_t(char const *);
  string_t(char const *p, size_t n);
  string_t(string_view_t string_view);
  ~string_t();

  operator string_view_t() const;

  char const *data() const;
  size_t size() const;
  char operator[](size_t) const;
  string_t &operator=(string_t const &);
  string_t &operator=(string_t &&);

  void operator+=(char);
  void operator+=(char const *);
  void operator+=(string_t const &);
  void operator+=(string_t &&);
  template <typename other_type_even_if_implicitly_convertible_t>
  void operator+=(other_type_even_if_implicitly_convertible_t c) = delete;

  string_t operator+(char) const;
  string_t operator+(char const *) const;
  string_t operator+(string_t const &) const;
  string_t operator+(string_t &&) const;

  bool operator==(string_t const &) const;
  bool operator!=(string_t const &) const;
  bool operator<(string_t const &) const;

  char const *begin() const;
  char const *end() const;
  char *begin();
  char *end();

  foreach_index_t<size_t> foreach_index() const { return {buf.size()}; }

  c_str_host_t c_str_host() const;
// Mainly to use with printf
// Warning: mind the lifetime: result cannot be store
#define C_STR c_str_host().c_str()

  vector_t<char> buf;
};

string_t operator+(char const *, string_t const &);

namespace literal {
string_t operator""_s(const char *str, size_t);
}

}//[mto.module-end]

namespace mto::no_stl::string {//[mto.ns-compatibility]
  using namespace mto::no_stl::string::string;//[mto]
}//[mto]
