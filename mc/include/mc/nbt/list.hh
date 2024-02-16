#pragma once

#include "mc/nbt/base.hh"

#include <vector>

namespace mc::nbt {
    class list_base : public base {
    public:
        static uint8_t const TAG;
        [[nodiscard]] uint8_t tag() const override;

        static std::unique_ptr<list_base> parse(input &);
    };

    template <typename T> class list : public list_base {
    public:
        list();
        static list parse(input &);

        void snbt(std::ostream &) const override;

        static uint8_t const LIST_TAG;

    private:
        static T read_one(input &);

        std::vector<T> _v;
    };

    class empty_list : public list_base {
    public:
        empty_list();
        static empty_list parse(input &);

        void snbt(std::ostream &) const override;
    };
}
