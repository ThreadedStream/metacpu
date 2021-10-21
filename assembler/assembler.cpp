#include <cassert>
#include <cstring>
#include <algorithm>
#include <cstdlib>

#include "assembler.h"
#include "token.h"
#include "instruction.h"


#define ASSERT_WITH_CLEANUP(cond, fmt, ...) \
if (!(cond)) { \
		fprintf(stderr, fmt, __VA_ARGS__); \
		cleanup(); \
		exit(-1); \
} 

// 0 -> 0xFF
// data section -> [0xF0, 0xFF]


void Assembler::generateSymbolTable() {
	assert(asm_source_ != nullptr && "asm_source_ is nullptr!!!");
	uint8_t pc{ 0 };
	const auto len = strlen(asm_source_);
	std::string token;
	char curr_c;
	for (uint32_t pos = 0; pos < len, isascii(asm_source_[pos]); ++pos) {
        curr_c = asm_source_[pos];
		if (curr_c == '.') {
			// advance position in order to skip '.'
			pos++;
			const auto label_name = getLabelName(pos, len);
			// store that into symbol table
			proc_sym_table_.emplace(label_name, pc);
		
		} else if (isascii(curr_c) && isspace(curr_c)) {
            continue;
		} else {
			token += curr_c;

			const auto it = instructions.find(token);
			// increment pc in case of encountered instruction
			if (it != instructions.cend() && pos+1 < len && isspace(asm_source_[pos+1])) {
                fprintf(stdout, "Token: %s, Mode: %d\n", token.c_str(), it->second);
                pc++;
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

void Assembler::assemble() {	
	assert(asm_source_ != nullptr && "asm_source_ is nullptr!!!");
	uint8_t pc{ 0 };
	const auto len = strlen(asm_source_);
	std::string token;
	char curr_c;
	for (uint32_t pos = 0; pos < len, isascii(asm_source_[pos]); ++pos) {
		curr_c = asm_source_[pos];
		if (curr_c == '.') {
			// ignore labels
			nextLine(pos, len);
		}
		else if (isascii(curr_c) && isspace(curr_c)) {
			continue;
		}
		else {
			token += curr_c;
			// TODO(threadedstream): At that point, i don't think we need instruction mode anymore.
			// I'll probably elide it and make more room for instructions, thus allowing up to 255 entries in my 
			// yet poor instruction set. 
			const auto it = instructions.find(token);
			if (it != instructions.cend() && pos + 1 < len && isspace(asm_source_[pos + 1])) {
				pos++;
				if (it->second == InstructionMode::NONE) {
					address_space_[pc] = assembleInstruction(token, static_cast<uint16_t>(it->second), 0x0);
					//machine_code += ' ';
					token = "";
				}
				else if (it->second == InstructionMode::IMMEDIATE) {
					const auto value = fetchImmediateOperand(pos, len);
					address_space_[pc] = assembleInstruction(token, static_cast<uint16_t>(it->second), value);
					//machine_code += ' ';
					token = "";
				}
				else {
					// Memory instruction mode
					const auto value = fetchMemoryOperand(pos, len);
					address_space_[pc] = assembleInstruction(token, static_cast<uint16_t>(it->second), value);
					//machine_code += ' ';
					token = "";
				}
				pc++;
			}
		}
	}
	
	const auto success = tools::cStyleWriteToFile("D:/toys/metacpu/assembler/samples/sample.bin", address_space_);
	ASSERT_WITH_CLEANUP(success, "");
}

uint32_t Assembler::fetchMemoryOperand(uint32_t &pos, uint32_t len) {
	eatWhitespaces(pos, len);
	std::string value;
	while (pos < len && !isspace(asm_source_[pos])) {
		value += asm_source_[pos];
		pos++;
	}

	const auto label_it = proc_sym_table_.find(value);
	const auto var_it = data_var_sym_table_.find(value);


	// make sure value does not exist in both symbol tables
	const auto multiple_definition_cond = label_it != proc_sym_table_.cend() && var_it != data_var_sym_table_.cend();
	ASSERT_WITH_CLEANUP(!multiple_definition_cond, "multiple definition of %s", value);
		

	if (label_it != proc_sym_table_.cend()) {
		return proc_sym_table_[value];
	}
	else if (var_it != data_var_sym_table_.cend()) {
		return data_var_sym_table_[value];
	}
	else {
		fprintf(stderr, "unresolved symbol %s", value);
		cleanup();
		exit(-1);
	}
}



uint32_t Assembler::fetchImmediateOperand(uint32_t& pos, uint32_t len) {
	eatWhitespaces(pos, len);
	std::string value;
	while (pos < len && !isspace(asm_source_[pos])) {
		value += asm_source_[pos];
		pos++;
	}
	
	return static_cast<uint32_t>(atoi(value.c_str()));
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
		ASSERT_WITH_CLEANUP(data_section_ptr < 0xFF, "data section overflow");
		data_var_sym_table_[identifier] = data_section_ptr++;
		address_space_[data_section_ptr - 1] = value_int;
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
		ASSERT_WITH_CLEANUP(asm_source_[pos] == symbol, "expected %c", symbol);
	}
	else {
		return;
	}
	
	pos++;
}


uint32_t Assembler::lookupLabel(const std::string& name) {
	const auto val = proc_sym_table_[name];
	ASSERT_WITH_CLEANUP(val != 0, "unresolved label %s", name);

	return val;
}


std::string Assembler::getLabelName(uint32_t& pos, uint32_t len) {
    std::string label;
    while (pos < len && asm_source_[pos] != ':') {
        label += asm_source_[pos];
        pos++;
    }
	
	return label;
}

