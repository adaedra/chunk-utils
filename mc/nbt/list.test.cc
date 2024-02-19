#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/test/unit_test.hpp>

#include "input.hh"
#include "mc/nbt/list.hh"
#include "mc/nbt/primitive.hh"

void decode_empty_list() {
    char data[] = {0, 0, 0, 0, 0};
    boost::iostreams::stream<boost::iostreams::array_source> in {data, sizeof(data)};
    mc::input input {in};

    auto res {mc::nbt::list_base::parse(input)};
    BOOST_CHECK_NE(dynamic_cast<mc::nbt::empty_list *>(res.get()), nullptr);
}

void reject_untyped_list_with_values() {
    char data[] = {0, 0, 0, 0, 1, -1};
    boost::iostreams::stream<boost::iostreams::array_source> in {data, sizeof(data)};
    mc::input input {in};

    BOOST_CHECK_EXCEPTION(mc::nbt::list_base::parse(input), std::runtime_error, [](std::runtime_error const & ex) {
        return std::string(ex.what()) == "(byte 0005) untyped list with elements";
    });
}

void decode_short_list() {
    char data[] = {2, 0, 0, 0, 3, 0, 1, 0, 2, 0, 3};
    boost::iostreams::stream<boost::iostreams::array_source> in {data, sizeof(data)};
    mc::input input {in};

    auto res {mc::nbt::list_base::parse(input)};
    auto list {dynamic_cast<mc::nbt::list<mc::nbt::primitive<int16_t>> *>(res.get())};
    BOOST_CHECK_NE(list, nullptr);

    BOOST_CHECK_EQUAL(list->data().size(), 3);
    BOOST_CHECK_EQUAL(list->data().at(0).value(), 1);
    BOOST_CHECK_EQUAL(list->data().at(1).value(), 2);
    BOOST_CHECK_EQUAL(list->data().at(2).value(), 3);
}

void encode_short_list_snbt() {
    mc::nbt::primitive<int16_t> data[] = {
        mc::nbt::primitive<int16_t>(1), mc::nbt::primitive<int16_t>(2), mc::nbt::primitive<int16_t>(3)
    };
    auto list {mc::nbt::list<mc::nbt::primitive<int16_t>>(data)};

    BOOST_CHECK_EQUAL(static_cast<mc::nbt::base &>(list).snbt(), "[1s,2s,3s]");
}
