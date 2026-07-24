#ifndef SUBJECT_MANAGER_HPP
#define SUBJECT_MANAGER_HPP

#include "Subject.hpp"
#include <string>
#include <vector>

class FileManager;

class SubjectManager {
private:
  std::vector<Subject> m_subjects{};

public:
  SubjectManager() = default;

  const std::vector<Subject> &get_subjects() const;

  void add_subject(Subject s, const std::string &path);
  void update_subject(const std::string &s_id, const Subject &subject,
                      const std::string &path);
  void delete_subject(const std::string &s_id, const std::string &path);
  void load_from_file(const std::string &path);

  friend class FileManager;
};

#endif
