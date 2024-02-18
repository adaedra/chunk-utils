#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/test/unit_test.hpp>

#include "input.hh"
#include "mc/nbt/array.hh"

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

    BOOST_CHECK_EQUAL("[I;1,2,3]", static_cast<mc::nbt::base &>(array).snbt());
}
