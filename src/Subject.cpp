#include "Subject.hpp"
#include "uuid.hpp"
#include <utility>

Subject::Subject(std::string code, std::string title)
    : m_code{std::move(code)}, m_title{std::move(title)} {
  m_id = get_uuid_string();
};

const std::string &Subject::id() const { return m_id; };

const std::string &Subject::code() const { return m_code; };

void Subject::set_code(std::string code) {
  if (code.length() < 2)
    return;
  m_code = std::move(code);
};

void Subject::set_title(std::string title) {
  if (title.length() < 4)
    return;
  m_title = std::move(title);
};
