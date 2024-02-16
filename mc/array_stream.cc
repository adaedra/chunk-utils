#include "array_stream.hh"

array_stream::array_stream(std::ostream & s) : _stream { s }, _first { true } {}

void array_stream::operator<<(std::string const & value) {
    if (!_first) {
        _stream << ',';
    }
    _stream << value;
    _first = false;
}
