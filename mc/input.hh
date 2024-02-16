#pragma once

#include <iostream>
#include <optional>

namespace mc {
    class input {
    public:
        explicit input(std::istream & stream);

        template <typename T> T value(T def = T {}) {
            _stream.read(reinterpret_cast<char *>(&def), sizeof(T));
            report_gcount(sizeof(T));
            return def;
        }

        template <typename T> std::optional<T> maybe(T def = T {}) {
            _stream.read(reinterpret_cast<char *>(&def), sizeof(T));

            if (_stream.gcount() == 0) {
                return std::nullopt;
            }

            report_gcount(sizeof(T));
            return def;
        }

        std::string string(std::streamsize sz);
        [[noreturn]] void except(char const * what);
        [[noreturn]] void except(std::string const & what);

        void ensure_end();

    private:
        std::istream & _stream;
        std::streamsize _read;

        void report_gcount(std::size_t expected);
    };
}
