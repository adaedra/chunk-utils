#include "mc/nbt/string.hh"

#include <boost/endian.hpp>

#include "input.hh"

uint8_t const mc::nbt::string::TAG {8};

uint8_t mc::nbt::string::tag() const { return TAG; }

mc::nbt::string::string(std::string && s) : _s {s} {}

mc::nbt::string::string(string const & other) : _s {other._s} {}

mc::nbt::any mc::nbt::string::clone() const { return std::make_unique<string>(*this); }

mc::nbt::string mc::nbt::string::parse(input & input) {
    auto sz {input.value<boost::endian::big_uint16_t>()};
    auto result {input.string(sz)};

    return string(std::move(result));
}

void mc::nbt::string::snbt(std::ostream & stream) const { stream << '"' << _s << '"'; }

std::string const & mc::nbt::string::data() const { return _s; }
