#pragma once

#include <string>
#include <unordered_map>
#include <cstdint>

// addi - 0x0 (add immediate)
// add  - 0x1 (add value the address points to)
// subi - 0x2 (sub immediate)
// sub  - 0x3 (sub value the address points to)
// clac - 0x4 (clear acc)
// bnz  - 0x5 (branch-if-not-zero)
// bz   - 0x6 (branch-if-zero)
// ucb  - 0x7 (unconditional-branch)
// str  - 0x8 (store value of acc into address)
// leave - 0x9 (terminate the execution of a program)
// cmp - 0xA (compare value with acc)
// out - 0xB (output to console the value that the input address points to)
// big - 0xC (branch-if-greater)
// bil - 0xD (branch-if-less)

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
        {"leave", 0x9},
		{"cmp", 0xA},
		{"out", 0xB},
		{"big", 0xC},
		{"bil", 0xD}
};


static inline uint16_t assembleInstruction(const std::string &instruction, const uint16_t mode, const uint8_t value) {
    const uint16_t opcode = (opcodes[instruction]) << 12;

    return opcode | mode << 8 | value;
}