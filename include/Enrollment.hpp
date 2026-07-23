#ifndef ENROLLMENT_HPP
#define ENROLLMENT_HPP

#include <string>

class Enrollment {
private:
  std::string m_id;
  std::string m_student_id;
  std::string m_subject_code;

public:
  Enrollment(std::string student_id, std::string subject_code);

  const std::string &student_id() const;
  const std::string &subject_code() const;

  void set_student_id(std::string id);
  void set_subject_code(std::string code);
};

#endif
