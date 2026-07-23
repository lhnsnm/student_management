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
  void update_subject(const std::string &s_id, const Subject &subject);
  void delete_subject(const std::string &s_id);
  void load_from_file(const std::string &path);
};

#endif
