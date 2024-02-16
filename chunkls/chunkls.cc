#include <boost/core/span.hpp>
#include <boost/endian.hpp>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/device/mapped_file.hpp>
#include <boost/iostreams/filter/zlib.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/range/adaptor/indexed.hpp>
#include <fmt/format.h>
#include <iostream>

#include "mc/nbt/root.hh"
#include "params.hh"
#include "util/options.hh"

static class : public options<params> {
    void prepare() override {
        _hidden.add_options()("region", boost::program_options::value<std::string>(), "region file to read");
        _positional.add("region", 1);
    }

    bool extract(variables_map const & vm) override {
        if (!vm.contains("region")) {
            return false;
        }

        params.path = vm["region"].as<std::string>();
        return true;
    }
} OPTIONS;

int main(int argc, char const * const * argv) {
    if (!OPTIONS.parse(argc, argv)) {
        return 1;
    };

    boost::iostreams::mapped_file file { OPTIONS->path, std::ios::in };
    boost::span const offsets { reinterpret_cast<boost::endian::big_uint32_t const *>(file.const_data()), 1024 };

    for (auto const & it : offsets | boost::adaptors::indexed(0)) {
        auto idx { it.index() };

        std::cout << fmt::format("Chunk {:4} ({:2}, {:2}): ", idx, idx % 32, idx / 32);
        if (it.value() == 0) {
            std::cout << "Not allocated";
        } else {
            auto size { it.value() & 0xFF };
            auto offset { it.value() >> 8 };

            std::cout << fmt::format(
                "Offset {:08x}, Size {}", offset * sizeof(uint32_t) * 1024, size * sizeof(uint32_t) * 1024
            );

            if (size == 0 || offset == 0) {
                std::cout << fmt::format(" ** invalid {} = 0", size == 0 ? "size" : "offset") << std::endl;
                continue;
            }

            if (offset * sizeof(uint32_t) * 1024 + size * sizeof(uint32_t) * 1024 > file.size()) {
                std::cout << " ** chunk out of file bounds" << std::endl;
                continue;
            }

            boost::endian::big_uint32_t const * actual_size {
                reinterpret_cast<boost::endian::big_uint32_t const *>(file.const_data()) + (offset * 1024)
            };
            uint8_t const * compression { reinterpret_cast<uint8_t const *>(actual_size + 1) };

            std::cout << fmt::format("\n\tActual size: {}, Compression: {}", *actual_size - 1, *compression);

            boost::iostreams::filtering_stream<boost::iostreams::input> chunk_data;
            chunk_data.push(boost::iostreams::zlib_decompressor());
            chunk_data.push(
                boost::iostreams::array_source(reinterpret_cast<char const *>(compression + 1), *actual_size - 1)
            );

            try {
                auto root { mc::nbt::root::parse(chunk_data) };

                std::cout << fmt::format(
                    "\n\tRoot compound \"{}\" has {} entries", root.name(), root.data().values().size()
                );
            } catch (std::exception const & e) {
                std::cout << " ** errored: " << e.what();
            }
        }

        std::cout << std::endl;
    }

    return 0;
}
