#ifndef VARIANT_H
#define VARIANT_H


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

// holds identifier names for variant_class::type_member
enum class variant_type {
	string_type,
	double_type,
 };

//custom variant type struct -- holds string or double
struct variant_class {
	variant_type type_member{};
	// union -- only one can hold value at given time
	union {
		std::string str;
		double dbl;
	};
	variant_class() : type_member(variant_type::string_type), str("") {}
	variant_class(const std::string& string) : type_member(variant_type::string_type), str(string) {}
	variant_class(double value) : type_member(variant_type::double_type), dbl(value) {}
    variant_class(const variant_class& v);
    variant_class(variant_class&& v) noexcept;
    ~variant_class();
    variant_class& operator=(const variant_class& other);
	variant_class& operator=(variant_class&& other) noexcept;
	bool operator<(const variant_class& other) const;
	bool operator>(const variant_class& other) const;
	template <typename v>
	void visit(v&& visitor) const;
};

// class so can read variant typ to file
class print_visitor {
	std::ofstream& file;

public:
	print_visitor(std::ofstream& outputFile) : file(outputFile) {}
	void operator()(const std::string& str) const;
	void operator()(double value) const;
};



template <typename v>
void variant_class::visit(v&& visitor) const {
	switch (type_member) {
	case variant_type::string_type:
		visitor(str);
		break;
	case variant_type::double_type:
		visitor(dbl);
		break;
	}
}
















#endif
