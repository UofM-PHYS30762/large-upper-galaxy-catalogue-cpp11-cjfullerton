#ifndef REGEX_FUNCTIONS_H
#define REGEX_FUNCTIONS_H

#include <string>


// namespace holding library of regex checks for input validation
namespace regex_functions {
    bool string_is_double(const std::string& input);
    bool string_is_integer(const std::string& input);
    bool string_is_positive_double(const std::string& input);
    bool string_is_positive_integer(const std::string& input);
    bool ra_check(const std::string& input);
    bool dec_check(const std::string& input);
    bool id_check(const std::string& input);
    bool age_check(const std::string& input);
    bool planet_type_check(const std::string& input);
    bool morphology_check(const std::string& input);
    bool int_is_either(int int_1,int int_2,const std::string& input);
    bool int_between(int int_1,int int_2,const std::string& input );
    bool is_four_digits(const std::string& input);
    bool object_type(const std::string& input);
    bool has_members(const std::string& input,int n_members);
    bool is_csv(const std::string& input);
    bool between_1_11(const std::string& input);
};

#endif  
