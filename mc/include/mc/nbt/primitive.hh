#pragma once

#include <boost/endian.hpp>

#include "mc/nbt/base.hh"

namespace mc::nbt {
    template <typename T> class primitive : public base {
    public:
        explicit primitive(T const & t);
        static primitive parse(input &);

        static uint8_t const TAG;
        [[nodiscard]] uint8_t tag() const override;

        void snbt(std::ostream &) const override;

    private:
        using item_t = boost::endian::endian_arithmetic<boost::endian::order::big, T, sizeof(T) * 8>;
        item_t _v;
    };
}
