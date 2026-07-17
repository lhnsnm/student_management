#pragma once

#include <string>
#include <optional>
#include "uuid.hpp"

class Student
{
private:
    std::string m_id;
    std::string m_first_name;
    std::string m_last_name;
    int m_year_level;
    std::optional<std::string> m_email;
    std::optional<std::string> m_phone;

public:
    // Constructor declaration (Default arguments belong ONLY in the header)
    Student(
        const std::string &first_name,
        const std::string &last_name);

    // Getters
    const std::string &get_id() const;
    const std::string &get_first_name() const;
    const std::string &get_last_name() const;
    std::string get_name() const;
    int get_year_level() const;
    const std::optional<std::string> &get_email() const;
    const std::optional<std::string> &get_phone() const;

    // Setters
    void set_first_name(std::string first_name);
    void set_last_name(std::string last_name);
    void set_year_level(int year_level);
    void set_email(std::string email);
    void set_phone(std::string phone);
};
