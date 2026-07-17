#include "uuid.hpp"

boost::uuids::uuid get_uuid()
{
    boost::uuids::random_generator gen;
    return gen();
};

std::string get_uuid_string()
{
    return boost::uuids::to_string(get_uuid());
}