#include <fmt/format.h>
#include <fstream>

#include "mc/nbt/root.hh"
#include "params.hh"
#include "util/options.hh"

static class : public options<params> {
    void prepare() override {
        _hidden.add_options()("file", boost::program_options::value<std::string>(), "NBT file to read");
        _positional.add("file", 1);
    }

    bool extract(variables_map const & vm) override {
        if (!vm.contains("file")) {
            return false;
        }

        params.path = vm["file"].as<std::string>();
        return true;
    }
} OPTIONS;

int main(int argc, char const * const * argv) {
    if (!OPTIONS.parse(argc, argv)) {
        return 1;
    };

    std::ifstream file { OPTIONS->path };
    auto root { mc::nbt::root::parse(file) };

    std::cout << "// Root compound \"" << root.name() << "\"\n";
    root.data().snbt(std::cout);
}
