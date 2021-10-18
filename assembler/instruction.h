#pragma once

#include <string>
#include <unordered_map>
#include <cstdint>

// addi - 0x1
// add  - 0x2
// subi - 0x3
// sub  - 0x4
// clac - 0x5
// bnz  - 0x6
// bz   - 0x7
// ucb  - 0x8
// str  - 0x9
// leave - 0xA

static std::unordered_map<std::string, uint8_t> opcodes = {
	{"addi", 0x1},
	{"add",	 0x2},
	{"subi", 0x3},
	{"sub",  0x4},
	{"clac", 0x5},
	{"bnz",  0x6},
	{"bz",   0x7},
	{"ucb",  0x8},
	{"str",  0x9},
	{"leave", 0xA}
};


static inline std::string assembleInstruction(const std::string& instruction, const uint16_t mode, const uint8_t value) {
	const uint16_t opcode = (opcodes[instruction]) << 12;

	return std::to_string(opcode | mode << 8 | value);
}