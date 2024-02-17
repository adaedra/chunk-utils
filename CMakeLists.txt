cmake_minimum_required(VERSION 3.20)
project(chunk-utils)

find_package(Boost REQUIRED COMPONENTS iostreams program_options)
find_package(ZLIB REQUIRED)
find_package(fmt CONFIG REQUIRED)

enable_testing()

add_subdirectory(chunkls)
add_subdirectory(nbtdump)
add_subdirectory(util)
add_subdirectory(mc)
