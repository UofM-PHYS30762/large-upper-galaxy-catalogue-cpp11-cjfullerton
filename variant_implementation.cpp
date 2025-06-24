#include "variant_interface.h"

// Copy constructor
variant_class::variant_class(const variant_class &v) : variant_class() {
  type_member = v.type_member;
  switch (type_member) {
  case variant_type::string_type:
    new (&str) std::string(v.str);
  case variant_type::double_type:
    dbl = v.dbl;
    break;
  }
}

variant_class::variant_class(variant_class &&v) noexcept : variant_class() {
  type_member = v.type_member;
  switch (type_member) {
  case variant_type::string_type:
    new (&str) std::string(std::move(v.str));
    break;
  case variant_type::double_type:
    dbl = v.dbl;
    break;
  }
}
variant_class::~variant_class() {
  if (type_member == variant_type::string_type) {
    str.~basic_string();
  }
}
// Copy assignment operator
variant_class &variant_class::operator=(const variant_class &other) {
  if (this != &other) {
    this->~variant_class();
    new (this) variant_class(other);
  }
  return *this;
}

// move assignment operator
variant_class &variant_class::operator=(variant_class &&other) noexcept {
  if (this != &other) {
    this->~variant_class();
    new (this) variant_class(std::move(other));
  }
  return *this;
}

// overload < for variant class
bool variant_class::operator<(const variant_class &other) const {
  switch (type_member) {
  case variant_type::double_type:
    return dbl < other.dbl;
  case variant_type::string_type:
    return str < other.str;
  }

  return false;
}
// overload > for variant class
bool variant_class::operator>(const variant_class &other) const {
  switch (type_member) {
  case variant_type::double_type:
    return dbl > other.dbl;
  case variant_type::string_type:
    return str > other.str;
  }
  return false;
}

// overload () for string inputs -> so can write variant type to file
void print_visitor::operator()(const std::string &str) const { file << str; }

// overload () for doubles -> same as above
void print_visitor::operator()(double value) const { file << value; }
