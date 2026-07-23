#ifndef STUDENT_MANAGER_HPP
#define STUDENT_MANAGER_HPP

#include "Student.hpp"
#include <string>
#include <utility>
#include <vector>

class StudentNode {
public:
  int key;
  Student student;
  StudentNode *next{nullptr};

  StudentNode(Student s) : student{std::move(s)}, next{nullptr} {}
};

class StudentManager {
private:
  std::vector<StudentNode *> students{1000, nullptr};

  int student_count{0};

  int hash(const int &key);

  void clear();

public:
  StudentManager() = default;
  ~StudentManager();

  StudentManager(const StudentManager &other);
  StudentManager &operator=(const StudentManager &other);
  StudentManager(StudentManager &&other) noexcept;
  StudentManager &operator=(StudentManager &&other) noexcept;

  void update(const std::string &student_id, const Student &student);

  void put(const Student &student, const int &key);
  bool remove(const int &key);
  bool remove(const std::string &sid);
  Student get(const int &key);
  std::vector<StudentNode *> &get_students();
  const std::vector<StudentNode *> &get_students() const;
  Student get(const std::string &student_id);
  void print() const;
  void print(std::string &student_id) const;
  const int &size() const;
};

#endif
