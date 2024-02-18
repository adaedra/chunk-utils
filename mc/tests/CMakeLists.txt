add_executable(mc_tests
        tests.cc
        ../nbt/array.test.cc
        ../nbt/string.test.cc
)
set_property(TARGET mc_tests PROPERTY CXX_STANDARD 20)
set_property(TARGET mc_tests PROPERTY CXX_EXTENSIONS OFF)
target_link_libraries(mc_tests mc)
target_include_directories(mc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
add_test(NAME mc_tests COMMAND mc_tests)
