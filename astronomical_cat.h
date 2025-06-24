#ifndef MY_CATALOGUE_H
#define MY_CATALOGUE_H

#include "object_interface.h"
#include <vector>
#include <memory>
#include<type_traits>
#include<iostream>

class catalogue {

    friend std::istream& operator>>(std::istream& is, catalogue& c);
    friend std::ostream& operator<<(std::ostream& os, catalogue& c);


protected:
    std::string catalogue_id;
    std::vector<std::unique_ptr<astronomical_object>> objects;

public:
    static int number_catalogues;
    catalogue();
    ~catalogue();
    catalogue(catalogue&&) noexcept;
    catalogue& operator=(catalogue&&)noexcept;
    void add_object(std::unique_ptr<astronomical_object>& obj);
    void csv_read(const std::string& file,std::string cat_id);
    void user_read();
    void sort(std::string type);
    template <typename T>
    void create_ptr(std::istream& is);
    void output_type(std::string search_type);
    void output_id();
    void clear_memory();
    void output_object_id();
    std::string get_id();
    void set_id(std::string const id);
    void delete_object(std::string);
    void write_to_csv(const std::string& filename);

};


// structure --  allows type of template to be retrieved
template <typename T>
struct type_of
{
    static std::string get_type()
    {
        return typeid(T).name();
    }
};

// catalogue member function -- adds an object of given type to catalogue::objects
template <typename T>
inline void catalogue::create_ptr(std::istream& is) {
    T* obj = new T;
    std::unique_ptr<T> o_ptr(obj);
    try {
        o_ptr->data_input(is);
    }
    catch (std::runtime_error& e) {
        throw e;
    }
    std::string type_of_temp = type_of<T>::get_type();
    std::string word{};
    size_t space = type_of_temp.find(' ');
    if (space != std::string::npos) {
        word = type_of_temp.substr(space + 1);
    }
    o_ptr->type = word;
    objects.emplace_back(std::move(o_ptr));
}

#endif

