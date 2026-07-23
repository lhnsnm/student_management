#include <algorithm>
#include <cctype>
#include <exception>
#include <iomanip>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>

#include "EnrollmentManager.hpp"
#include "Student.hpp"
#include "StudentManager.hpp"
#include "SubjectManager.hpp"

bool add_student(StudentManager &sm, int &key);
void view_students(const StudentManager &sm);
void search_student(const StudentManager &sm);
bool delete_student(StudentManager &sm);
bool update_student(StudentManager &sm);
bool enroll_student(EnrollmentManager &em, SubjectManager &sm);

std::string to_lowercase(const std::string &str) {
  std::string result = str;
  std::transform(result.begin(), result.end(), result.begin(),
                 [](unsigned char c) { return std::tolower(c); });
  return result;
}

int main() {
  StudentManager student_manager;
  SubjectManager subject_manager;
  EnrollmentManager enrollment_manager;

  subject_manager.load_from_file("data/subjects.txt");

  int key_id = 1;

  while (1) {
    std::cout << "Student Management Program\n"
              << "(1) Add student\n"
              << "(2) View students\n"
              << "(3) Delete student\n"
              << "(4) Update student\n"
              << "(5) Search student\n"
              << "(6) Enroll student\n"
              << "(-1) To quit\n"
              << "Select option: ";

    int option;
    std::cin >> option;

    if (option == -1)
      goto end_loop;

    if (option == 1) {
      if (!add_student(student_manager, key_id)) {
        continue; // FIX: Do not quit the menu on add failure, just continue
                  // loop
      }
      key_id++;
    }

    if (option == 2) {
      view_students(student_manager);
    }

    if (option == 3) {
      delete_student(student_manager);
    }

    if (option == 4) {
      update_student(student_manager);
    }

    if (option == 5) {
      search_student(student_manager);
    }

    if (option == 6) {
      enroll_student(enrollment_manager, subject_manager);
    }
  }

end_loop:

  return 0;
}

bool add_student(StudentManager &sm, int &key) {
  try {
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

    Student s(std::move(fname), std::move(lname));
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

void search_student(const StudentManager &sm) {
  std::vector<StudentNode *> result;
  std::string input;
  std::cout << "Search student: " << std::endl;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::getline(std::cin, input);

  std::string lowered_input = to_lowercase(input);

  std::copy_if(
      sm.get_students().begin(), sm.get_students().end(),
      std::back_inserter(result), [&lowered_input](StudentNode *node) {
        if (!node)
          return false;
        return to_lowercase(node->student.get_name()) == lowered_input ||
               to_lowercase(node->student.get_first_name()) == lowered_input ||
               to_lowercase(node->student.get_last_name()) == lowered_input;
      });

  if (result.empty()) {
    std::cout << "No students found." << std::endl;
  } else {
    std::cout << std::left << std::setw(40) << "ID" << std::setw(20)
              << "First Name" << "Last Name" << std::endl;
    for (const StudentNode *node : result) {
      std::cout << std::left << std::setw(40) << node->student.get_id()
                << std::setw(20) << node->student.get_first_name()
                << node->student.get_last_name() << std::endl;
    }
  }

  std::cin.get();
}

bool delete_student(StudentManager &sm) {
  std::cout << "Delete student" << std::endl;
  std::string sid;
  std::cout << "Enter the id of the student: ";
  std::cin >> sid;

  if (!sm.remove(sid)) {
    std::cerr << "Cannot delete student" << std::endl;
    return false;
  };
  return true;
}

bool update_student(StudentManager &sm) {
  try {
    std::cout << "Update student" << std::endl;
    std::string sid;
    std::cout << "Enter the id of the student: ";
    std::cin >> sid;

    Student s = sm.get(sid);

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

    sm.update(sid, s);

    return true;
  } catch (const std::runtime_error &e) {
    std::cerr << "Caught an exception: " << e.what() << std::endl;
    return false;
  } catch (const std::exception &e) {
    std::cerr << "Caught standard exception: " << e.what() << std::endl;
    return false;
  }
}

bool enroll_student(EnrollmentManager &em, SubjectManager &sm) {
  try {
    std::cout << "Enroll student" << std::endl;
    std::string sid;
    std::cout << "Enter student ID: ";
    std::cin >> sid;

    if (sm.get_subjects().empty()) {
      std::cerr << "No subjects available" << std::endl;
      return false;
    }

    std::cout << "Available subjects:" << std::endl;
    for (const auto &subject : sm.get_subjects()) {
      std::cout << "  " << subject.code() << " - " << subject.title() << " ("
                << subject.units() << " units)" << std::endl;
    }

    std::string code;
    std::cout << "Enter subject code: ";
    std::cin >> code;

    em.add_enrollment(Enrollment(sid, code));
    std::cout << "Enrollment successful" << std::endl;
    return true;
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    return false;
  }
}
