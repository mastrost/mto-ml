#pragma once

//[mto.import ./map]
//[mto.import no_stl/utility]
#include "../tools/pimpl_deprecated.h"
#include <map>

#define NO_STL_MAP_NS \
mto::no_stl::map//[mto.ns_namespace]

#define INSTANCIATE_MAP(K, V) \
  template struct NO_STL_MAP_NS::map_t<K, V>

//[mto-gen.begin]
#include "./map.h"
#include "no_stl/utility.h"
namespace mto::no_stl::map::map {
namespace map = mto::no_stl::map::map;
namespace utility = mto::no_stl::utility;
}
#include "cpp_tools/defines.h"
//[mto-gen.end]
//[mto]
namespace mto::no_stl::map::map {//[mto.module-begin]

using namespace tools;

namespace {

template <typename key_t, typename value_t>
using impl_t = std::map<key_t, value_t>;

template <typename key_t, typename value_t>
impl_t<key_t, value_t> const &get_impl(map_t<key_t, value_t> const &_this) {
  return (impl_t<key_t, value_t> const &)(_this.impl);
}

template <typename key_t, typename value_t>
impl_t<key_t, value_t> &get_impl(map_t<key_t, value_t> &_this) {
  return (impl_t<key_t, value_t> &)(_this.impl);
}

template <typename key_t, typename value_t>
impl_t<key_t, value_t> &&get_impl(map_t<key_t, value_t> &&_this) {
  return utility::move((impl_t<key_t, value_t> &&)(_this.impl));
}

}

template <typename key_t, typename value_t>
map_t<key_t, value_t>::map_t() {
  new (impl) impl_t<key_t, value_t>();
}

template <typename key_t, typename value_t>
map_t<key_t, value_t>::map_t(std::initializer_list<value_type_t> const &l) {
  new (impl) impl_t<key_t, value_t>();
  for (let &x : l)
    insert(x);
}

template <typename key_t, typename value_t>
map_t<key_t, value_t>::map_t(map_t const &o) {
  new (impl) impl_t<key_t, value_t>(get_impl(o));
}

template <typename key_t, typename value_t>
map_t<key_t, value_t>::map_t(map_t &&o) {
  new (impl) impl_t<key_t, value_t>(get_impl(utility::move(o)));
}

template <typename key_t, typename value_t>
map_t<key_t, value_t> &map_t<key_t, value_t>::operator=(map_t const &o) {
  get_impl(*this) = get_impl(o);
  return *this;
}

template <typename key_t, typename value_t>
map_t<key_t, value_t> &map_t<key_t, value_t>::operator=(map_t &&o) {
  get_impl(*this) = get_impl(utility::move(o));
  return *this;
}

template <typename key_t, typename value_t>
map_t<key_t, value_t>::~map_t() {
  static_assert(impl_size == sizeof(impl_t<key_t, value_t>));
  static_assert(impl_align == alignof(impl_t<key_t, value_t>));

  let &x = get_impl(*this);
  x.~impl_t<key_t, value_t>();
}

template <typename key_t, typename value_t>
void map_t<key_t, value_t>::insert(map_t<key_t, value_t>::value_type_t const &x) {
  let res = get_impl(*this).insert({x.key, x.value});
  // insertion n'a aucun effet: sans doute une erreur d'utilisation
  // (une maj est sans doute voulue)
  CHECK(res.second);
}

template <typename key_t, typename value_t>
size_t map_t<key_t, value_t>::size() const {
  return get_impl(*this).size();
}

/**
 * const iteration
 */

template <typename key_t, typename value_t>
typename map_t<key_t, value_t>::const_iterator_t
map_t<key_t, value_t>::find(key_t const &x) const {
  return pimpl_to_itf<const_iterator_t>(get_impl(*this).find(x));
}

template <typename key_t, typename value_t>
typename map_t<key_t, value_t>::const_iterator_t
map_t<key_t, value_t>::begin() const {
  return pimpl_to_itf<const_iterator_t>(get_impl(*this).begin());
}

template <typename key_t, typename value_t>
typename map_t<key_t, value_t>::const_iterator_t
map_t<key_t, value_t>::end() const {
  return pimpl_to_itf<const_iterator_t>(get_impl(*this).end());
}

template <typename key_t, typename value_t>
void map_t<key_t, value_t>::erase(typename map_t<key_t, value_t>::const_iterator_t const &it) {
  typedef typename impl_t<key_t, value_t>::const_iterator it_impl_t;
  let std_it = *(it_impl_t *)it.impl;
  get_impl(*this).erase(std_it);
}

template <typename key_t, typename value_t>
value_t *map_t<key_t, value_t>::get(key_t const &key, value_t const &_default) {
  let it = find(key);
  if (it != end()) {
    return &(*it).value;
  } else {
    insert({key, _default});
    let it = find(key);
    return &(*it).value;
  }
}

template <typename key_t, typename value_t>
value_t *map_t<key_t, value_t>::get(key_t const &key) {
  return *get_if(key);
}

template <typename key_t, typename value_t>
value_t const *map_t<key_t, value_t>::get(key_t const &key) const {
  return *get_if(key);
}

template <typename key_t, typename value_t>
opt_ptr_t<value_t> map_t<key_t, value_t>::get_if(key_t const &key) {
  let it = find(key);
  if (it == end()) {
    return nullptr;
  } else {
    return &(*it).value;
  }
}

template <typename key_t, typename value_t>
opt_ptr_t<value_t const> map_t<key_t, value_t>::get_if(key_t const &key) const {
  let it = find(key);
  if (it == end()) {
    return nullptr;
  } else {
    return &(*it).value;
  }
}

/**
 * non const iteration
 */

template <typename key_t, typename value_t>
typename map_t<key_t, value_t>::iterator_t
map_t<key_t, value_t>::find(key_t const &x) {
  return pimpl_to_itf<iterator_t>(get_impl(*this).find(x));
}

template <typename key_t, typename value_t>
typename map_t<key_t, value_t>::iterator_t
map_t<key_t, value_t>::begin() {
  return pimpl_to_itf<iterator_t>(get_impl(*this).begin());
}

template <typename key_t, typename value_t>
typename map_t<key_t, value_t>::iterator_t
map_t<key_t, value_t>::end() {
  return pimpl_to_itf<iterator_t>(get_impl(*this).end());
}

template <typename key_t, typename value_t>
void map_t<key_t, value_t>::erase(
    typename map_t<key_t, value_t>::iterator_t const &it) {
  typedef typename impl_t<key_t, value_t>::iterator it_impl_t;
  let std_it = *(it_impl_t *)it.impl;
  get_impl(*this).erase(std_it);
}

template <typename key_t, typename value_t>
void map_t<key_t, value_t>::erase(key_t const &x) {
  get_impl(*this).erase(x);
}

/**
 * const_iterator
 */
template <typename key_t, typename value_t>
using const_it_impl_t = typename impl_t<key_t, value_t>::const_iterator;

template <typename key_t, typename value_t>
const_it_impl_t<key_t, value_t> &get_impl(typename map_t<key_t, value_t>::const_iterator_t &_this) {
  return (const_it_impl_t<key_t, value_t> &)(_this.impl);
}

template <typename key_t, typename value_t>
const_it_impl_t<key_t, value_t> const &get_impl(typename map_t<key_t, value_t>::const_iterator_t const &_this) {
  return (const_it_impl_t<key_t, value_t> const &)(_this.impl);
}

template <typename key_t, typename value_t>
map_t<key_t, value_t>::const_iterator_t::const_iterator_t() {
  new (impl) const_it_impl_t<key_t, value_t>();
}

template <typename key_t, typename value_t>
map_t<key_t, value_t>::const_iterator_t::const_iterator_t(const_iterator_t const &o) {
  new (impl) const_it_impl_t<key_t, value_t>(get_impl<key_t, value_t>(o));
}

template <typename key_t, typename value_t>
typename map_t<key_t, value_t>::const_iterator_t &
map_t<key_t, value_t>::const_iterator_t::operator=(const_iterator_t const &o) {
  get_impl<key_t, value_t>(*this) = get_impl<key_t, value_t>(o);
  return *this;
}

template <typename key_t, typename value_t>
map_t<key_t, value_t>::const_iterator_t::~const_iterator_t() {
  typedef typename impl_t<key_t, value_t>::const_iterator it_impl_t;

  static_assert(impl_size == sizeof(it_impl_t));
  static_assert(impl_align == alignof(it_impl_t));

  let x = (it_impl_t *)(impl);
  x->~it_impl_t();
}

template <typename key_t, typename value_t>
bool map_t<key_t, value_t>::const_iterator_t::operator==(map_t<key_t, value_t>::const_iterator_t const &o) const {
  typedef typename impl_t<key_t, value_t>::const_iterator it_impl_t;
  return (*(it_impl_t *)impl) == (*(it_impl_t *)(o.impl));
}

template <typename key_t, typename value_t>
bool map_t<key_t, value_t>::const_iterator_t::operator!=(map_t<key_t, value_t>::const_iterator_t const &o) const {
  typedef typename impl_t<key_t, value_t>::const_iterator it_impl_t;
  return (*(it_impl_t *)impl) != (*(it_impl_t *)(o.impl));
}

template <typename key_t, typename value_t>
void map_t<key_t, value_t>::const_iterator_t::operator++() {
  typedef typename impl_t<key_t, value_t>::const_iterator it_impl_t;
  ++(*(it_impl_t *)impl);
}

template <typename key_t, typename value_t>
typename map_t<key_t, value_t>::value_type_const_ref_t
map_t<key_t, value_t>::const_iterator_t::operator*() const {
  typedef typename impl_t<key_t, value_t>::const_iterator it_impl_t;
  it_impl_t *impl_ref = (it_impl_t *)impl;
  return {(*impl_ref)->first, (*impl_ref)->second};
}

/**
 * iterator
 */
template <typename key_t, typename value_t>
using it_impl_t = typename impl_t<key_t, value_t>::iterator;

template <typename key_t, typename value_t>
it_impl_t<key_t, value_t> &get_impl(typename map_t<key_t, value_t>::iterator_t &_this) {
  return (it_impl_t<key_t, value_t> &)(_this.impl);
}

template <typename key_t, typename value_t>
it_impl_t<key_t, value_t> const &get_impl(typename map_t<key_t, value_t>::iterator_t const &_this) {
  return (it_impl_t<key_t, value_t> const &)(_this.impl);
}

template <typename key_t, typename value_t>
map_t<key_t, value_t>::iterator_t::iterator_t() {
  new (impl) it_impl_t<key_t, value_t>();
}

template <typename key_t, typename value_t>
map_t<key_t, value_t>::iterator_t::iterator_t(iterator_t const &o) {
  new (impl) it_impl_t<key_t, value_t>(get_impl<key_t, value_t>(o));
}

template <typename key_t, typename value_t>
typename map_t<key_t, value_t>::iterator_t &
map_t<key_t, value_t>::iterator_t::operator=(iterator_t const &o) {
  get_impl<key_t, value_t>(*this) = get_impl<key_t, value_t>(o);
  return *this;
}

template <typename key_t, typename value_t>
map_t<key_t, value_t>::iterator_t::~iterator_t() {
  typedef typename impl_t<key_t, value_t>::iterator it_impl_t;

  static_assert(impl_size == sizeof(it_impl_t));
  static_assert(impl_align == alignof(it_impl_t));

  let x = (it_impl_t *)(impl);
  x->~it_impl_t();
}

template <typename key_t, typename value_t>
bool map_t<key_t, value_t>::iterator_t::operator==(map_t<key_t, value_t>::iterator_t const &o) const {
  typedef typename impl_t<key_t, value_t>::iterator it_impl_t;
  return (*(it_impl_t *)impl) == (*(it_impl_t *)(o.impl));
}

template <typename key_t, typename value_t>
bool map_t<key_t, value_t>::iterator_t::operator!=(map_t<key_t, value_t>::iterator_t const &o) const {
  typedef typename impl_t<key_t, value_t>::iterator it_impl_t;
  return (*(it_impl_t *)impl) != (*(it_impl_t *)(o.impl));
}

template <typename key_t, typename value_t>
void map_t<key_t, value_t>::iterator_t::operator++() {
  typedef typename impl_t<key_t, value_t>::iterator it_impl_t;
  ++(*(it_impl_t *)impl);
}

template <typename key_t, typename value_t>
typename map_t<key_t, value_t>::value_type_ref_t
map_t<key_t, value_t>::iterator_t::operator*() const {
  typedef typename impl_t<key_t, value_t>::iterator it_impl_t;
  it_impl_t *impl_ref = (it_impl_t *)impl;
  return {(*impl_ref)->first, (*impl_ref)->second};
}

}//[mto.module-end]
