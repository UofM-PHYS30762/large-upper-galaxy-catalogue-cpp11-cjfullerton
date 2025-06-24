#ifndef MY_CLASS_H
#define MY_CLASS_H

#include "regex_checks.h"
#include "variant_interface.h"
#include<iomanip>
#include<type_traits>
#include<memory>

// Abstract base class - Astronomical Object
class astronomical_object {

	friend std::ostream& operator<<(std::ostream& os, astronomical_object& o);
	friend std::istream& operator>>(std::istream& is, astronomical_object& obj);

protected:
	double redshift{}, right_ascension{}, declination{}, mass{}, radius{};

public:
	std::string type;
	std::string id{};
	astronomical_object(std::string ty, std::string id, double z, double ra, double dec, double m, double r) : type{ ty }, id{ id }, redshift{ z }, right_ascension{ ra }, declination{ dec }, mass{ m }, radius{ r } {}
	astronomical_object() = default;
	virtual ~astronomical_object() {};
	astronomical_object(astronomical_object&); // copy constructor 
	astronomical_object(astronomical_object&&) noexcept; //move constructor 
	astronomical_object& operator=(astronomical_object&); // copy assignment
	astronomical_object& operator=(astronomical_object&&) noexcept; // move assignment
	virtual std::istream& data_input(std::istream& is) = 0;
	virtual std::vector<variant_class> get_all_new() const = 0;
	virtual void data_out() = 0;
	void update_type(std::string);
};


// Abstract derived class - satellite
template<typename T>
class satellite : public astronomical_object {
protected:
	double orbital_period{};
	T additional{};
public:
	satellite(std::string ty, std::string id, double z, double ra, double dec, double m, double r, double t, T add) : astronomical_object{ ty, id,z,ra,dec,m,r },
		orbital_period{ t }, additional{ add } {}
	satellite() = default;
	satellite(satellite&);
	satellite(satellite&&) noexcept;
	satellite& operator=(satellite&);
	satellite& operator=(satellite&&) noexcept;
	std::istream& data_input(std::istream& in);
	void data_out() ;
	virtual std::vector<variant_class> get_all_new() const = 0;
	virtual  ~satellite() {}


};

//abstract derived class - non-satellite
template <typename T, typename U>
class non_satellite : public astronomical_object {
protected:

	double magnitude{}, age{}, luminosity{};
	T additional_1{};
	U additional_2{};
public:
	non_satellite(std::string ty, std::string id, double z, double ra, double dec, double m, double r, double mag, double a, double l, T add_1, U add_2) : astronomical_object{ ty,id,z,ra,dec,m,r },
		magnitude{ mag }, age{ a }, luminosity{ l }, additional_1{ add_1 }, additional_2{ add_2 } {}
	non_satellite() = default;
	non_satellite(non_satellite&);
	non_satellite(non_satellite&&) noexcept;
	std::istream& data_input(std::istream& in);
	void data_out();
	non_satellite& operator=(non_satellite&);
	non_satellite& operator=(non_satellite&&) noexcept;
	void process_additional(const std::string& additional1, const std::string& additional2);
	virtual ~non_satellite() {}
	virtual std::vector<variant_class> get_all_new() const = 0;


};

// derived class -- planet
class planet : public satellite<std::string> {
protected:
	std::string planet_type{};
public:
	planet(std::string ty, std::string id, double z, double ra, double dec, double m, double r, double t, std::string type) : satellite{ ty,id,z,ra,dec,m,r,t,type }
	{}
	planet() = default;
	~planet() {}
	std::vector<variant_class> get_all_new() const;

};
 // derived class -- moon
class moon : public satellite<std::string> {
protected:
	std::string planet_orbit{};
public:
	moon(std::string ty, std::string id, double z, double ra, double dec, double m, double r, double t, std::string planet) : satellite{ ty,id,z,ra,dec,m,r,t, planet } {}
	moon() = default;
	~moon() {}
	std::vector<variant_class> get_all_new() const;
};
//derived class-- star
class star : public non_satellite<double, double> {

protected:
	double temperature{};
	double magnetic_field{};
public:
	star(std::string ty, std::string id, double z, double ra, double dec, double m, double r, double mag, double a, double l, double temp, double b) : non_satellite{ ty,id,z, ra, dec, m, r, mag, a, l,temp,b } {}
	star() = default;
	~star() {}
	std::vector<variant_class> get_all_new() const;
};
//derived class - galaxy
class galaxy : public non_satellite<std::string, double> {
protected:
	std::string morphology{};
	double pec_vel{};
public:
	galaxy(std::string ty, std::string id, double z, double ra, double dec, double m, double r, double mag, double a, double l, std::string morph, double v) : non_satellite{ ty, id,z, ra, dec, m, r, mag, a, l,morph,v } {}
	galaxy() = default;
	~galaxy() {}
	std::vector<variant_class> get_all_new() const;


};

// copy constructor for non-satellite
template <typename T, typename U >
inline non_satellite < T, U> ::non_satellite(non_satellite& object)
{

	magnitude = object.magnitude;
	age = object.age;
	luminosity = object.luminosity;
	additional_1 = object.additional_1;
	additional_2 = object.additional_2;
}
//copy assignment for non_satellite
template <typename T, typename U >
inline non_satellite<T, U>& non_satellite<T, U>:: operator=(non_satellite& object) {


	if (&object == this) return *this;
	magnitude = object.magnitude;
	age = object.age;
	luminosity = object.luminosity;
	additional_1 = object.additional_1;
	additional_2 = object.additional_2;
	return *this;
}
// move construcotr for non-satellite
template <typename T, typename U>
inline non_satellite<T, U>::non_satellite(non_satellite&& object) noexcept
{

	magnitude = std::move(object.magnitude);
	age = std::move(object.age);
	luminosity = std::move(object.luminosity);
	additional_1 = std::move(object.additional_1);
	additional_2 = std::move(object.additional_2);

}
//move assignment for non-satellite
template <typename T, typename U>
inline non_satellite<T, U>& non_satellite<T, U> :: operator =(non_satellite&& object) noexcept
{

	if (&object == this) return *this;
	magnitude = std::move(object.magnitude);
	age = std::move(object.age);
	luminosity = std::move(object.luminosity);
	additional_1 = std::move(object.additional_1);
	additional_2 = std::move(object.additional_2);
	return *this;

}
//copy constructor for satellite
template <typename T>
inline satellite<T>::satellite(satellite& object)
{
	orbital_period = object.orbital_period;
	additional = object.additional;

}

// copy assignment for satellite
template<typename T>
inline satellite<T>& satellite<T>:: operator=(satellite& object) {


	if (&object == this) return *this;
	orbital_period = object.orbital_period;
	additional = object.additional;
	return*this;
}

// move constructor for satellite
template <typename T>
inline satellite<T>::satellite(satellite&& object) noexcept
{

	orbital_period = std::move(object.orbital_period);
	additional = std::move(object.additional);

}
// move assignment for satellite
template <typename T>
inline satellite<T>& satellite<T> :: operator =(satellite&& object) noexcept
{
	if (&object == this) return *this;
	orbital_period = std::move(object.orbital_period);
	additional = std::move(object.additional);

	return *this;

}

// satellite member function -- input istream into members
template <typename T>
std::istream& satellite<T>::data_input(std::istream& in) {

	std::string buffer;
	std::vector<std::string> buffers;
	while (std::getline(in, buffer)) {
		std::istringstream iss{buffer};
		std::string buffers_2{};
		while(getline(iss,buffers_2,',')) {
			buffers.emplace_back(buffers_2);
		}
	} 
	if (buffers.size() != 8 && buffers.size() != 10 ) {
		throw(std::runtime_error("Input has to include 8 data"));
	}
	try {
		try {
			regex_functions::id_check(buffers[0]);
			regex_functions::ra_check(buffers[1]);
			regex_functions::dec_check(buffers[2]);
			regex_functions::string_is_positive_double(buffers[3]);
			regex_functions::string_is_positive_double(buffers[4]);
			regex_functions::string_is_positive_double(buffers[5]);
			regex_functions::string_is_positive_double(buffers[6]);
			if (type == "planet") {
				regex_functions::planet_type_check(buffers[7]);
			}
		}
		catch (std::runtime_error& e) {
			throw e;
			std::cout << e.what() << std::endl;
		}
		id = buffers[0];
		right_ascension = stod(buffers[1]);
		declination = stod(buffers[2]);
		redshift = stod(buffers[3]);
		mass = stod(buffers[4]);
		radius = stod(buffers[5]);
		orbital_period = stod(buffers[6]);
		additional = buffers[7];
	}
	catch (const std::out_of_range& e) {
		throw e;
		std::cout << e.what() << std::endl;
	}
	return in;

}

// non-satellite member function -- input istream to members
template <typename T, typename U>
std::istream& non_satellite < T, U > ::data_input(std::istream& in) {
	
	
	std::string buffer;
	std::vector<std::string> buffers;
	while (std::getline(in, buffer)) {
		std::istringstream iss{ buffer };
		std::string buffers_2{};
		while (getline(iss, buffers_2, ',')) {
			buffers.emplace_back(buffers_2);
		}
	}
	if (buffers.size() != 11) {
		throw(std::runtime_error("Input must have 11 data"));
	}
	try {
		try {
			regex_functions::id_check(buffers[0]);
			regex_functions::ra_check(buffers[1]);
			regex_functions::dec_check(buffers[2]);
			regex_functions::string_is_positive_double(buffers[3]);
			regex_functions::string_is_positive_double(buffers[4]);
			regex_functions::string_is_positive_double(buffers[5]);
			regex_functions::string_is_double(buffers[6]);
			regex_functions::string_is_positive_double(buffers[7]);
			regex_functions::age_check(buffers[8]);
		}
		catch (std::runtime_error& e) {
			throw e;
			std::cout << e.what() << std::endl;
		}
		id = buffers[0];
		right_ascension = stod(buffers[1]);
		declination = stod(buffers[2]);
		redshift = stod(buffers[3]);
		mass = stod(buffers[4]);
		radius = stod(buffers[5]);
		magnitude = stod(buffers[6]);
		luminosity = stod(buffers[7]);
		age = stod(buffers[8]);
		
		// constexpr -- only one conditional executed
		// is_same matches template type to str/double
		/*if constexpr (std::is_same<T, double>::value) {
			try {
				regex_functions::string_is_positive_double(buffers[9]);
			}
			catch (std::runtime_error& e) {
				std::cout << e.what() << std::endl;
			}
			additional_1 = stod(buffers[9]);
			type = "star";
		}
		else if (std::is_same<T, std::string>::value) {
			try {
				regex_functions::morphology_check(buffers[9]);
			}
			catch (std::runtime_error& e) {
				std::cout << e.what() << std::endl;
			}
			additional_1 = buffers[9];
			type = "galaxy";
		}
		if constexpr (std::is_same<U, double>::value) {
			try {
				regex_functions::string_is_positive_double(buffers[10]);
			}
			catch (std::runtime_error& e) {
				std::cout << e.what() << std::endl;
			}
			additional_2 = stod(buffers[10]);
		}*/
		process_additional(buffers[9], buffers[10]);
	}
	catch (const std::out_of_range& e) {
		throw e;
		std::cout << e.what() << std::endl;
	}
	return in;
}

template <typename T, typename U>
inline void non_satellite<T, U>::process_additional(const std::string& additional1, const std::string& additional2) {
}

template <>
inline void non_satellite<std::string, double>::process_additional(const std::string& a, const std::string& b) {
	try {
		regex_functions::string_is_positive_double(b);
		regex_functions::morphology_check(a);
	}
	catch (std::runtime_error& e) {
		throw e;
		std::cout << e.what() << std::endl;
	}
	additional_1 = a;
	additional_2 =stod(b);
	type = "galaxy";
}

template <>
inline void non_satellite<double, double>::process_additional(const std::string& a, const std::string& b) {
	try {
		regex_functions::string_is_positive_double(a);
	}
	catch (std::runtime_error& e) {
		throw e;
		std::cout << e.what() << std::endl;
	}
	additional_1 = stod(a);
	type = "star";
	try {
		regex_functions::string_is_positive_double(b);
	}
	catch (std::runtime_error& e) {
		throw e;
		std::cout << e.what() << std::endl;
	}
	additional_2 = stod(b);
}






// satellite member function -- prints object to screen
template<typename T>
inline void satellite<T>::data_out() {
	std::cout << "|" << std::left << std::setw(10) << "ID";
	std::cout << "|" << std::left << std::setw(10) << "RA[\370]";
	std::cout << "|" << std::left << std::setw(10) << "DEC[\370]";
	std::cout << "|" << std::left << std::setw(10) << "Redshift";
	std::cout << "|" << std::left << std::setw(10) << "Mass[M_E]";
	std::cout << "|" << std::left << std::setw(10) << "Radius[R_E]";
	std::cout << "|" << std::left << std::setw(10) << "Orbital Period";
		if (type == "planet") {
				std::cout << "|" << std::left<<std::setw(10) << "Planet Type|" << std::endl;
			}
			else if (type == "moon") {
			    std::cout << "|" << std::left<< std::setw(10) << "Orbits|" << std::endl;
			}
		std::cout << "|" << std::left << std::setw(10) << id;
		std::cout << "|" << std::left << std::setw(10) << right_ascension;
		std::cout << "|" << std::left << std::setw(10) << declination;
		std::cout << "|" << std::left << std::setw(10) << redshift;
		std::cout << "|" << std::left << std::setw(10) << mass;
		std::cout << "|" << std::left << std::setw(10) << radius;
		std::cout << "|" << std::left << std::setw(20) << orbital_period;
		std::cout << "|" << std::left << std::setw(10) << additional << " |" << std::endl;
		

}

// non-satellite member function -- prints out object
template<typename T, typename U>
inline void non_satellite<T, U>::data_out() {
	std::cout  << "|" << std::left << std::setw(9) << "ID"
		<< "|" << std::left << std::setw(9) << "RA[\370]"
		<< "|" << std::left << std::setw(9) << "DEC[\370]"
		<< "|" << std::left << std::setw(9) << "Redshift"
		<< "|" << std::left << std::setw(9) << "Mass"
		<< "|" << std::left << std::setw(9) << "Radius"
		<< "|" << std::left << std::setw(9) << "MAG[AB]"
		<< "|" << std::left << std::setw(9) << "Luminosity"
		<<"|"  << std::left << std::setw(9) << "Age[Gyr]";
	if (type == "galaxy") {
		std::cout<< "|"<<std::left << std::setw(9) << "morphology"
			<< "|"<< std::left << std::setw(9) << "Peculiar Velocity[km/s]|" << std::endl;
	}
	else if (type == "star") {
		std::cout<<"|"<<std::left << std::setw(9) << "Temp[T_6]"
			<< "|" << std::left << std::setw(9) << "Mag.Field[T]|" << std::endl;
	}
	std::cout << "|" << std::left << std::setw(9) << id
		<< "|"<<std::left << std::setw(9) << right_ascension
		<< "|"<<std::left << std::setw(9) << declination
		<< "|"<<std::left << std::setw(9) << redshift
		<< "|"<<std::left << std::setw(9) << mass
		<< "|"<<std::left << std::setw(9) << radius
		<< "|"<<std::left << std::setw(9) << magnitude
		<< "|"<<std::left << std::setw(10) << luminosity
		<< "|"<<std::left << std::setw(9) << age
		<< "|"<<std::left << std::setw(10) << additional_1
		<< "|" << std::left << std::setw(9) << additional_2 << "|" << std::endl;
	
}





#endif

