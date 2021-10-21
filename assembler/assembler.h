#pragma once

#include <cstdint>
#include <cstdlib>
#include <unordered_map>

#include "tools.h"

constexpr uint8_t address_space_size = 0xFF;

class Assembler {
public:
    explicit Assembler(const char *path) {
        asm_source_ = tools::cStyleLoadFileIntoMemory(path);
        assert(asm_source_ != nullptr && "asm_source_ is nullptr");
		address_space_.resize(address_space_size);
		data_section_ptr = 0xF0;
    }

    ~Assembler() {
        cleanup();
    }


    void generateSymbolTable();

    void assemble();

public:
    [[nodiscard]] constexpr inline auto &dataVarSymTable() noexcept { return data_var_sym_table_; }

    [[nodiscard]] constexpr inline auto &procSymTable() noexcept { return proc_sym_table_; }

private:
    std::string getLabelName(uint32_t &pos, uint32_t len);

//    void parseLabel(uint32_t &pos, uint32_t len);

    void nextLine(uint32_t &pos, uint32_t len);

    void parseVarBlock(uint32_t &pos, uint32_t len);

    uint32_t lookupLabel(const std::string &name);

    uint32_t lookupVar(const std::string &name);

    uint32_t fetchImmediateOperand(uint32_t &pos, uint32_t len);

    uint32_t fetchMemoryOperand(uint32_t &pos, uint32_t len);

    inline void cleanup() {
        free(asm_source_);
    }


    inline void eatWhitespaces(uint32_t &pos, uint32_t len) {
        while (pos < len && isspace(asm_source_[pos])) {
            pos++;
        }
    }

    void expectSymbol(uint8_t symbol, uint32_t &pos, uint32_t len);

private:
	uint8_t data_section_ptr;
	std::vector<uint16_t> address_space_;
	std::unordered_map<std::string, uint32_t> proc_sym_table_;
    std::unordered_map<std::string, uint32_t> data_var_sym_table_;
    char *asm_source_;
};

