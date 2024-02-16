#include "mc/nbt/compound.hh"

#include <boost/endian.hpp>
#include <fmt/format.h>
#include <sstream>

#include "array_stream.hh"
#include "input.hh"

uint8_t const mc::nbt::compound::TAG { 10 };
uint8_t const mc::nbt::compound::END { 0 };

uint8_t mc::nbt::compound::tag() const { return TAG; }

mc::nbt::compound::compound() = default;

mc::nbt::compound mc::nbt::compound::parse(input & input) {
    compound result;

    for (;;) {
        auto tag { input.value<uint8_t>(UINT8_MAX) };

        if (tag == compound::END) {
            return result;
        }

        auto name_sz { input.value<boost::endian::big_uint16_t>() };
        auto name { input.string(name_sz) };

        if (TYPES.contains(tag)) {
            result._values.emplace(name, TYPES.at(tag)(input));
        } else {
            input.except(fmt::format("Unknown tag {} for key {}", tag, name));
        }
    }
}

std::unordered_map<std::string, mc::nbt::any> const & mc::nbt::compound::values() const { return _values; }

void mc::nbt::compound::snbt(std::ostream & stream) const {
    stream << '{';

    array_stream out { stream };
    for (auto const & [key, value] : _values) {
        std::ostringstream s;
        s << key << ':';
        value->snbt(s);
        out << s.str();
    }

    stream << '}';
}
