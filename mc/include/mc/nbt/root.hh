#pragma once

#include "mc/nbt/compound.hh"

namespace mc::nbt {
    class root {
    public:
        root(std::string && name, compound && data);
        static root parse(input &);
        static root parse(std::istream &);

        [[nodiscard]] std::string const & name() const;
        [[nodiscard]] compound const & data() const;

    private:
        std::string _name;
        compound _data;
    };
}
