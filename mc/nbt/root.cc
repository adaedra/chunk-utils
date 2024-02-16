#include "mc/nbt/root.hh"

#include <boost/endian.hpp>
#include <fmt/format.h>

#include "input.hh"
#include "mc/nbt/compound.hh"

mc::nbt::root::root(std::string && name, compound && data) : _name { std::move(name) }, _data { std::move(data) } {}

mc::nbt::root mc::nbt::root::parse(input & input) {
    auto tag { input.value<uint8_t>(UINT8_MAX) };
    if (tag != compound::TAG) {
        input.except(fmt::format("expected root compound tag ({}), got {}", compound::TAG, tag));
    }

    auto name_sz { input.value<boost::endian::big_uint16_t>() };
    auto name { input.string(name_sz) };

    compound children { compound::parse(input) };
    input.ensure_end();
    return { std::move(name), std::move(children) };
}

mc::nbt::root mc::nbt::root::parse(std::istream & s) {
    input in { s };
    return parse(in);
}

std::string const & mc::nbt::root::name() const { return _name; }

mc::nbt::compound const & mc::nbt::root::data() const { return _data; }
