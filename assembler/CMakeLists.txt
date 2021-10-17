cmake_minimum_required(VERSION 3.12)
project(metacpu_asm)

set(CMAKE_CXX_STANDARD 17)

add_executable(metacpu_asm
        assembler.h
        assembler.cpp
        tokenizer.h
        tools.h
        token.h
        tokenizer.cpp
        main.cpp
)
