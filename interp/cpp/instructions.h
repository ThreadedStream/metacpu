#pragma once


constexpr uint16_t instruction_mask = 0xFF00;
constexpr uint16_t value_mask = 0x00FF;

enum {
    ADDI = 0x0000,
    ADD = 0x0100,
    SUBI = 0x0200,
    SUB = 0x0300,
    CLAC = 0x0400,
    BNZ = 0x0500,
    BZ = 0x0600,
    UCB = 0x0700,
    STR = 0x0800,
    LEAVE = 0x0900,
    CMP = 0x0A00,
    CMPI = 0x0B00,
    OUTD = 0x0C00,
    BIG = 0x0D00,
    BIL = 0x0E00,
    OUTB = 0x0F00,
    RET  = 0x1000,
};