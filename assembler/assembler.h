#pragma once
#include <cstdint>
#include <cstdlib>
#include <unordered_map>

#include "tools.h"

#define CALL(str)

class Assembler {
public:
    Assembler(const char* path) {
        asm_source_ = tools::cStyleLoadFileIntoMemory(path);
        assert(asm_source_ != nullptr && "asm_source_ is nullptr");
    }

    ~Assembler() {
        free(asm_source_);
    }

    void generateSymbolTable();

public:
	[[nodiscard]] constexpr inline auto& dataVarSymTable() noexcept { return data_var_sym_table_; }
	[[nodiscard]] constexpr inline auto& procSymTable() noexcept { return proc_sym_table_; }

private:
    void parseLabel(uint32_t &pos, uint32_t len);

    void nextLine(uint32_t& pos, uint32_t len);

	void parseVarBlock(uint32_t& pos, uint32_t len);

	inline void eatWhitespaces(uint32_t& pos, uint32_t len) {
		while (pos < len && isspace(asm_source_[pos])) {
			pos++;
		}
	}

	void expectSymbol(uint8_t symbol, uint32_t& pos, uint32_t len);


private:
    uint32_t pc_{0};
    std::unordered_map<std::string, uint32_t> proc_sym_table_;
    std::unordered_map<std::string, uint32_t> data_var_sym_table_;
    char* asm_source_;
};

