#include "mc/nbt/base.hh"

#include <sstream>

#include "mc/nbt/array.hh"
#include "mc/nbt/compound.hh"
#include "mc/nbt/list.hh"
#include "mc/nbt/primitive.hh"
#include "mc/nbt/string.hh"

mc::nbt::base::base(base &&) noexcept = default;

mc::nbt::base::~base() = default;

template <typename T> static mc::nbt::any parse(mc::input & stream) { return std::make_unique<T>(T::parse(stream)); }

static std::unique_ptr<mc::nbt::base> parse_list(mc::input & stream) { return mc::nbt::list_base::parse(stream); }

std::unordered_map<uint8_t, mc::nbt::any (*)(mc::input &)> const mc::nbt::base::TYPES {
    { compound::TAG, ::parse<compound> },
    { string::TAG, ::parse<string> },
    { primitive<int8_t>::TAG, ::parse<primitive<int8_t>> },
    { primitive<int16_t>::TAG, ::parse<primitive<int16_t>> },
    { primitive<int32_t>::TAG, ::parse<primitive<int32_t>> },
    { primitive<int64_t>::TAG, ::parse<primitive<int64_t>> },
    { primitive<float>::TAG, ::parse<primitive<float>> },
    { primitive<double>::TAG, ::parse<primitive<double>> },
    { list_base::TAG, ::parse_list },
    { array<int8_t>::TAG, ::parse<array<int8_t>> },
    { array<int32_t>::TAG, ::parse<array<int32_t>> },
    { array<int64_t>::TAG, ::parse<array<int64_t>> },
};

std::string mc::nbt::base::snbt() const {
    std::ostringstream out;
    snbt(out);
    return out.str();
}
