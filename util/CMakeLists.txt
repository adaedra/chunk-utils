add_library(util INTERFACE
        util/options.hh
)

set_property(TARGET util PROPERTY CXX_STANDARD 20)
set_property(TARGET util PROPERTY CXX_EXTENSIONS OFF)
target_include_directories(util INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(util INTERFACE Boost::program_options)
