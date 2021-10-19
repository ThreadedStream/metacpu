#include <map>
#include <cstdint>
#include <fstream>
#include <cstdlib>
#include <cassert>
#include <string>
#include <vector>
#include <cstring>

#include "tokenizer.h"
#include "assembler.h"
#include "tools.h"
#include "instruction.h"

std::map<const char *, int16_t> symbol_table;

std::vector<Token> tokens;

typedef Token (*HandlerFuncPtr)(const char *src, int32_t src_len, int32_t &pos);

// Available instructions:
// addi imm     - add immediate to acc
// subi imm     - subtract immediate from acc
// clac         - clear acc
// add label    - add value at address aliased by label to acc
// sub label    - subtract value at address aliased by label from acc
// bz  label    - branch to label if acc = 0
// str label    - store value at address aliased by label into acc
std::map<std::string, HandlerFuncPtr> instruction_handlers = {
        {"addi", &Tokenizer::addi},
        {"subi", &Tokenizer::subi},
        {"add", &Tokenizer::add},
        {"clac", &Tokenizer::clac},
};

// Phases of a metacpu assembler
// 1) resolve aliases (labels)
// 2) parse the resolved assembly code
// 3) generate an equivalent machine code



#if 0
void resolveLabels(char *src) {
    assert(src != nullptr && "src is nullptr!!!");
    char curr_char = *src;
    std::string buf;
    switch (curr_char) {
        case ' ':
        case '\t':
        case '\r':
            break;
        case '\n':
            break;
        case '.':
            parseDirective();
            break;
    }
}
#endif

int main(int argc, const char *argv[]) {
    Assembler assembler("D:\\toys\\metacpu\\assembler\\samples\\sample.asm");

    assembler.generateSymbolTable();

	assembler.assemble();

	const auto &proc_sym_table = assembler.procSymTable();
	const auto &var_sym_table = assembler.dataVarSymTable();
	
    return 0;
}
