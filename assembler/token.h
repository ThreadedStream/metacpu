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
        {"addi",  InstructionMode::IMMEDIATE},
        {"subi",  InstructionMode::IMMEDIATE},
        {"add",   InstructionMode::MEMORY},
        {"sub",   InstructionMode::MEMORY},
        {"clac",  InstructionMode::NONE},
        {"str",   InstructionMode::MEMORY},
        {"bz",    InstructionMode::MEMORY},
        {"bnz",   InstructionMode::MEMORY},
        {"ucb",   InstructionMode::MEMORY},
        {"leave", InstructionMode::NONE},
        {"cmpi",  InstructionMode::IMMEDIATE},
        {"cmp",   InstructionMode::MEMORY},
        {"outd",  InstructionMode::NONE},
        {"big",   InstructionMode::MEMORY},
        {"bil",   InstructionMode::MEMORY},
        {"outb",  InstructionMode::NONE},
        {"ret", InstructionMode::NONE},
		{"submem", InstructionMode::MEMORY},
		{"addmem", InstructionMode::MEMORY}
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
