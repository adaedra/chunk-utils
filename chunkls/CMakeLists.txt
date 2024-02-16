add_executable(chunkls
        chunkls.cc
        params.hh
)
set_property(TARGET chunkls PROPERTY CXX_STANDARD 20)
set_property(TARGET chunkls PROPERTY CXX_EXTENSIONS OFF)
target_link_libraries(chunkls util mc)
