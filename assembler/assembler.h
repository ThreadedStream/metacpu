#pragma once

#include <cstdint>
#include <cstdlib>
#include <unordered_map>
#include <cassert>

#include "tools.h"

#if defined(_MSC_VER)
    #define ASSERT_WITH_CLEANUP(cond, fmt, ...) \
    if (!(cond)) { \
            fprintf(stderr, fmt, __VA_ARGS__); \
            cleanup(); \
            exit(-1); \
    }
#elif defined(__GNUC__)
#define ASSERT_WITH_CLEANUP(cond, fmt, ...) \
    if (!(cond)) {                              \
        fprintf(stderr, #__VA_ARGS__);                 \
        cleanup();                                \
        exit(-1);   \
    }

//#define FIRST(...) FIRST_HELPER(__VA_ARGS__, throwaway)
//#define FIRST_HELPER(first, ...) first
//
//#define REST(...) REST_HELPER(NUM(__VA_ARGS__), __VA_ARGS__)
//#define REST_HELPER(qty, ...) REST_HELPER2(qty, __VA_ARGS__)
//#define REST_HELPER2(qty, ...) REST_HELPER_##qty(__VA_ARGS__)
//#define REST_HELPER_ONE(first)
//#define REST_HELPER_TWOORMORE(first, ...) , __VA_ARGS__
//#define NUM(...) \
//    SELECT_10TH(__VA_ARGS__, TWOORMORE, TWOORMORE, TWOORMORE, TWOORMORE, \
//        TWOORMORE, TWOORMORE, TWOORMORE, TWOORMORE, ONE, throwaway)
//#define SELECT_10TH(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, ...) a10
#endif

constexpr uint8_t address_space_size = 0xFF;

class Assembler {
public:
    explicit Assembler(const char *path, const std::string &output_file) {
        asm_source_ = tools::cStyleLoadFileIntoMemory(path);
        assert(asm_source_ != nullptr && "asm_source_ is nullptr");
		address_space_.resize(address_space_size);
		data_section_ptr = 0xF0;
		
		generateSymbolTable();
		assemble(output_file);
    }

    ~Assembler() {
        cleanup();
    }


    void generateSymbolTable();

    void assemble(const std::string& output_file);

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

