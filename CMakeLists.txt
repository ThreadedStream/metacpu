cmake_minimum_required(VERSION 3.12)

project(metacpu_vm)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(assembler)
add_subdirectory(interp/cpp)

if (BUILD_TESTS)
    add_subdirectory(tests)
endif()