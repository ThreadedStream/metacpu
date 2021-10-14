#include <cassert>
#include <cstring>
#include <algorithm>

#include "assembler.h"
#include "token.h"

void Assembler::generateSymbolTable() {
    assert(asm_source_ != nullptr && "asm_source_ is nullptr!!!");
    const auto len = strlen(asm_source_);
    std::string token;
    char curr_c;
    for (uint32_t i = 0; i < len; ++i) {
        curr_c = asm_source_[i];
        if (curr_c == '.') {
            parseLabel(i, len);
        } else {
            token += curr_c;
            const auto it = std::find(reserved_tokens.cbegin(), reserved_tokens.cend(), token);
            if (it != reserved_tokens.end()) {
                lc++
            }
        }
    }
}

void Assembler::parseLabel(uint32_t& pos, uint32_t len) {
    std::string label;
    while (pos < len && asm_source_[pos] != ':') {
        label += asm_source_[pos];
        pos++;
    }

    assert(pos == len && "eof");

    // store that into symbol table

}

