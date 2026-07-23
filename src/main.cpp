#include <exception>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>

#include "Student.hpp"
#include "StudentManager.hpp"

bool add_student(std::string f_name, std::string l_name, int year,
                 StudentManager &sm, int &key);
void view_students(const StudentManager &sm);
bool delete_student(const std::string &id,
                    StudentManager &sm); // FIX: Signature must match definition
                                         // (const std::string&)
bool update_student(const std::string &id, StudentManager &sm);

int main() {
  StudentManager student_manager;

  bool quit = 0;
  int key_id = 1;

  while (!quit) {
    std::cout << "Student Management Program\n"
              << "(1) Add student\n"
              << "(2) View students\n"
              << "(3) Delete student\n"
              << "(4) Update student\n"
              << "(-1) To quit\n"
              << "Select option: ";

    int option;
    std::cin >> option;

    if (option == -1)
      goto end_loop;

    if (option == 1) {
      std::string fname, lname;
      int year;
      std::cout << "Add student\n"
                << "Enter first name: ";
      std::cin >> fname;

      std::cout << "Enter last name: ";
      std::cin >> lname;

      std::cout << "Enter year level: ";
      while (!(std::cin >> year)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Enter year level: ";
      }

      if (!add_student(fname, lname, year, student_manager, key_id)) {
        continue; // FIX: Do not quit the menu on add failure, just continue
                  // loop
      }

      key_id++;
    }

    if (option == 2) {
      view_students(student_manager);
    }

    if (option == 3) {
      std::cout << "Delete student" << std::endl;
      std::string sid;
      std::cout << "Enter the id of the student: ";
      std::cin >> sid;
      delete_student(sid, student_manager);
    }

    if (option == 4) {
      std::cout << "Update student" << std::endl;
      std::string sid;
      std::cout << "Enter the id of the student: ";
      std::cin >> sid;
      update_student(sid, student_manager);
    }

    if (option > 4) {
      std::cout << "Invalid option" << std::endl;
      return 1;
    }
  }

end_loop:

  return 0;
}

bool add_student(std::string f_name, std::string l_name, int year,
                 StudentManager &sm, int &key) {
  try {
    Student s(std::move(f_name), std::move(l_name));
    s.set_year_level(std::move(year));
    sm.put(s, key);
  } catch (const std::runtime_error &e) {
    std::cerr << "Caught an exception: " << e.what() << std::endl;
    return false;
  } catch (const std::exception &e) {
    std::cerr << "Caught standard exception: " << e.what() << std::endl;
    return false;
  }

  return true;
}

void view_students(const StudentManager &sm) {
  std::cout << "View students" << std::endl;
  sm.print();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                  '\n'); // Clear buffer
  std::cin.get();        // Wait for user keystroke
}

bool delete_student(const std::string &id, StudentManager &sm) {
  sm.remove(id);
  return true;
}

bool update_student(const std::string &id, StudentManager &sm) {
  try {
    Student s = sm.get(id);

    std::string fname = s.get_first_name();
    std::cout << "Enter new first name: ";
    std::cin >> fname;

    std::string lname = s.get_last_name();
    std::cout << "Enter new last name: ";
    std::cin >> lname;

    std::cout << "Enter new year level: ";
    int year;
    while (!(std::cin >> year)) {
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Invalid input. Enter new year level: ";
    }

    s.set_first_name(fname);
    s.set_last_name(lname);
    s.set_year_level(year);

    sm.update(id, s);

    return true;
  } catch (const std::runtime_error &e) {
    std::cerr << "Caught an exception: " << e.what() << std::endl;
    return false;
  } catch (const std::exception &e) {
    std::cerr << "Caught standard exception: " << e.what() << std::endl;
    return false;
  }
}
