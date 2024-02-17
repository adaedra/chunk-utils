add_library(mc STATIC
        array_stream.cc
        array_stream.hh
        include/mc/nbt/array.hh
        include/mc/nbt/base.hh
        include/mc/nbt/compound.hh
        include/mc/nbt/list.hh
        include/mc/nbt/primitive.hh
        include/mc/nbt/root.hh
        include/mc/nbt/string.hh
        input.hh
        input.cc
        nbt/array.cc
        nbt/base.cc
        nbt/compound.cc
        nbt/list.cc
        nbt/primitive.cc
        nbt/root.cc
        nbt/string.cc
)
set_property(TARGET mc PROPERTY CXX_STANDARD 20)
set_property(TARGET mc PROPERTY CXX_EXTENSIONS OFF)
target_include_directories(mc PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(mc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(mc Boost::boost Boost::iostreams ZLIB::ZLIB fmt::fmt)

add_subdirectory(tests)
