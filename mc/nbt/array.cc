#include "mc/nbt/array.hh"
#include "input.hh"

#include <algorithm>

template <typename T> mc::nbt::array<T>::array() = default;

template <typename T> uint8_t mc::nbt::array<T>::tag() const { return TAG; }

template <typename T> mc::nbt::array<T> mc::nbt::array<T>::parse(input & input) {
    boost::endian::big_uint32_t sz { input.value<boost::endian::big_uint32_t>() };

    array result;
    result._v.reserve(sz);

    for (std::size_t it { 0 }; it < sz; ++it) {
        result._v.push_back(input.value<item_t>());
    }

    return result;
}

template <typename T> void mc::nbt::array<T>::snbt(std::ostream & stream) const {
    stream << '[' << SNBT_TAG << ';';
    std::ostream_iterator<char> out(stream, ",");
    std::ranges::copy(_v, out);
    stream << ']';
}

template <> uint8_t const mc::nbt::array<int8_t>::TAG { 7 };
template <> char const mc::nbt::array<int8_t>::SNBT_TAG { 'B' };
template class mc::nbt::array<int8_t>;
template <> uint8_t const mc::nbt::array<int32_t>::TAG { 11 };
template <> char const mc::nbt::array<int32_t>::SNBT_TAG { 'I' };
template class mc::nbt::array<int32_t>;
template <> uint8_t const mc::nbt::array<int64_t>::TAG { 12 };
template <> char const mc::nbt::array<int64_t>::SNBT_TAG { 'L' };
template class mc::nbt::array<int64_t>;
