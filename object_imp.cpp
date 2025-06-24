
#include<iostream>
#include <string>
#include "object_interface.h"



void astronomical_object::update_type(std::string input) {
	type = input;
}

inline std::istream& astronomical_object::data_input(std::istream& is) {

}
// overloading ostream for base class
inline std::ostream& operator<<(std::ostream& os, astronomical_object& o)
{
	o.data_out();

	return os;
}

//overloading istream for base class
inline std::istream& operator>>(std::istream& is, astronomical_object& obj)
{

	obj.data_input(is);
	return is;
}



// deep copy constructor for base class
inline astronomical_object::astronomical_object(astronomical_object& object)
{
	id = object.id;
	redshift = object.redshift;
	right_ascension = object.right_ascension;
	declination = object.declination;
	mass = object.mass;
	radius = object.radius;

}

//deep copy assignment for base class

inline astronomical_object& astronomical_object:: operator =(astronomical_object& object)
{
	if (&object == this) return *this;
	id = object.id;
	redshift = object.redshift;
	right_ascension = object.right_ascension;
	declination = object.declination;
	mass = object.mass;
	radius = object.radius;
	return *this;

}
// move constructor for base class
inline astronomical_object::astronomical_object(astronomical_object&& object) noexcept
{
	id = std::move(object.id);
	redshift = std::move(object.redshift);
	right_ascension = std::move(object.right_ascension);
	declination = std::move(object.declination);
	mass = std::move(object.mass);
	radius = std::move(object.radius);
	object.id = "";
	object.redshift = 0;
	object.right_ascension = 0;
	object.declination = 0;
	object.mass = 0;
	object.radius = 0;

}

//move assignment for base class
inline astronomical_object& astronomical_object:: operator=(astronomical_object&& object) noexcept {

	if (&object == this) return *this;
	std::swap(id, object.id);
	std::swap(redshift, object.redshift);
	std::swap(right_ascension, object.right_ascension);
	std::swap(declination, object.declination);
	std::swap(mass, object.mass);
	std::swap(radius, object.radius);
	object.id = "";
	object.redshift = 0;
	object.right_ascension = 0;
	object.declination = 0;
	object.mass = 0;
	object.radius = 0;
	return *this;

}
