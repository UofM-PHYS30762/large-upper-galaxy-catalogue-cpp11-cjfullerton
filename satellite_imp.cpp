#include "object_interface.h"

std::vector<variant_class> moon::get_all_new() const {
  std::vector<variant_class> temp_variant_moon{};
  temp_variant_moon.emplace_back(type);
  temp_variant_moon.emplace_back(id);
  temp_variant_moon.emplace_back(right_ascension);
  temp_variant_moon.emplace_back(declination);
  temp_variant_moon.emplace_back(redshift);
  temp_variant_moon.emplace_back(mass);
  temp_variant_moon.emplace_back(radius);
  temp_variant_moon.emplace_back(orbital_period);
  temp_variant_moon.emplace_back(additional);
  return temp_variant_moon;
}
std::vector<variant_class> planet::get_all_new() const {
  std::vector<variant_class> temp_variant;
  temp_variant.emplace_back(type);
  temp_variant.emplace_back(id);
  temp_variant.emplace_back(right_ascension);
  temp_variant.emplace_back(declination);
  temp_variant.emplace_back(redshift);
  temp_variant.emplace_back(mass);
  temp_variant.emplace_back(radius);
  temp_variant.emplace_back(orbital_period);
  temp_variant.emplace_back(additional);
  return temp_variant;
}