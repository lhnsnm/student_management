#include <utility>

#include "Enrollment.hpp"
#include "uuid.hpp"

Enrollment::Enrollment(std::string student_id, std::string subject_code)
    : m_student_id{std::move(student_id)},
      m_subject_code{std::move(subject_code)} {
  m_id = get_uuid_string();
}

const std::string &Enrollment::student_id() const {
  // FIX: Return student ID, not enrollment UUID
  return m_student_id;
}

const std::string &Enrollment::subject_code() const { return m_subject_code; }

void Enrollment::set_student_id(std::string id) {
  if (!id.length())
    return;
  // FIX: Assign to student ID member, not enrollment ID
  m_student_id = std::move(id);
}

void Enrollment::set_subject_code(std::string code) {
  if (!code.length())
    return;
  m_subject_code = std::move(code);
}
