#pragma once

#include <vector>
#include <string>
#include <unordered_map>


// Available memory bank: 256 16-bit entries 

// TODO(threadedstream): needs to be changed to something less painful to query
static std::unordered_map<std::string, bool> instructions = {
	{"addi", true}, // add immediate
	{"subi", true}, // sub immediate
	{"add", true}, // access memory, add contents
	{"sub", true}, // access memory, sub contents
	{"clac", true}, // clear acc
	{"str", true}, // store into memory
	{"bz", true}, // branch if zero
	{"bnz", true}, // branch if not zero
	{"ucb", true}, // unconditional branch
	{"leave", true}, // stop execution of a program
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
