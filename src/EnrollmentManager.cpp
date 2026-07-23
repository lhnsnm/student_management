#include "EnrollmentManager.hpp"

#include <algorithm>
#include <stdexcept>
#include <utility>

const std::vector<Enrollment> &EnrollmentManager::get_enrollments() const {
  return m_enrollments;
}

void EnrollmentManager::add_enrollment(Enrollment enrollment) {
  m_enrollments.push_back(std::move(enrollment));
}

void EnrollmentManager::update_enrollment(const std::string &enrollment_id, const Enrollment &enrollment) {
  auto it = std::find_if(m_enrollments.begin(), m_enrollments.end(),
                         [&enrollment_id](const Enrollment &e) { return e.id() == enrollment_id; });

  if (it == m_enrollments.end()) {
    throw std::runtime_error("Enrollment not found");
  }

  *it = enrollment;
}

void EnrollmentManager::delete_enrollment(const std::string &enrollment_id) {
  auto it = std::find_if(m_enrollments.begin(), m_enrollments.end(),
                         [&enrollment_id](const Enrollment &e) { return e.id() == enrollment_id; });

  if (it == m_enrollments.end()) {
    throw std::runtime_error("Enrollment not found");
  }

  m_enrollments.erase(it);
}
