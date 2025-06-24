#include "astronomical_cat.h"
#include "object_interface.h"
#include <fstream>

// demonstration of catalogue,classes etc.

int main() {

  std::vector<std::unique_ptr<catalogue>> cat_vector;
  bool programexit = false;
  int mainmenu{0};
  int submenu{0};
  while (!programexit) {
    std::cout << "Welcome to ACEO -- The Astronomical Catalogue for "
                 "Extragalactic Objects--"
              << std::endl;
    std::cout << "This is the Main menu -- Please Select a Following option"
              << std::endl;
    std::string s;
    if (catalogue::number_catalogues == 0) {
      bool continue_bool = false;
      std::cout << "1) Create new catalogue" << std::endl;
      std::cout << "4) Exit" << std::endl;
      do {
        std::cin >> s;
        try {
          continue_bool = regex_functions::int_is_either(1, 4, s);
        } catch (std::runtime_error &e) {
          std::cout << e.what() << std::endl;
        }

      } while (!continue_bool);

    } else {
      bool continue_bool = false;
      std::cout << "1) Create new catalogue" << std::endl;
      std::cout << "2) Select current catalogue" << std::endl;
      std::cout << "3) Delete a current catalogue" << std::endl;
      std::cout << "4) Exit" << std::endl;
      do {
        std::cin >> s;
        try {
          continue_bool = regex_functions::int_between(1, 4, s);
        } catch (std::runtime_error &e) {
          std::cout << e.what() << std::endl;
        }
      } while (!continue_bool);
    }
    mainmenu = stoi(s);
    switch (mainmenu) {
    case 1: {
      std::string s_2{};
      bool continue_main_menu{false};
      std::cout << "Please select:" << std::endl;
      std::cout << "1) Enter from Keyboard" << std::endl;
      std::cout << "2) Read in from file" << std::endl;
      std::cout << "3) Return to Main menu" << std::endl;
      do {
        try {
          std::cin >> s_2;
          continue_main_menu = regex_functions::int_between(1, 3, s_2);
        } catch (std::runtime_error &e) {
          std::cout << e.what() << std::endl;
        }
      } while (!continue_main_menu);
      submenu = stoi(s_2);
      switch (submenu) {
      case 1: {
        catalogue cat;
        bool is_id_good{false};
        std::string s;
        std::cout << "Please enter the ID you wish to name the catalogue, "
                     "please make it a 4 digit number"
                  << std::endl;
        do {
          try {
            std::cin >> s;
            is_id_good = regex_functions::is_four_digits(s);
          } catch (std::runtime_error &e) {
            std::cout << e.what() << std::endl;
          }
        } while (!is_id_good);
        try {
          cat.user_read();
          cat.set_id(s);
          cat_vector.emplace_back(new catalogue(std::move(cat)));

        } catch (std::runtime_error &e) {
          std::cout << e.what() << std::endl;
        }
        break;
      }
      case 2: {
        catalogue cat;
        std::string s;
        bool is_id_good{false};
        std::cout << "Please enter the ID you wish to name the catalogue, "
                     "please make it a 4 digit number"
                  << std::endl;
        do {
          try {
            std::cin >> s;
            is_id_good = regex_functions::is_four_digits(s);
          } catch (std::runtime_error &e) {
            std::cout << e.what() << std::endl;
          }
        } while (!is_id_good);
        std::cout << "Please enter the name of the file";
        std::string filename{};
        std::cin >> filename;
        cat.csv_read(filename, s);
        cat_vector.emplace_back(new catalogue(std::move(cat)));
        break;
      }
      case 3:
        break;
      default:
        std::cout << "Invalid choice. Please re-enter" << std::endl;
        break;
      }
      if (submenu == 3) {
        break;
      }
      break;

      break;
    }
    case 2: {
      for (int i{0}; i < cat_vector.size(); i++) {
        (*cat_vector[i]).output_id();
        std::cout << std::endl;
      }
      std::cout << "Please select the catalogue you wish to inspect:"
                << std::endl;
      std::string catalogue_choice{};
      std::cin >> catalogue_choice;
      auto it = std::find_if(
          cat_vector.begin(), cat_vector.end(),
          [catalogue_choice](const std::unique_ptr<catalogue> &cat_ptr) {
            return cat_ptr->get_id() == catalogue_choice;
          });
      if (it != cat_vector.end()) {
        std::cout << **it;
        std::string s_3{};
        bool continue_sub_catalogue{false};
        std::cout << "Please select what you want to do with this catalogue."
                  << std::endl;
        std::cout << "1) Display data of certain object and sort" << std::endl;
        std::cout << "2) Delete an object" << std::endl;
        std::cout << "3) Add an object to this catalogue" << std::endl;
        std::cout << "4) Read catalogue to file" << std::endl;
        std::cout << "5) Return to Main menu" << std::endl;
        do {
          try {
            std::cin >> s_3;
            continue_sub_catalogue = regex_functions::int_between(1, 5, s_3);
          } catch (std::runtime_error &e) {
            std::cout << e.what() << std::endl;
          }
        } while (!continue_sub_catalogue);
        submenu = stoi(s_3);
        switch (submenu) {
        case 1: {
          bool object_submenu_choice{false};
          std::cout << "Please enter what object type you want to sort";
          std::string sort_type;
          do {
            try {
              std::cin >> sort_type;
              object_submenu_choice = regex_functions::object_type(sort_type);
            } catch (std::runtime_error &e) {
              std::cout << e.what() << std::endl;
            }

          } while (!object_submenu_choice);
          (**it).sort(sort_type);
          break;
        }
        case 2: {
          (**it).output_object_id();
          bool delete_choice{false};
          std::cout << "Please enter the ID of the object you wish to delete"
                    << std::endl;
          std::string id_del;
          do {
            try {
              std::cin >> id_del;
              delete_choice = regex_functions::id_check(id_del);
            } catch (std::runtime_error &e) {
              std::cout << e.what() << std::endl;
            }
          } while (!delete_choice);
          (**it).delete_object(id_del);
          break;
        }
        case 3: {
          (**it).user_read();
          break;
        }
        case 4: {
          std::cout << "Please enter the filename you wish to use (xxxxx.csv)"
                    << std::endl;
          std::string filename{};
          bool is_file_correct{false};
          do {
            try {
              std::cin >> filename;
              is_file_correct = regex_functions::is_csv(filename);
            } catch (std::runtime_error &e) {
              std::cout << e.what() << std::endl;
            }
          } while (!is_file_correct);
          (**it).write_to_csv(filename);
          break;
        }
        case 5: {
          break;
        }
        }
      } else {
        std::cout << "That catalogue does not exist" << std::endl;
      }

      break;
    }
    case 3: {
      for (int i{0}; i < cat_vector.size(); i++) {
        (*cat_vector[i]).output_id();
        std::cout << std::endl;
      }
      std::string delete_choice{};
      std::cout << "Please select the catalogue you wish to delete:"
                << std::endl;

      std::cin >> delete_choice;

      try {
        auto it_1 = std::find_if(
            cat_vector.begin(), cat_vector.end(),
            [delete_choice](const std::unique_ptr<catalogue> &cat_ptr) {
              return cat_ptr->get_id() == delete_choice;
            });
        cat_vector.erase(it_1);
      } catch (std::out_of_range &e) {
        std::cout << e.what() << std::endl;
        std::cout << "Catalogue does not exist " << std::endl;
      }

      break;
    }
    case 4: {
      programexit = false;
      break;
    }
    default:
      std::cout << "Invalid input -- Please re-enter" << std::endl;
    }
  }
  return 0;
}