#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/test/unit_test.hpp>

#include "input.hh"
#include "mc/nbt/string.hh"

void decode_string() {
    char data[] = { 0, 5, 'h', 'e', 'l', 'l', 'o' };
    boost::iostreams::stream<boost::iostreams::array_source> in { data, 7 };
    mc::input input { in };

    auto res { mc::nbt::string::parse(input) };
    BOOST_CHECK_EQUAL("hello", res.data());
}
