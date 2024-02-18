#include <boost/test/included/unit_test.hpp>

using namespace boost::unit_test;

// array.test.cc
extern void decode_array();
extern void encode_array_snbt();

// string.test.cc
extern void decode_string();

test_suite * init_unit_test_suite(int, char **) {
    framework::master_test_suite().add(BOOST_TEST_CASE(decode_string));
    framework::master_test_suite().add(BOOST_TEST_CASE(decode_array));
    framework::master_test_suite().add(BOOST_TEST_CASE(encode_array_snbt));
    return nullptr;
}
