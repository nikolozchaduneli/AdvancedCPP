cmake_minimum_required(VERSION 3.14)
project(cppa_project CXX)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_MODULE_PATH})

find_package(asmjit REQUIRED)

add_compile_options(-W -Wall -Werror -std=c++2a)


## MAIN library
add_library(cppa src/image.cpp src/dilate.cpp)

target_include_directories(cppa PUBLIC ${CMAKE_SOURCE_DIR}/include)


## TEST
add_subdirectory(tests)
add_subdirectory(benchs)
