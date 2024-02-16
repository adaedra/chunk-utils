#pragma once

#include <cstdint>
#include <ostream>
#include <unordered_map>

namespace mc {
    class input;

    namespace nbt {
        class base {
        public:
            base(base &&) noexcept;
            virtual ~base();

            virtual void snbt(std::ostream &) const = 0;
            [[nodiscard]] std::string snbt() const;

        protected:
            base() = default;
            [[nodiscard]] virtual uint8_t tag() const = 0;

            static std::unordered_map<uint8_t, std::unique_ptr<base> (*)(input &)> const TYPES;
        };

        using any = std::unique_ptr<base>;
    }
}