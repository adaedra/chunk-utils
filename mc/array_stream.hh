#pragma once

#include <ostream>

class array_stream {
public:
    explicit array_stream(std::ostream &);

    void operator<<(std::string const &);

private:
    std::ostream & _stream;
    bool _first;
};
