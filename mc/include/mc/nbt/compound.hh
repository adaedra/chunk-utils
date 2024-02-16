#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>

#include "mc/nbt/base.hh"

namespace mc::nbt {
    class compound : public base {
    public:
        static uint8_t const TAG;
        [[nodiscard]] uint8_t tag() const override;

        static uint8_t const END;

        compound();
        static compound parse(input &);

        void snbt(std::ostream &) const override;

        [[nodiscard]] std::unordered_map<std::string, any> const & values() const;

    private:
        std::unordered_map<std::string, any> _values;
    };
}
