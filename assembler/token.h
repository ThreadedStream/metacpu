#pragma once

#include <vector>
#include <string>


std::vector <std::string> reserved_tokens = {
        "addi",
        "subi",
        "add",
        "sub",
        "clac",
        "var",
        "str",
        "BEGINDATA",
        "ENDATA",
};

enum class TokenType : unsigned {
    LABEL,
    OPCODE,
    NUMBER,
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
