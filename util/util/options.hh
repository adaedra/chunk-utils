#pragma once

#include <boost/program_options.hpp>
#include <iostream>

template <typename P> class options {
public:
    virtual ~options() = default;

    bool parse(int argc, char const * const * argv) {
        using namespace boost::program_options;

        prepare();
        _all.add(_options).add(_hidden);

        variables_map vm;
        try {
            store(command_line_parser(argc, argv).options(_all).positional(_positional).run(), vm);
            notify(vm);
        } catch (std::exception const & ex) {
            std::cerr << ex.what() << std::endl;
            std::cout << '\n' << _options;
            return false;
        }

        if (vm.contains("help") || !extract(vm)) {
            std::cout << _options;
            return false;
        }

        return true;
    }

    P params;
    P const & operator*() { return params; }
    P const * operator->() { return &params; }

protected:
    options() : _options { "Options" } { _options.add_options()("help", "shows this help"); }

    using variables_map = boost::program_options::variables_map;
    using options_description = boost::program_options::options_description;
    using positional_options_description = boost::program_options::positional_options_description;

    virtual void prepare() = 0;
    virtual bool extract(variables_map const &) = 0;

    options_description _options;
    options_description _hidden;
    options_description _all;
    positional_options_description _positional;
};
