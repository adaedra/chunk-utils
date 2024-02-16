#include "input.hh"

#include <fmt/format.h>

mc::input::input(std::istream & stream) : _stream { stream }, _read { 0 } {}

std::string mc::input::string(std::streamsize sz) {
    std::string ret(sz, 0);

    _stream.read(ret.data(), sz);
    _read += _stream.gcount();

    return ret;
}

void mc::input::except(const char * what) { throw std::runtime_error(fmt::format("(byte {:04x}) {}", _read, what)); }

void mc::input::except(std::string const & what) { except(what.c_str()); }

void mc::input::report_gcount(std::size_t expected) {
    if (static_cast<std::size_t>(_stream.gcount()) < expected) {
        except(fmt::format("read {} bytes out of {}", _stream.gcount(), expected));
    }

#ifdef MC_DEBUG
    std::cerr << fmt::format("** at {:06x}, read {} bytes", _read, expected) << std::endl;
#endif
    _read += _stream.gcount();
}

void mc::input::ensure_end() {
    _stream.peek();
    if (_stream.gcount() > 0) {
        except("Extra data at end of file");
    }
}
