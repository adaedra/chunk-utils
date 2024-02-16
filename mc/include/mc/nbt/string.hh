#pragma once

#include <cstdint>

#include "mc/nbt/base.hh"

namespace mc::nbt {
    class string : public base {
    public:
        static uint8_t const TAG;
        [[nodiscard]] uint8_t tag() const override;

        explicit string(std::string &&);
        static string parse(input &);

        void snbt(std::ostream &) const override;

    private:
        std::string _s;
    };
}
