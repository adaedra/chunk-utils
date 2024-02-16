#pragma once

#include <boost/endian.hpp>
#include <vector>

#include "mc/nbt/base.hh"

namespace mc::nbt {
    template <typename T> class array : public base {
    public:
        array();
        static array parse(input &);

        static uint8_t const TAG;
        [[nodiscard]] uint8_t tag() const override;

        void snbt(std::ostream &) const override;

    private:
        using item_t = boost::endian::endian_arithmetic<boost::endian::order::big, T, sizeof(T) * 8>;
        std::vector<item_t> _v;

        static char const SNBT_TAG;
    };
}
