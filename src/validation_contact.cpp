#include "validation_contact.hpp"
#include <regex>

bool Validation::is_valid_email(const std::string &email)
{
    // Standard email pattern: checks for name, @ symbol, domain name, and extension
    const std::regex email_pattern(
        R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");

    return std::regex_match(email, email_pattern);
}

bool Validation::is_valid_phone(const std::string &phone)
{
    // Flexible international pattern. Matches formats like:
    // +1234567890, +1 (234) 567-8901, 123-456-7890, or 1234567890
    const std::regex phone_pattern(
        R"(^(\+\d{1,3}[- ]?)?\(?\d{3}\)?[- ]?\d{3}[- ]?\d{4}$)");

    return std::regex_match(phone, phone_pattern);
}
