//[mto.import ./string.manip]
#include "no_stl/map/map.impl.h"
#include "cpp_tools/contract.h"
#include <string>
#include <sstream>
#include <cstdio>

//[mto-gen.begin]
#include "./string.manip.h"
namespace mto::no_stl::string::string {
namespace string = mto::no_stl::string::string;
}
#include "cpp_tools/defines.h"
//[mto-gen.end]
//[mto]
namespace mto::no_stl::string::string {//[mto.module-begin]

namespace {

template <typename _t>
optional_t<_t> try_parse(string_t const &s, bool check_eos = true) {
  std::stringstream parser(s.c_str_host().c_str());
  _t res;
  parser >> res;
  if (parser.fail() || (check_eos && !parser.eof()))
    return {};
  return res;
}

}

static bool is_same(char const *in, string_t const &pattern) {
  for (size_t i = 0; i < pattern.size(); ++i)
    if (in[i] != pattern[i])
      return false;
  return true;
}

string_t to_lower(string_t const &str) {
  string_t res;
  for (let c : str) {
    res += char(::tolower(c));
  }
  return res;
}

string_t to_upper(string_t const &str) {
  string_t res;
  for (let c : str) {
    res += char(::toupper(c));
  }
  return res;
}

string_t replace(string_t const &str, env_t const &env) {
  string_t res;
  for (size_t i = 0; i < str.size();) {
    bool found = false;
    for (auto const &[in, out] : env) {
      if (i + in.size() > str.size())
        continue;

      if (is_same(str.data() + i, in)) {
        res += out;
        found = true;
        i += in.size();
        break;
      }
    }
    if (!found) {
      res += str[i];
      ++i;
    }
  }
  return res;
}

string_t remove_char(string_t const &str, char c) {
  string_t res;
  for (auto const &elt : str) {
    if (elt != c)
      res += elt;
  }
  return res;
}

string_t to_string(int32_t x) {
  return std::to_string(x).c_str();
}

string_t to_string(int64_t x) {
  return std::to_string(x).c_str();
}

string_t to_string(uint32_t x) {
  return std::to_string(x).c_str();
}

string_t to_string(uint64_t x) {
  return std::to_string(x).c_str();
}

string_t to_string(float x) {
  std::stringstream str;
  str.precision(7);
  str << x;
  return str.str().c_str();
}

string_t to_string(double x) {
  std::stringstream str;
  str.precision(16);
  str << x;
  return str.str().c_str();
}

string_t large_int_str(uint32_t i) {
  let src = to_string(i);
  auto res = string_t{};
  for (let i : src.foreach_index()) {
    if (i != 0 && (src.size() - i) % 3 == 0) {
      res += "'";
    }
    res += src[i];
  }
  return res;
}

template <>
optional_t<int32_t> read(string_t const &str) {
  return try_parse<int32_t>(str, true);
}

template <>
optional_t<int64_t> read(string_t const &str) {
  return try_parse<int64_t>(str, true);
}

template <>
optional_t<float> read(string_t const &str) {
  return try_parse<float>(str, true);
}

template <>
optional_t<double> read(string_t const &str) {
  return try_parse<double>(str, true);
}

vector_t<string_t> split(string_t const &str, char sep) {
  vector_t<string_t> res;
  string_t cur;
  for (auto const &c : str) {
    if (c != sep)
      cur += c;
    else {
      res.push_back(cur);
      cur = string_t();
    }
  }
  res.push_back(cur);
  return res;
}

int32_t find(string_t const &str, char c) {
  for (int32_t i = 0; i < int32_t(str.size()); ++i)
    if (str[i] == c)
      return i;
  return NOT_FOUND;
}

bool contains(string_t const &str, char c) {
  return find(str, c) != NOT_FOUND;
}

string_t substr(string_t const &str, size_t pos, size_t size) {
  REQUIRES(pos < str.size() && pos + size <= str.size());
  string_t res;
  for (size_t i = 0; i < size; ++i) {
    res += str[pos + i];
  }
  return res;
}

/**
 * bin
 */
string_t bin_to_string(span_t<byte_t const> bin) {
  auto str = string_t{};
  for (let b : bin) {
    str += char(b);
  }
  return str;
}

vector_t<byte_t> string_to_bin(string_t const &str) {
  auto bin = vector_t<byte_t>{};
  for (let c : str) {
    bin.push_back(byte_t(c));
  }
  return bin;
}

}//[mto.module-end]

namespace _ns =
mto::no_stl::string::string//[mto.module-namespace]
    ;

INSTANCIATE_MAP(_ns::string_t, _ns::string_t);
