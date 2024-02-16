#include "mc/nbt/primitive.hh"

#include "input.hh"

template <typename T> mc::nbt::primitive<T>::primitive(T const & v) : _v { v } {}

template <typename T> mc::nbt::primitive<T> mc::nbt::primitive<T>::parse(input & input) {
    auto v { input.value<item_t>() };
    return primitive(v);
}

template class mc::nbt::primitive<int8_t>;
template <> uint8_t const mc::nbt::primitive<int8_t>::TAG { 1 };
template <> void mc::nbt::primitive<int8_t>::snbt(std::ostream & stream) const {
    stream << static_cast<int16_t>(_v) << 'b';
}

template class mc::nbt::primitive<int16_t>;
template <> uint8_t const mc::nbt::primitive<int16_t>::TAG { 2 };
template <> void mc::nbt::primitive<int16_t>::snbt(std::ostream & stream) const { stream << _v << 's'; }

template class mc::nbt::primitive<int32_t>;
template <> uint8_t const mc::nbt::primitive<int32_t>::TAG { 3 };
template <> void mc::nbt::primitive<int32_t>::snbt(std::ostream & stream) const { stream << _v; }

template class mc::nbt::primitive<int64_t>;
template <> uint8_t const mc::nbt::primitive<int64_t>::TAG { 4 };
template <> void mc::nbt::primitive<int64_t>::snbt(std::ostream & stream) const { stream << _v << 'l'; }

template class mc::nbt::primitive<float>;
template <> uint8_t const mc::nbt::primitive<float>::TAG { 5 };
template <> void mc::nbt::primitive<float>::snbt(std::ostream & stream) const { stream << _v << 'f'; }

template class mc::nbt::primitive<double>;
template <> uint8_t const mc::nbt::primitive<double>::TAG { 6 };
template <> void mc::nbt::primitive<double>::snbt(std::ostream & stream) const { stream << _v; }

template <typename T> uint8_t mc::nbt::primitive<T>::tag() const { return TAG; }
