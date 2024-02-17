#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/test/included/unit_test.hpp>
#include <sstream>

#include "input.hh"
#include "mc/nbt/string.hh"

using namespace boost::unit_test;

void decode_string() {
    char data[] = { 0, 5, 'h', 'e', 'l', 'l', 'o' };
    boost::iostreams::stream<boost::iostreams::array_source> in { data, 7 };
    mc::input input { in };

    auto res { mc::nbt::string::parse(input) };
    BOOST_CHECK_EQUAL("hello", res.data());
}

test_suite * init_unit_test_suite(int, char **) {
    framework::master_test_suite().add(BOOST_TEST_CASE(decode_string));
    return nullptr;
}
