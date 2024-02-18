#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/test/included/unit_test.hpp>
#include <sstream>

#include "input.hh"
#include "mc/nbt/array.hh"
#include "mc/nbt/string.hh"

using namespace boost::unit_test;

void decode_string() {
    char data[] = { 0, 5, 'h', 'e', 'l', 'l', 'o' };
    boost::iostreams::stream<boost::iostreams::array_source> in { data, 7 };
    mc::input input { in };

    auto res { mc::nbt::string::parse(input) };
    BOOST_CHECK_EQUAL("hello", res.data());
}

void decode_array() {
    char data[] = { 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 2 };
    boost::iostreams::stream<boost::iostreams::array_source> in { data, 12 };
    mc::input input { in };

    auto res { mc::nbt::array<int32_t>::parse(input) };
    BOOST_CHECK_EQUAL(2, res.data().size());
    BOOST_CHECK_EQUAL(1, res.data().at(0));
    BOOST_CHECK_EQUAL(2, res.data().at(1));
}

void encode_array_snbt() {
    int32_t data[] = { 1, 2, 3 };
    auto array { mc::nbt::array<int32_t>(data) };

    std::stringstream res;
    array.snbt(res);
    BOOST_CHECK_EQUAL("[I;1,2,3]", res.str());
}

test_suite * init_unit_test_suite(int, char **) {
    framework::master_test_suite().add(BOOST_TEST_CASE(decode_string));
    framework::master_test_suite().add(BOOST_TEST_CASE(decode_array));
    framework::master_test_suite().add(BOOST_TEST_CASE(encode_array_snbt));
    return nullptr;
}
