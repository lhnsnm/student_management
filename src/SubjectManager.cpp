#include "SubjectManager.hpp"
#include "FileManager.hpp"

#include <algorithm>
#include <stdexcept>
#include <string>
#include <utility>

const std::vector<Subject> &SubjectManager::get_subjects() const {
  return m_subjects;
}

void SubjectManager::add_subject(Subject s, const std::string &path) {
  m_subjects.push_back(std::move(s));

  FileManager fm;
  fm.write_subject_file(path, m_subjects.back());
}

void SubjectManager::update_subject(const std::string &s_id,
                                    const Subject &subject,
                                    const std::string &path) {
  auto it =
      std::find_if(m_subjects.begin(), m_subjects.end(),
                   [&s_id](const Subject &curr) { return curr.id() == s_id; });

  if (it == m_subjects.end()) {
    throw std::runtime_error("Subject not found");
  }

  *it = subject;

  FileManager fm;

  fm.update_subject_file(path, *it);
}

void SubjectManager::delete_subject(const std::string &s_id,
                                    const std::string &path) {
  auto it =
      std::find_if(m_subjects.begin(), m_subjects.end(),
                   [&s_id](const Subject &curr) { return curr.id() == s_id; });

  if (it == m_subjects.end()) {
    throw std::runtime_error("Subject not found");
  }

  FileManager fm;
  fm.delete_subject_file(path, *it);

  m_subjects.erase(it);
}

void SubjectManager::load_from_file(const std::string &path) {
  FileManager fm;
  fm.load_subject_file(path, *this);
}
