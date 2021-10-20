#pragma once

#include <string>
#include <unordered_map>
#include <cstdint>

// addi - 0x0
// add  - 0x1
// subi - 0x2
// sub  - 0x3
// clac - 0x4
// bnz  - 0x5
// bz   - 0x6
// ucb  - 0x7
// str  - 0x8
// leave - 0x9

static std::unordered_map<std::string, uint8_t> opcodes = {
        {"addi",  0x0},
        {"add",   0x1},
        {"subi",  0x2},
        {"sub",   0x3},
        {"clac",  0x4},
        {"bnz",   0x5},
        {"bz",    0x6},
        {"ucb",   0x7},
        {"str",   0x8},
        {"leave", 0x9}
};


static inline uint16_t assembleInstruction(const std::string &instruction, const uint16_t mode, const uint8_t value) {
    const uint16_t opcode = (opcodes[instruction]) << 12;

    return opcode | mode << 8 | value;
}