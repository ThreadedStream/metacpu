cmake_minimum_required(VERSION 3.12)

project(metacpu_vm)

set(CMAKE_CXX_STANDARD 17)


set(SOURCES main.cpp vm.cpp )
set (HEADERS vm.h instructions.h)

add_executable(metacpu_vm ${HEADERS} ${SOURCES})
