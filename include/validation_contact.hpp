#pragma once
#include <string>

namespace Validation {
    // Returns true if the email format is valid
    bool is_valid_email(const std::string& email);

    // Returns true if the phone number format is valid
    bool is_valid_phone(const std::string& phone);
}
