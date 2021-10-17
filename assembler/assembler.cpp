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
	for (uint32_t pos = 0; pos < len, isascii(asm_source_[pos]); ++pos) {
        curr_c = asm_source_[pos];
		if (curr_c == '.') {
			// advance position in order to skip '.'
			pos++;
			parseLabel(pos, len);
		} else if (isascii(curr_c) && isspace(curr_c)) {
            continue;
        } else {
            token += curr_c;
			// increment pc in case of encountered instruction
			if (instructions[token]) {
                fprintf(stdout, "%s\n", token.c_str());
                pc_++;
                nextLine(pos, len);
                token = "";
			}
			// beginning of data section
			else if (token == "BEGINDATA"){
				// advance position in order to jump over 'A' character
				pos++;
				// move to the next line
				parseVarBlock(pos, len);
				token = "";
			}
			else {
				continue;
			}
        }
    }
}


void Assembler::nextLine(uint32_t &pos, const uint32_t len) {
    while (pos < len && asm_source_[pos] != '\n') {
        pos++;
    }
}

void Assembler::parseVarBlock(uint32_t &pos, uint32_t len) {
	std::string identifier, value;
	eatWhitespaces(pos, len);
	expectSymbol('{', pos, len);
	eatWhitespaces(pos, len);


	while (pos < len && asm_source_[pos] != '}') {
		while (pos < len && asm_source_[pos] != ' ') {
			identifier += asm_source_[pos];
			pos++;
		}

		eatWhitespaces(pos, len);
		expectSymbol('=', pos, len);
		eatWhitespaces(pos, len);

		while (!isspace(asm_source_[pos])) {
			value += asm_source_[pos];
			pos++;
		}

		const auto value_int = atoi(value.c_str());
		data_var_sym_table_[identifier] = value_int;
		identifier = ""; value = "";
		eatWhitespaces(pos, len);
	}

	// making sure that data var block is terminated with '}' symbol
	// throw an exception if it is not.
	expectSymbol('}', pos, len);

	return;
}

void Assembler::expectSymbol(uint8_t symbol, uint32_t& pos, uint32_t len) {
	if (pos < len) {
		static char error_buffer[64];
		sprintf(error_buffer, "expected %c", symbol);
		assert(asm_source_[pos] == symbol && error_buffer);
	}
	else {
		return;
	}
	
	pos++;
}

void Assembler::parseLabel(uint32_t& pos, uint32_t len) {
    std::string label;
    while (pos < len && asm_source_[pos] != ':') {
        label += asm_source_[pos];
        pos++;
    }

    // store that into symbol table
    proc_sym_table_.emplace(label.c_str(), pc_);
}

