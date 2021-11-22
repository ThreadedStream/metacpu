cmake_minimum_required(VERSION 3.12)
project(metacpu_asm)

set(CMAKE_CXX_STANDARD 17)

set(HEADER_FILES assembler.h tools.h token.h ../common/bin_tree.h)
set(SOURCES assembler.cpp main.cpp)

add_executable(metacpu_asm ${HEADER_FILES} ${SOURCES})

target_include_directories(metacpu_asm PUBLIC ${CMAKE_SOURCE_DIR}/common)
