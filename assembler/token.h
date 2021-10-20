#pragma once

#include <vector>
#include <string>
#include <unordered_map>


enum class InstructionMode : unsigned {
    NONE = 0x0,
    IMMEDIATE = 0x1,
    MEMORY = 0x2
};

// Available memory bank: 256 16-bit entries 

// TODO(threadedstream): needs to be changed to something less painful to query
static std::unordered_map<std::string, InstructionMode> instructions = {
        {"addi",  InstructionMode::IMMEDIATE}, // add immediate
        {"subi",  InstructionMode::IMMEDIATE}, // sub immediate
        {"add",   InstructionMode::MEMORY}, // access memory, add contents
        {"sub",   InstructionMode::MEMORY}, // access memory, sub contents
        {"clac",  InstructionMode::NONE}, // clear acc
        {"str",   InstructionMode::MEMORY}, // store into memory
        {"bz",    InstructionMode::MEMORY}, // branch if zero
        {"bnz",   InstructionMode::MEMORY}, // branch if not zero
        {"ucb",   InstructionMode::MEMORY}, // unconditional branch
        {"leave", InstructionMode::NONE}, // stop execution of a program
};

enum class TokenType : unsigned {
    INSTRUCTION,
    NUMBER,
    LABEL,
};


struct Token {
    TokenType type;
    const char *name;
    union {
        Token *operand;
        const char *value_str;
        int16_t value_int;
    };
};
