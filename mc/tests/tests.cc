#include <boost/test/included/unit_test.hpp>

using namespace boost::unit_test;

// array.test.cc
extern void decode_array();
extern void encode_array_snbt();

// list.test.cc
extern void decode_empty_list();
extern void reject_untyped_list_with_values();
extern void decode_short_list();
extern void encode_short_list_snbt();

// string.test.cc
extern void decode_string();

test_suite * init_unit_test_suite(int, char **) {
    framework::master_test_suite().add(BOOST_TEST_CASE(decode_string));
    framework::master_test_suite().add(BOOST_TEST_CASE(decode_array));
    framework::master_test_suite().add(BOOST_TEST_CASE(decode_empty_list));
    framework::master_test_suite().add(BOOST_TEST_CASE(reject_untyped_list_with_values));
    framework::master_test_suite().add(BOOST_TEST_CASE(decode_short_list));
    framework::master_test_suite().add(BOOST_TEST_CASE(encode_short_list_snbt));
    framework::master_test_suite().add(BOOST_TEST_CASE(encode_array_snbt));
    return nullptr;
}
