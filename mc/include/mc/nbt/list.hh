#pragma once

#include "mc/nbt/base.hh"

#include <span>
#include <vector>

namespace mc::nbt {
    class list_base : public base {
    public:
        ~list_base() override;

        static uint8_t const TAG;
        [[nodiscard]] uint8_t tag() const override;

        static std::unique_ptr<list_base> parse(input &);

        [[nodiscard]] virtual std::unique_ptr<list_base> clone_list() = 0;
    };

    template <typename T> class list : public list_base {
    public:
        list();
        explicit list(std::span<T> const &);
        list(list const &);
        list(list &&) noexcept;
        ~list() override;
        [[nodiscard]] any clone() const override;
        [[nodiscard]] std::unique_ptr<list_base> clone_list() override;

        static list parse(input &);

        void snbt(std::ostream &) const override;

        static uint8_t const LIST_TAG;

        [[nodiscard]] std::vector<T> const & data() const;

    private:
        static T read_one(input &);

        std::vector<T> _v;
    };

    class empty_list : public list_base {
    public:
        empty_list();
        empty_list(empty_list const &);
        empty_list(empty_list &&) noexcept;
        ~empty_list() override;
        [[nodiscard]] any clone() const override;
        [[nodiscard]] std::unique_ptr<list_base> clone_list() override;

        static empty_list parse(input &);

        void snbt(std::ostream &) const override;
    };
}
