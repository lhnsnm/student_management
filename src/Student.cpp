#include "Student.hpp"
#include "validation_contact.hpp"
#include <cctype>
#include <algorithm> // Required for std::transform
#include <iostream>  // Required for std::cerr
#include <utility>   // Required for std::move

// Helper function (Pass by reference, modify in place, return void)
void capitalize_name(std::string &name)
{
    if (name.empty())
        return;

    // Lowercase every character in the string
    std::transform(
        name.begin(),
        name.end(),
        name.begin(),
        [](unsigned char c)
        { return std::tolower(c); });

    // Uppercase only the very first character
    name[0] = static_cast<char>(std::toupper(static_cast<unsigned char>(name[0])));
}

// Constructor implementation
Student::Student(
    const std::string &first_name,
    const std::string &last_name)
    : m_first_name{std::move(first_name)},
      m_last_name{std::move(last_name)},
      m_year_level{1}
{
    m_id = get_uuid_string();
    capitalize_name(m_first_name);
    capitalize_name(m_last_name);
}

// Getter implementations
const std::string &Student::get_id() const
{
    return m_id;
}

const std::string &Student::get_first_name() const
{
    return m_first_name;
}

const std::string &Student::get_last_name() const
{
    return m_last_name;
}

std::string Student::get_name() const
{
    return m_first_name + " " + m_last_name;
}

int Student::get_year_level() const
{
    return m_year_level;
}

const std::optional<std::string> &Student::get_email() const
{
    return m_email;
}

const std::optional<std::string> &Student::get_phone() const
{
    return m_phone;
}

// Setters implementations

void Student::set_first_name(std::string first_name)
{
    if (first_name.length() < 3)
        return;

    capitalize_name(first_name);
    m_first_name = std::move(first_name);
}

void Student::set_last_name(std::string last_name)
{
    if (last_name.length() < 3)
        return;

    capitalize_name(last_name);
    m_last_name = std::move(last_name);
}

void Student::set_year_level(int year_level)
{
    m_year_level = std::move(year_level);
}

void Student::set_email(std::string email)
{
    if (Validation::is_valid_email(email))
    {
        m_email = std::move(email);
    }
    else
    {
        std::cerr << "Error: Invalid email format\n";
    }
}

void Student::set_phone(std::string phone)
{
    if (Validation::is_valid_phone(phone))
    {
        m_phone = std::move(phone);
    }
    else
    {
        std::cerr << "Error: Invalid phone number format\n";
    }
}