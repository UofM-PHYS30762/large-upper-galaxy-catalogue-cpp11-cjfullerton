#include "object_interface.h"

// getter function for all members using custom variant_class
std::vector<variant_class> star::get_all_new() const {
  std::vector<variant_class> temp_variant_non_sat{};
  temp_variant_non_sat.emplace_back(type);
  temp_variant_non_sat.emplace_back(id);
  temp_variant_non_sat.emplace_back(right_ascension);
  temp_variant_non_sat.emplace_back(declination);
  temp_variant_non_sat.emplace_back(redshift);
  temp_variant_non_sat.emplace_back(mass);
  temp_variant_non_sat.emplace_back(radius);
  temp_variant_non_sat.emplace_back(magnitude);
  temp_variant_non_sat.emplace_back(luminosity);
  temp_variant_non_sat.emplace_back(age);
  temp_variant_non_sat.emplace_back(additional_1);
  temp_variant_non_sat.emplace_back(additional_2);
  return temp_variant_non_sat;
}

std::vector<variant_class> galaxy::get_all_new() const {
  std::vector<variant_class> temp_variant_non_sat{};
  temp_variant_non_sat.emplace_back(type);
  temp_variant_non_sat.emplace_back(id);
  temp_variant_non_sat.emplace_back(right_ascension);
  temp_variant_non_sat.emplace_back(declination);
  temp_variant_non_sat.emplace_back(redshift);
  temp_variant_non_sat.emplace_back(mass);
  temp_variant_non_sat.emplace_back(radius);
  temp_variant_non_sat.emplace_back(magnitude);
  temp_variant_non_sat.emplace_back(luminosity);
  temp_variant_non_sat.emplace_back(age);
  temp_variant_non_sat.emplace_back(additional_1);
  temp_variant_non_sat.emplace_back(additional_2);
  return temp_variant_non_sat;
}
