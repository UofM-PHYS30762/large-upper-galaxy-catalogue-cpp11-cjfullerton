#include "regex_checks.h"
#include <regex>

namespace regex_functions {


	bool string_is_double(const std::string& input) {

		std::regex is_double("^[-+]?\\d*\\.?\\d+([eE][-+]?\\d+)?$");
		if (!std::regex_match(input, is_double)) {
			throw(std::runtime_error("Input is not a valid double"));
		}
		return true;
	}

	bool string_is_integer(const std::string& input) {
		std::regex is_integer("^[-+]?\\d+$");
		if (!std::regex_match(input, is_integer)) {
			throw(std::runtime_error("Input is not a valid integer"));
		}
		return true;
	}

	bool string_is_positive_double(const std::string& input) {
		std::regex is_positive_double("^\\d*\\.?\\d+$");
		if (!std::regex_match(input, is_positive_double)) {
			throw(std::runtime_error("Input is not a valid positive double"));
		}
		return true;
	}

	bool string_is_positive_integer(const std::string& input) {
		std::regex is_positive_integer("^[1-9]\\d*$");
		if (!std::regex_match(input, is_positive_integer)) {
			throw(std::runtime_error("Input is not a valid positive integer"));
		}
		return true;
	}
	// checks for double between 0 and 360
	bool ra_check(const std::string& input) {
		std::regex ra_in_range("^([0-9]|[1-9][0-9]|[1-2][0-9]{2}|3[0-5][0-9]|360)(\\.\\d+)?$");
		if (!std::regex_match(input, ra_in_range)) {
			throw(std::runtime_error("Input for RA must be a double between 0 and 360 degrees"));
		}
		return true;
	}
	// checks for double between -90 and 90
	bool dec_check(const std::string& input) {
		
		double input_double{ stod(input) };
		if (!string_is_double(input)) {
			throw(std::runtime_error("Input for Dec must be a double between -90 and 90 degrees"));
		}
		else if (input_double > 90 || input_double < -90) {
			throw(std::runtime_error("Input for Dec must be a double between -90 and 90 degrees"));
		}
		return true;
	}
	//checks for 3 letters, followed by 3 numbers
	bool id_check(const std::string& input) {
		std::regex id(R"([a-zA-Z]{3}\d{3})");
		if (!std::regex_match(input, id)) {
			throw(std::runtime_error("Id must be 3 characters, followed by 3 integers (xxx111) "));
		}
		return true;
	}
	//checks for a double, and that it is less than the age of the universe
	bool age_check(const std::string& input) {
		std::regex age_less("^\\d*\\.?\\d+$");
		double age_universe = 13.7;
		double value = std::stod(input);
		if (!std::regex_match(input, age_less)) {
			throw (std::runtime_error("Input must be a double"));
		}
		else if (!(value < age_universe)) {
			throw(std::runtime_error("Age of object must be less than age of the universe"));
		}
		return true;
	}
	// checks that input is valid planet type
	bool planet_type_check(const std::string& input) {
		std::regex planet_type("^(gas giant|neptunian|super-earth|terrestrial)$");
		if (!std::regex_match(input, planet_type)) {
			throw(std::runtime_error("planet type must be one of the following (gas giant, neptunian, super-earth, terrestrial)"));
		}
		return true;
	}
	//checks input is a valid morphology type
	bool morphology_check(const std::string& input) {
		
		std::regex morph("^(disk|spheroid|peculiar)$");
		if (!std::regex_match(input, morph)) {
			throw(std::runtime_error("morphology must be one of the following (disk,spheroid,peculiar)"));
		}
		return std::regex_match(input, morph);
	}

	bool int_between(int lower, int upper, const std::string& input) {
		std::regex pattern("^(" + std::to_string(lower) + "|" + std::to_string(upper) + "|["
			+ std::to_string(lower + 1) + "-" + std::to_string(upper - 1) + "])$");
		if (!std::regex_match(input, pattern)) {
			throw(std::runtime_error("Choice must be an integer between" + std::to_string(lower) + " and " + std::to_string(upper)));

		}
		return true;
	}
	bool int_is_either(int int_1, int int_2,const std::string&input) {
		std::regex int_either("^(?:" + std::to_string(int_1) + "|" + std::to_string(int_2) + ")$");
		if (!std::regex_match(input, int_either)) {
			throw(std::runtime_error("Choice must be either " + std::to_string(int_1) + " or " + std::to_string(int_2)));
		}
		return true;
	}
	bool is_four_digits(const std::string& input) {
		
		std::regex is_four_digits("^(\\d{4})$");
		if (!std::regex_match(input, is_four_digits)) {
			throw(std::runtime_error("Must be a four digit number"));
		}
		return true;
		
	}

	bool object_type(const std::string& input) {

		std::regex object_typ("^(planet|galaxy|moon|star)$");
		if (!std::regex_match(input, object_typ)) {
			throw(std::runtime_error("Input must be a valid object type (planet,galaxy,moon,star)"));
		}
		return std::regex_match(input, object_typ);
	}


	// checks that a csv contains a certain number of , delimited values
	bool has_members(const std::string& input, int n_members) {

		std::regex has_member("^([^,]+,){0," + std::to_string(n_members - 1) + "}[^,]+$");
		if (!std::regex_match(input, has_member)) {
			throw(std::runtime_error("Input must have " + std::to_string(n_members) + " comma delimited values"));
		}
		return std::regex_match(input, has_member);
	}

	bool is_csv(const std::string& input) {
		std::regex csv(R"([a-zA-Z0-9]+\.csv)");
		if (!std::regex_match(input, csv)) {
			throw(std::runtime_error("Filename must be alphanumeric (no special characters), and end in .csv"));

		}
		return std::regex_match(input, csv);
	}
	bool between_1_11(const std::string& input) {
		std::regex between("^(1[0-1]|[1-9])$");
		if (!std::regex_match(input, between)) {
			throw(std::runtime_error("Input must be between 1 and 11"));
		}
		return(std::regex_match(input, between));

	}
}
