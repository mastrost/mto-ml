#pragma once

#include <initializer_list>
//[mto.import no_stl/optional/opt_ptr:opt_ptr_t]

//[mto-gen.begin]
#include "no_stl/optional/opt_ptr.h"
namespace mto::no_stl::map::map {
using mto::no_stl::optional::opt_ptr::opt_ptr_t;
}
#include "cpp_tools/defines.h"
//[mto-gen.end]
//[mto]
namespace mto::no_stl::map::map {//[mto.module-begin]

template <typename key_t, typename value_t>
struct map_t {
  struct value_type_t {
    key_t const key;
    value_t value;
  };

  struct value_type_const_ref_t {
    key_t const &key;
    value_t const &value;
  };

  struct value_type_ref_t {
    key_t const &key;
    value_t &value;
  };

  map_t();
  map_t(std::initializer_list<value_type_t> const &);
  map_t(map_t const &);
  map_t(map_t &&);
  map_t &operator=(map_t const &);
  map_t &operator=(map_t &&);

  struct const_iterator_t {
    const_iterator_t();
    const_iterator_t(const_iterator_t const &);
    const_iterator_t &operator=(const_iterator_t const &);
    ~const_iterator_t();

    bool operator==(const_iterator_t const &) const;
    bool operator!=(const_iterator_t const &) const;
    void operator++();
    value_type_const_ref_t operator*() const;

    static constexpr int impl_size = sizeof(void *);
    static constexpr int impl_align = sizeof(void *);
    alignas(impl_align) char impl[impl_size];
  };

  struct iterator_t {
    iterator_t();
    iterator_t(iterator_t const &);
    iterator_t &operator=(iterator_t const &);
    ~iterator_t();

    bool operator==(iterator_t const &) const;
    bool operator!=(iterator_t const &) const;
    void operator++();
    value_type_ref_t operator*() const;

    static constexpr int impl_size = sizeof(void *);
    static constexpr int impl_align = sizeof(void *);
    alignas(impl_align) char impl[impl_size];
  };

  ~map_t();

  void insert(value_type_t const &);
  size_t size() const;

  const_iterator_t find(key_t const &) const;
  const_iterator_t begin() const;
  const_iterator_t end() const;
  void erase(const_iterator_t const &it);

  iterator_t find(key_t const &);
  iterator_t begin();
  iterator_t end();
  void erase(iterator_t const &it);

  void erase(key_t const &);

  value_t *get(key_t const &key, value_t const &_default);
  value_t *get(key_t const &key);
  value_t const *get(key_t const &key) const;
  opt_ptr_t<value_t> get_if(key_t const &key);
  opt_ptr_t<value_t const> get_if(key_t const &key) const;

#ifdef __EMSCRIPTEN__
  static constexpr int impl_size = 12;
#else
  static constexpr int impl_size = 48;
#endif
  static constexpr int impl_align = sizeof(void *);
  alignas(impl_align) char impl[impl_size];
};

}//[mto.module-end]

namespace mto::no_stl::map {//[mto.ns-compatibility]
  using namespace mto::no_stl::map::map;//[mto]
}//[mto]
