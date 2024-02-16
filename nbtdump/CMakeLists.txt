add_executable(nbtdump
        params.hh
        nbtdump.cc
)
set_property(TARGET nbtdump PROPERTY CXX_STANDARD 20)
set_property(TARGET nbtdump PROPERTY CXX_EXTENSIONS OFF)
target_link_libraries(nbtdump util mc)
