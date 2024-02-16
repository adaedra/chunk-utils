#include "mc/nbt/list.hh"

#include <fmt/format.h>
#include <sstream>

#include "array_stream.hh"
#include "input.hh"
#include "mc/nbt/array.hh"
#include "mc/nbt/compound.hh"
#include "mc/nbt/primitive.hh"
#include "mc/nbt/string.hh"

uint8_t const mc::nbt::list_base::TAG { 9 };

uint8_t mc::nbt::list_base::tag() const { return TAG; }

template <typename T> static std::unique_ptr<mc::nbt::list_base> parse(mc::input & input) {
    return std::make_unique<mc::nbt::list<T>>(mc::nbt::list<T>::parse(input));
}

static std::unique_ptr<mc::nbt::list_base> parse_empty(mc::input & input) {
    return std::make_unique<mc::nbt::empty_list>(mc::nbt::empty_list::parse(input));
}

static std::unordered_map<uint8_t, std::unique_ptr<mc::nbt::list_base> (*)(mc::input &)> LIST_TYPES {
    { mc::nbt::compound::TAG, ::parse<mc::nbt::compound> },
    { mc::nbt::string::TAG, ::parse<mc::nbt::string> },
    { mc::nbt::primitive<int8_t>::TAG, ::parse<mc::nbt::primitive<int8_t>> },
    { mc::nbt::primitive<int16_t>::TAG, ::parse<mc::nbt::primitive<int16_t>> },
    { mc::nbt::primitive<int32_t>::TAG, ::parse<mc::nbt::primitive<int32_t>> },
    { mc::nbt::primitive<int64_t>::TAG, ::parse<mc::nbt::primitive<int64_t>> },
    { mc::nbt::primitive<float>::TAG, ::parse<mc::nbt::primitive<float>> },
    { mc::nbt::primitive<double>::TAG, ::parse<mc::nbt::primitive<double>> },
    { mc::nbt::list_base::TAG, ::parse<std::unique_ptr<mc::nbt::list_base>> },
    { mc::nbt::array<int8_t>::TAG, ::parse<mc::nbt::array<int8_t>> },
    { mc::nbt::array<int32_t>::TAG, ::parse<mc::nbt::array<int32_t>> },
    { mc::nbt::array<int64_t>::TAG, ::parse<mc::nbt::array<int64_t>> },
    { 0, ::parse_empty },
};

std::unique_ptr<mc::nbt::list_base> mc::nbt::list_base::parse(input & input) {
    auto tag { input.value<uint8_t>(UINT8_MAX) };

    if (!LIST_TYPES.contains(tag)) {
        input.except(fmt::format("Invalid tag {} for list", tag));
    }

    return LIST_TYPES.at(tag)(input);
}

template <typename T> mc::nbt::list<T>::list() = default;

template <typename T> mc::nbt::list<T> mc::nbt::list<T>::parse(input & input) {
    list<T> result;

    auto sz { input.value<boost::endian::big_uint32_t>() };
    result._v.reserve(sz);

    for (uintptr_t idx { 0 }; idx < sz; ++idx) {
        result._v.push_back(read_one(input));
    }

    return result;
}

template <typename T> T mc::nbt::list<T>::read_one(input & input) { return T::parse(input); }

template <>
std::unique_ptr<mc::nbt::list_base> mc::nbt::list<std::unique_ptr<mc::nbt::list_base>>::read_one(input & input) {
    return list_base::parse(input);
}

template <typename T> void mc::nbt::list<T>::snbt(std::ostream & stream) const {
    stream << '[';

    array_stream out { stream };
    for (auto const & it : _v) {
        out << static_cast<base const &>(it).snbt();
    }

    stream << ']';
}

template <> void mc::nbt::list<std::unique_ptr<mc::nbt::list_base>>::snbt(std::ostream & stream) const {
    stream << '[';

    array_stream out { stream };
    for (auto const & it : _v) {
        out << it->snbt();
    }

    stream << ']';
}

mc::nbt::empty_list::empty_list() = default;

mc::nbt::empty_list mc::nbt::empty_list::parse(input & input) {
    auto sz { input.value<boost::endian::big_uint32_t>() };

    if (sz != 0) {
        input.except("untyped list with elements");
    }

    return {};
}

void mc::nbt::empty_list::snbt(std::ostream & stream) const { stream << "[]"; }
