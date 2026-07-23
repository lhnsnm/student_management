#ifndef SUBJECT_HPP
#define SUBJECT_HPP

#include <string>

class Subject {
private:
  std::string m_id;
  std::string m_code;
  std::string m_title;

public:
  Subject(std::string code, std::string title);

  // Getters
  const std::string &id() const;
  const std::string &code() const;
  const std::string &title() const;

  // Setters
  void set_code(std::string code);
  void set_title(std::string title);
};

#endif
