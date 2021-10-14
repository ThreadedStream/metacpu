#pragma once
#include <cstdint>
#include <unordered_map>

#include "tools.h"

#define CALL(str)

class Assembler {
    Assembler(const char* path) {
        asm_source_ = tools::loadFileIntoMemory(path);
    }


    void generateSymbolTable();

private:
    void parseLabel(uint32_t &pos, uint32_t len);

private:
    uint32_t lc_{0};
    std::unordered_map<const char*, uint32_t> proc_sym_table_;
    std::unordered_map<const char*, uint32_t> data_var_sym_table_;
    const char* asm_source_;
};

