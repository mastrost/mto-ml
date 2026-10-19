#pragma once

//[mto.import ./string]
//[mto.import no_stl/vector/vector:vector_t]
//[mto.import no_stl/optional/optional:optional_t]
//[mto.import no_stl/map/map:map_t]
//[mto.import no_stl/byte/byte:byte_t]
//[mto.import no_stl/span/span:span_t]

//[mto-gen.begin]
#include "./string.h"
#include "no_stl/vector/vector.h"
#include "no_stl/optional/optional.h"
#include "no_stl/map/map.h"
#include "no_stl/byte/byte.h"
#include "no_stl/span/span.h"
namespace mto::no_stl::string::string {
namespace string = mto::no_stl::string::string;
using mto::no_stl::vector::vector::vector_t;
using mto::no_stl::optional::optional::optional_t;
using mto::no_stl::map::map::map_t;
using mto::no_stl::byte::byte::byte_t;
using mto::no_stl::span::span::span_t;
}
#include "cpp_tools/defines.h"
//[mto-gen.end]
//[mto]
namespace mto::no_stl::string::string {//[mto.module-begin]

string_t to_lower(string_t const &str);
string_t to_upper(string_t const &str);

typedef map_t<string_t, string_t> env_t;

// devrait prendre un span, ou meme un iterateur
string_t replace(string_t const &str, env_t const &env);
string_t remove_char(string_t const &str, char c);

string_t to_string(int32_t);
string_t to_string(int64_t);
string_t to_string(uint32_t);
string_t to_string(uint64_t);
string_t to_string(float);
string_t to_string(double);

// format "123'888'222"
string_t large_int_str(uint32_t i);

template <typename _t>
optional_t<_t> read(string_t const &) = delete;

template <>
optional_t<int32_t> read(string_t const &);

template <>
optional_t<int64_t> read(string_t const &);

template <>
optional_t<float> read(string_t const &);

template <>
optional_t<double> read(string_t const &);

vector_t<string_t> split(string_t const &str, char sep);

[[maybe_unused]] static constexpr int32_t NOT_FOUND = -1;
int32_t find(string_t const &str, char c);

bool contains(string_t const &str, char c);

// precondition: le range doit être valide
string_t substr(string_t const &str, size_t pos, size_t size);

/**
 * bin
 */
string_t bin_to_string(span_t<byte_t const> bin);
vector_t<byte_t> string_to_bin(string_t const &str);

}//[mto.module-end]

namespace mto::no_stl::string {//[mto.ns-compatibility]
  using namespace mto::no_stl::string::string;//[mto]
}//[mto]
