#pragma once


#include "no_stl/array/array.h"
#include "no_stl/string/string.h"
#include "no_stl/vector/vector.h"
#include "no_stl/span/span.h"
namespace mto::math::ml::projects::makemore::common {
using mto::no_stl::array::array::array_t;
using mto::no_stl::string::string::string_t;
using mto::no_stl::vector::vector::vector_t;
using mto::no_stl::span::span::cspan_t;
}
#include "cpp_tools/defines.h"
namespace mto::math::ml::projects::makemore::common {

static constexpr char begin = '<';
static constexpr char end = '>';
typedef array_t<char, size_t, 2> bigram_t;
static constexpr size_t num_chars = 28;

typedef vector_t<string_t> words_t;
typedef cspan_t<string_t> words_sp_t;

vector_t<bigram_t>
extract_bigrams(words_sp_t words);

char to_char(size_t i);
size_t to_index(char c);
float to_findex(char c);

}
