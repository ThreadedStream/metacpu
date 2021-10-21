#pragma once


constexpr uint16_t instruction_mask = 0xF000;
constexpr uint16_t mode_mask = 0x0F00;
constexpr uint16_t value_mask = 0x00FF;

enum {
    ADDI = 0x0000,
    ADD = 0x1000,
    SUBI = 0x2000,
    SUB = 0x3000,
    CLAC = 0x4000,
    BNZ = 0x5000,
    BZ = 0x6000,
    UCB = 0x7000,
    STR = 0x8000,
    LEAVE = 0x9000,
	CMP  = 0xA000,
	CMPI = 0xB000,
	OUT  = 0xC000,
	BIG  = 0xD000,
	BIL  = 0xE000
};