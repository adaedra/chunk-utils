#pragma once

#include <boost/endian.hpp>
#include <span>
#include <vector>

#include "mc/nbt/base.hh"

namespace mc::nbt {
    template <typename T> class array : public base {
    public:
        using item_t = boost::endian::endian_arithmetic<boost::endian::order::big, T, sizeof(T) * 8>;

        array();
        explicit array(std::span<T> const &);
        array(array const &);
        array(array &&) noexcept;
        [[nodiscard]] any clone() const override;

        static array parse(input &);

        static uint8_t const TAG;
        [[nodiscard]] uint8_t tag() const override;

        void snbt(std::ostream &) const override;

        [[nodiscard]] std::vector<item_t> const & data() const;

    private:
        std::vector<item_t> _v;

        static char const SNBT_TAG;
    };
}
