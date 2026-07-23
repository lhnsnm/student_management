#ifndef SUBJECT_MANAGER_HPP
#define SUBJECT_MANAGER_HPP

#include "Subject.hpp"
#include <string>
#include <vector>

class SubjectManager {
private:
  std::vector<Subject> m_subjects{};

public:
  SubjectManager() = default;

  const std::vector<Subject> &get_subjects() const;

  void add_subject(Subject s);
  void update_enrollment(const std::string &s_id);
  void delete_enrollment(const std::string &s_id);
};

#endif
