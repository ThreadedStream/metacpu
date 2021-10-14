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
std::map<std::string, HandlerFuncPtr> opcode_handlers = {
        {"addi", &Tokenizer::addi},
        {"subi", &Tokenizer::subi},
        {"add", &Tokenizer::add},
        {"clac", &Tokenizer::clac},
};


// Phases of a metacpu assembler
// 1) resolve aliases (labels)
// 2) parse the resolved assembly code
// 3) generate an equivalent machine code

/*
	Example program:
.text
	clac
	addi 52
	subi 32
	str  a
.endtext
.data
	.label a
.endata
*/

void parseDirective() {
}


void parse(const char *src) {
    assert(src != nullptr && "src is nullptr!!!!");
    std::string token;
    const auto len = strlen(src);
    char curr_c{0};
    for (int32_t i = 0; i < len; i++) {
        curr_c = *(src + i);
        if (isspace(curr_c)) {
            continue;
        }
        const auto handler = opcode_handlers[token];
        if (handler) {
            tokens.push_back(handler(src, len, i));
            token = "";
            continue;
        }
        if (curr_c == '.') {
            parseDirective();
            token = "";
            continue;
        } else {
            token += curr_c;
        }
    }
}




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

    char *src = tools::loadFileIntoMemory("../../samples/sample.asm");
    parse(src);

    free(src);
    for (auto &token : tokens) {
        free(token.operand);
        token.operand = nullptr;
    }

    return 0;
}
