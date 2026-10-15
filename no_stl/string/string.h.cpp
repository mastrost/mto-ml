//[mto.import ./string]
#include "../utility.h"

//[mto-gen.begin]
#include "./string.h"
namespace mto::no_stl::string::string {
namespace string = mto::no_stl::string::string;
}
#include "cpp_tools/defines.h"
//[mto-gen.end]
//[mto]
namespace mto::no_stl::string::string {//[mto.module-begin]


namespace {
void append_c_str(string_t &s, char const *str) {
  while (*str != 0)
    s.buf.push_back(*str++);
}
}

string_t::string_t() {
}

string_t::string_t(string_t const &o) {
  buf = o.buf;
}

string_t::string_t(string_t &&o) {
  buf = no_stl::move(o.buf);
}

string_t::string_t(char const *str) {
  append_c_str(*this, str);
}

string_t::string_t(char const *p, size_t n) {
  for (size_t i = 0; i < n; ++i)
    buf.push_back(*p++);
}

string_t::string_t(string_view_t string_view)
    : string_t(string_view.data(), string_view.size()) {
}

string_t::~string_t() {
}

string_t::operator string_view_t() const {
  return {buf.data(), buf.size()};
}

char const *string_t::data() const {
  return buf.data();
}

size_t string_t::size() const {
  return buf.size();
}

char string_t::operator[](size_t i) const {
  return buf[i];
}

string_t &string_t::operator=(string_t const &o) {
  buf = o.buf;
  return *this;
}

string_t &string_t::operator=(string_t &&o) {
  buf = no_stl::move(o.buf);
  return *this;
}

void string_t::operator+=(char c) {
  buf.push_back(c);
}

void string_t::operator+=(char const *o) {
  append_c_str(*this, o);
}

void string_t::operator+=(string_t const &o) {
  for (size_t i = 0; i < o.size(); ++i)
    buf.push_back(o.buf[i]);
}

void string_t::operator+=(string_t &&o) {
  for (size_t i = 0; i < o.size(); ++i)
    buf.push_back(o.buf[i]);
}

string_t string_t::operator+(char const *o) const {
  string_t res = *this;
  res += o;
  return res;
}

string_t string_t::operator+(char c) const {
  string_t res = *this;
  res += c;
  return res;
}

string_t string_t::operator+(string_t const &o) const {
  string_t res = *this;
  res += o;
  return res;
}

string_t string_t::operator+(string_t &&o) const {
  string_t res = *this;
  res += no_stl::move(o);
  return res;
}

bool string_t::operator==(string_t const &o) const {
  return buf == o.buf;
}

bool string_t::operator!=(string_t const &o) const {
  return buf != o.buf;
}

bool string_t::operator<(string_t const &o) const {
  return buf < o.buf;
}

string_t operator+(char const *c_str, string_t const &str) {
  string_t res(c_str);
  res += str;
  return res;
}

char const *string_t::begin() const {
  return buf.begin();
}

char const *string_t::end() const {
  return buf.end();
}

char *string_t::begin() {
  return buf.begin();
}

char *string_t::end() {
  return buf.end();
}

c_str_host_t string_t::c_str_host() const {
  vector::vector_t<char> c_str_buf = buf;
  c_str_buf.push_back(0);
  return {no_stl::move(c_str_buf)};
}

namespace literal {
string_t operator""_s(const char *p, size_t n) {
  return string_t(p, n);
}
}

}//[mto.module-end]
