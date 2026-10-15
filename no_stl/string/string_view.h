#pragma once
#include <cpp_tools/contract.h>
//[mto.import no_stl/span/index_iterator:foreach_index_t]

//[mto-gen.begin]
#include "no_stl/span/index_iterator.h"
namespace mto::no_stl::string::string_view {
using mto::no_stl::span::index_iterator::foreach_index_t;
}
#include "cpp_tools/defines.h"
//[mto-gen.end]
//[mto]
namespace mto::no_stl::string::string_view {//[mto.module-begin]

/**
 * Comme std::string_view: la donnée est forcément const
 */
struct string_view_t {
  char const *data() const { return _data; }
  size_t size() const { return _size; }

  char operator[](size_t i) const {
    REQUIRES(i < _size);
    return _data[i];
  }

  bool empty() const {
    return _size == 0;
  }

  string_view_t slice(size_t first) const {
    REQUIRES(first <= _size);
    return {
        _data + first,
        _size - first,
    };
  }

  bool operator==(string_view_t) const;

  char const *begin() const { return _data; }
  char const *end() const { return _data + _size; }

  foreach_index_t<size_t> foreach_index() const { return {_size}; }

  char const *_data;
  size_t _size;
};

namespace literals {

string_view_t operator""_sv(char const *str, size_t size);

}

}//[mto.module-end]

namespace mto::no_stl::string {//[mto.ns-compatibility]
  using namespace mto::no_stl::string::string_view;//[mto]
}//[mto]
