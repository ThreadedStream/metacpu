#pragma once
#include <cstdint>
#include <memory>

enum class TokenType : unsigned {
    LABEL,
    OPCODE,
    NUMBER,
};

struct Token {
    TokenType type;
    const char *name;
    union{
        Token* operand;
        const char* value_str;
        int16_t value_int;
    };
};

