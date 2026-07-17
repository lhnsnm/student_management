#pragma once

#include <boost/uuid/uuid.hpp>            // Main UUID class
#include <boost/uuid/uuid_generators.hpp> // Generators (random, time-based, etc.)
#include <boost/uuid/uuid_io.hpp>         // Streaming operator to convert to string

boost::uuids::uuid get_uuid();
std::string get_uuid_string();