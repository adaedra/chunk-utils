#pragma once

#include <cstdint>
#include <ostream>
#include <unordered_map>

namespace mc {
    class input;

    namespace nbt {
        class base;
        using any = std::unique_ptr<base>;

        class base {
        public:
            base(base &&) noexcept;
            virtual ~base();

            [[nodiscard]] virtual any clone() const = 0;

            virtual void snbt(std::ostream &) const = 0;
            [[nodiscard]] std::string snbt() const;

        protected:
            base() = default;
            [[nodiscard]] virtual uint8_t tag() const = 0;

            static std::unordered_map<uint8_t, any (*)(input &)> const TYPES;
        };
    }
}
