#include "SubjectManager.hpp"

#include <algorithm>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <utility>

const std::vector<Subject> &SubjectManager::get_subjects() const {
  return m_subjects;
}

void SubjectManager::add_subject(Subject s) {
  m_subjects.push_back(std::move(s));
}

void SubjectManager::update_subject(const std::string &s_id, const Subject &subject) {
  auto it = std::find_if(m_subjects.begin(), m_subjects.end(),
                         [&s_id](const Subject &s) { return s.id() == s_id; });

  if (it == m_subjects.end()) {
    throw std::runtime_error("Subject not found");
  }

  *it = subject;
}

void SubjectManager::delete_subject(const std::string &s_id) {
  auto it = std::find_if(m_subjects.begin(), m_subjects.end(),
                         [&s_id](const Subject &s) { return s.id() == s_id; });

  if (it == m_subjects.end()) {
    throw std::runtime_error("Subject not found");
  }

  m_subjects.erase(it);
}

void SubjectManager::load_from_file(const std::string &path) {
  std::ifstream file(path);
  if (!file.is_open()) {
    throw std::runtime_error("Cannot open file: " + path);
  }

  std::string line;
  while (std::getline(file, line)) {
    if (line.empty())
      continue;

    std::stringstream ss(line);
    std::string code, title, units_str;

    if (!std::getline(ss, code, ','))
      continue;
    if (!std::getline(ss, title, ','))
      continue;
    if (!std::getline(ss, units_str))
      continue;

    try {
      int units = std::stoi(units_str);
      m_subjects.emplace_back(code, title);
      m_subjects.back().set_units(units);
    } catch (const std::exception &) {
      continue;
    }
  }
}
