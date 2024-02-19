#pragma once

#include <cstdint>

#include "mc/nbt/base.hh"

namespace mc::nbt {
    class string : public base {
    public:
        static uint8_t const TAG;
        [[nodiscard]] uint8_t tag() const override;

        explicit string(std::string &&);
        string(string const &);
        [[nodiscard]] any clone() const override;

        static string parse(input &);

        void snbt(std::ostream &) const override;

        [[nodiscard]] std::string const & data() const;

    private:
        std::string _s;
    };
}
