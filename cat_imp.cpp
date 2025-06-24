#include "astronomical_cat.h"
#include <algorithm>
#include <execution>
#include <fstream>
#include <iomanip>
#include <map>
#include <sstream>
#include <string>

int catalogue::number_catalogues = 0;

// constructor for catalogue-- updates static member
catalogue::catalogue() { number_catalogues++; }

inline catalogue::~catalogue() {}

void catalogue::output_id() { std::cout << catalogue_id; }

void catalogue::output_object_id() {
  for (const auto &object : objects) {
    std::cout << "Object ID: " << object->id << std::endl;
  }
}

std::string catalogue::get_id() { return catalogue_id; }

// catalogue move constructor
catalogue::catalogue(catalogue &&c) noexcept {

  catalogue_id = std::move(c.catalogue_id);
  objects = std::move(c.objects);
}
// catalogue move assignment
catalogue &catalogue::operator=(catalogue &&c) noexcept {
  if (&c == this)
    return *this;
  catalogue_id = std::move(c.catalogue_id);
  objects = std::move(c.objects);
  return *this;
}

// catalogue member function -- outputs all objects of search_type
inline void catalogue::output_type(std::string search_type) {
  for (int i{0}; i < objects.size(); i++) {
    if ((objects[i])->type == search_type) {
      (*objects[i]).data_out();
    }
  }
}

// overload >> for catalogue
std::istream &operator>>(std::istream &is, catalogue &c) {
  std::string object_type;
  if (std::getline(is, object_type, ',')) {

    // Create an object of the derived class based on the object type
    if (object_type == "planet") {
      bool planet_error = false;
      planet *p = new planet;
      // Use a unique_ptr to manage the lifetime of the object
      std::unique_ptr<planet> p_ptr(p);
      try {
        // inputs istream to object *p_ptr
        p_ptr->data_input(is);
      } catch (const std::exception &e) {
        planet_error = true;
        std::cout << "Error: " << e.what() << std::endl;
      }
      if (!planet_error) {
        p_ptr->update_type(object_type);
        // move p_ptr into catalogue
        c.objects.emplace_back(std::move(p_ptr));
        std::cout << "read successful" << std::endl;
      }
    } else if (object_type == "star") {
      bool star_error{false};
      star *s = new star;
      // Use a unique_ptr to manage the lifetime of the object
      std::unique_ptr<star> s_ptr(s);
      try {
        s_ptr->data_input(is);
      } catch (std::exception &e) {
        star_error = true;
        std::cout << "Error: " << e.what() << std::endl;
      }
      if (!star_error) {
        s_ptr->update_type(object_type);
        c.objects.emplace_back(std::move(s_ptr));
        std::cout << "read successful in" << std::endl;
      }
    } else if (object_type == "moon") {
      bool moon_error{false};
      moon *m = new moon;
      // Use a unique_ptr to manage the lifetime of the object
      std::unique_ptr<moon> m_ptr(m);
      try {
        m_ptr->data_input(is);
      } catch (std::exception &e) {
        moon_error = true;
        std::cout << "Error: " << e.what() << std::endl;
      }
      if (!moon_error) {
        m_ptr->update_type(object_type);
        c.objects.emplace_back(std::move(m_ptr));
        std::cout << "read successful" << std::endl;
      }
    } else if (object_type == "galaxy") {
      bool galaxy_error{false};
      galaxy *g = new galaxy;
      // Use a unique_ptr to manage the lifetime of the object
      std::unique_ptr<galaxy> g_ptr(g);
      try {
        g_ptr->data_input(is);
      } catch (std::exception &e) {
        galaxy_error = true;
        std::cout << "Error: " << e.what() << std::endl;
      }
      if (!galaxy_error) {
        g_ptr->update_type(object_type);
        c.objects.emplace_back(std::move(g_ptr));
        std::cout << "read successful" << std::endl;
      }
    }
  } else {
  }

  return is;
}

// overload << for catalogue
std::ostream &operator<<(std::ostream &os, catalogue &c) {
  std::string input;
  bool object_good{false};
  do {
    std::cout
        << "Please enter the type of astronomical object you wish to display"
        << std::endl;
    try {
      std::cin >> input;
      object_good = regex_functions::object_type(input);
    } catch (std::runtime_error e) {
      std::cout << e.what() << std::endl;
    }
  } while (!object_good);
  c.output_type(input);
  return os;
}

inline std::string ask_user_input() {
  std::string object_type;
  bool object_good{false};
  do {
    std::cout << "Please enter the object type : " << std::endl;
    try {
      std::cin >> object_type;
      object_good = regex_functions::object_type(object_type);
    } catch (std::runtime_error e) {
      std::cout << e.what() << std::endl;
    }
  } while (!object_good);
  return object_type;
}

inline void catalogue::add_object(std::unique_ptr<astronomical_object> &obj) {

  // emplace_back used to correctly move obj
  objects.emplace_back(std::move(obj));
}

// catalogue member function -- read into catalogue from user input
void catalogue::user_read() {
  bool continue_read = false;
  while (!continue_read) {
    std::string input = ask_user_input();
    if (input == "planet") {
      std::string buffer{};
      bool input_correct{false};
      do {
        try {
          std::cout
              << "Enter in the following order (comma-seperated): id, "
                 "right-ascension[\370], declination[\370], redshift, "
                 "mass[M_E], radius[R_E], orbital period[Days], planet type"
              << std::endl;
          std::cin.ignore();
          getline(std::cin, buffer);
          input_correct = regex_functions::has_members(buffer, 8);
        } catch (std::runtime_error e) {
          std::cout << e.what() << std::endl;
        }
      } while (!input_correct);
      std::stringstream ss(buffer);
      // calls create_ptr<T> function
      try {
        create_ptr<planet>(ss);
      } catch (std::runtime_error &e) {
        throw e;
      }
      std::string user_choice{};
      std::cout << " Do you want to add another object to this catalogue? (y/n)"
                << std::endl;
      std::cin >> user_choice;
      if (user_choice == "y") {
        continue_read = false;
      } else if (user_choice == "n") {
        continue_read = true;
      }
    } else if (input == "moon") {
      std::string buffer;
      bool moon_input_correct{false};
      do {
        try {
          std::cout << "Enter in the following order (comma-seperated): id, "
                       "right-ascension(\370), declination(\370), redshift, "
                       "mass(M_E), radius(R_E), orbital period(days), "
                       "planetary system"
                    << std::endl;
          std::cin.ignore();
          getline(std::cin, buffer);
          moon_input_correct = regex_functions::has_members(buffer, 8);
        } catch (std::runtime_error e) {
          std::cout << e.what() << std::endl;
        }

      } while (!moon_input_correct);
      std::stringstream ss(buffer);
      try {
        create_ptr<moon>(ss);
      } catch (std::runtime_error &e) {
        std::cout << e.what() << std::endl;
      }
      std::string user_choice{};
      std::cout << " Do you want to add another object to this catalogue? (y/n)"
                << std::endl;
      std::cin >> user_choice;
      if (user_choice == "y") {
        continue_read = false;
      } else if (user_choice == "n") {
        continue_read = true;
      }
    } else if (input == "galaxy") {
      std::string buffer;
      bool galaxy_input_good{false};
      do {
        try {
          std::cout << "Enter in the following order (comma-seperated): id, "
                       "right-ascension[\370], declination[\370], redshift, "
                       "mass[log(M_sol)],radius[kpc],"
                    << std::endl;
          std::cout << "magnitude[AB], age[Gyr], luminosity[Log(L_sol)], "
                       "morphology, peculiar velocity[km / s]"
                    << std::endl;
          std::cin.ignore();
          getline(std::cin, buffer);
          galaxy_input_good = regex_functions::has_members(buffer, 11);
        } catch (std::runtime_error e) {
          std::cout << e.what() << std::endl;
        }
      } while (!galaxy_input_good);
      std::stringstream ss(buffer);
      try {
        create_ptr<galaxy>(ss);
      } catch (std::runtime_error &e) {
        std::cout << e.what() << std::endl;
      }
      std::string user_choice{};
      std::cout << " Do you want to add another object to this catalogue? (y/n)"
                << std::endl;
      std::cin >> user_choice;
      if (user_choice == "y") {
        continue_read = false;
      } else if (user_choice == "n") {
        continue_read = true;
      }
    } else if (input == "star") {
      std::string buffer;
      bool star_input_good{false};
      do {
        try {
          std::cout << "Enter in the following order (comma-seperated): id, "
                       "right-ascension[\370], declination[\370], redshift, "
                       "mass[M_sol],"
                    << std::endl;
          std::cout
              << "radius[R_sol], magnitude[AB], age[Gyr], luminosity[L_sol], "
                 "temperature[T_6], magnetic field strength[B_sol]"
              << std::endl;
          std::cin.ignore();
          getline(std::cin, buffer);
          star_input_good = regex_functions::has_members(buffer, 11);
        } catch (std::runtime_error e) {
          std::cout << e.what() << std::endl;
        }

      } while (!star_input_good);
      std::stringstream ss(buffer);
      try {
        create_ptr<star>(ss);
      } catch (std::runtime_error &e) {
        std::cout << e.what() << std::endl;
      }
      std::string user_choice{};
      std::cout << " Do you want to add another object to this catalogue? (y/n)"
                << std::endl;
      std::cin >> user_choice;
      if (user_choice == "y") {
        continue_read = false;
      } else if (user_choice == "n") {
        continue_read = true;
      }
    } else {
      std::cerr << " Error, not a valid object type" << std::endl;
    }
  }
}

void catalogue::set_id(std::string const id) { catalogue_id = id; }

// catalogue member function -- sorts catalogue by object member
void catalogue::sort(std::string type) {

  std::vector<std::unique_ptr<astronomical_object>> temp_set;
  // move objects with type into temp_set
  for (auto it = objects.begin(); it != objects.end();) {
    if ((*it)->type == type) {
      temp_set.push_back(std::move(*it));
      it = objects.erase(it);
    } else {
      ++it;
    }
  }
  if (type == "planet" || type == "moon") {
    bool sort_column{false};
    std::string choice;
    std::cout << "please enter the column you wish to sort by (1-9)";
    do {
      try {
        std::cin >> choice;
        sort_column = regex_functions::int_between(1, 9, choice);
      } catch (std::runtime_error &e) {
        std::cout << e.what() << std::endl;
      }
    } while (!sort_column);
    int choice_int{stoi(choice)};
    // sort between range of temp_set. sorting function -- lambda that compares
    // members of obj1,obj2 by calling general getter function
    std::cout << "Increasing (1) or Decreaaing order (2)?" << std::endl;
    std::string order{};
    bool order_bool{false};
    do {
      try {
        std::cin >> order;
        order_bool = regex_functions::int_is_either(1, 2, order);
      } catch (std::runtime_error &e) {
        std::cout << e.what();
      }

    } while (!order_bool);
    if (order == "1") {
      std::sort(std::execution::par_unseq, temp_set.begin(), temp_set.end(),
                [choice_int](const std::unique_ptr<astronomical_object> &obj1,
                             const std::unique_ptr<astronomical_object> &obj2) {
                  return obj1->get_all_new()[choice_int] <
                         obj2->get_all_new()[choice_int];
                });
    } else if (order == "2") {
      std::sort(std::execution::par_unseq, temp_set.begin(), temp_set.end(),
                [choice_int](const std::unique_ptr<astronomical_object> &obj1,
                             const std::unique_ptr<astronomical_object> &obj2) {
                  return obj1->get_all_new()[choice_int] >
                         obj2->get_all_new()[choice_int];
                });
    }
  } else if (type == "galaxy" || type == "star") {
    bool non_satellite_sort_choice{false};
    std::string choice_nonsatellite;
    std::cout << "please enter the column you wish to sort by (1-11)";
    do {
      std::cin >> choice_nonsatellite;
      try {
        non_satellite_sort_choice =
            regex_functions::between_1_11(choice_nonsatellite);
      } catch (std::runtime_error &e) {
        std::cout << e.what() << std::endl;
      }
    } while (!non_satellite_sort_choice);
    int choice_int{stoi(choice_nonsatellite)};
    std::cout << "Increasing (1) or Decreasing (2) order?" << std::endl;
    std::string order_choice{};
    bool bool_order{false};
    do {
      try {
        std::cin >> order_choice;
        bool_order = regex_functions::int_is_either(1, 2, order_choice);
      } catch (std::runtime_error &e) {
        std::cout << e.what() << std::endl;
        ;
      }

    } while (!bool_order);
    if (order_choice == "1") {
      std::sort(std::execution::par_unseq, temp_set.begin(), temp_set.end(),
                [choice_int](const std::unique_ptr<astronomical_object> &obj1,
                             const std::unique_ptr<astronomical_object> &obj2) {
                  return obj1->get_all_new()[choice_int] <
                         obj2->get_all_new()[choice_int];
                });
    } else if (order_choice == "2") {
      std::sort(std::execution::par_unseq, temp_set.begin(), temp_set.end(),
                [choice_int](const std::unique_ptr<astronomical_object> &obj1,
                             const std::unique_ptr<astronomical_object> &obj2) {
                  return obj1->get_all_new()[choice_int] >
                         obj2->get_all_new()[choice_int];
                });
    }
  }
  for (int i{}; i < temp_set.size(); i++) {
    (*temp_set[i]).data_out();
  }
  // Move the filtered objects back into the original vector
  objects.insert(objects.end(), std::make_move_iterator(temp_set.begin()),
                 std::make_move_iterator(temp_set.end()));
}

void catalogue::delete_object(std::string id_delete) {

  try {
    // iterates through objects, returns id_match
    std::vector<std::unique_ptr<astronomical_object>>::iterator object =
        find_if(objects.begin(), objects.end(),
                [&](std::unique_ptr<astronomical_object> &obj) {
                  return obj->id == id_delete;
                });
    // deletes id_match object from objects
    if (object != objects.end()) {
      // deletes id_match object from objects
      objects.erase(std::remove(objects.begin(), objects.end(), *object));
    } else {
      // Handle the case when no match is found
      std::cout << "No matching object found." << std::endl;
    }
  } catch (const std::out_of_range &e) {
    std::cout << e.what() << " Object doesn't exist";
  }
}

// member function to write a catalogue to csv file
void catalogue::write_to_csv(const std::string &filename) {
  std::ofstream file(filename);
  if (!file.is_open()) {
    std::cerr << " Error in File" << std::endl;
  }
  // iterates through objects
  for (const auto &obj : objects) {
    // calls general getter function
    const auto members = obj->get_all_new();
    // iterates through getter function
    for (size_t i = 0; i < members.size(); ++i) {
      // uses custom variant_type visit function and print_visitor class
      members[i].visit(print_visitor(file));
      if (i < members.size() - 1) {
        file << ",";
      }
    }
    file << std::endl;
  }

  /*for (const auto& obj : objects) {
      const auto members = obj->get_all_new();
      for (size_t i = 0; i < members.size(); ++i) {
          std::visit([&file](const auto& member) {
              file << member; },members[i]);
          if (i < members.size() - 1) {
              file << ",";
          }
      }
      file << std::endl;
  }*/
  file.close();
  std::cout << "Data written to the CSV file: " << filename << std::endl;
}

// member function to read csv from file
void catalogue::csv_read(const std::string &filename, std::string cat_id) {
  catalogue cat;
  cat.set_id(cat_id);
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Failed to open file\n";
    return;
  }
  // Read each line of the CSV file
  std::string line;
  int row_num{0};
  while (std::getline(file, line)) {
    row_num++;
    std::cout << "Row number:" << row_num << std::endl;
    ;
    std::istringstream iss(line);
    // call overloaded >> for catalogue
    iss >> cat;
  }
  // efficiently move into objects
  objects = std::move(cat.objects);
  set_id(cat_id);
  return;
}