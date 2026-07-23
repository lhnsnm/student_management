#ifndef ENROLLMENT_MANAGER_HPP
#define ENROLLMENT_MANAGER_HPP

#include "Enrollment.hpp"
#include <string>
#include <vector>

class EnrollmentManager {
private:
  std::vector<Enrollment> m_enrollments{};

public:
  EnrollmentManager() = default;

  const std::vector<Enrollment> &get_enrollments() const;

  void add_enrollment(Enrollment enrollment);
  void update_enrollment(const std::string &enrollment_id);
  void delete_enrollment(const std::string &enrollment_id);
};

#endif
