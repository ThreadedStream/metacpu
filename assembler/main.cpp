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
std::map<std::string, HandlerFuncPtr> handlers = {
        {"addi", &Parser::addi},
        {"subi", &Parser::subi},
        {"add", &Parser::add}
        {"clac", &Parser::clac},

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
        const auto handler = handlers[token];
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


char *loadSrcIntoMemory(const char *const path) {
    std::ifstream stream(path, std::ios::in | std::ios::app);
    if (!stream) {
        fputs("[[error]] make sure that path to the file is correct\n", stderr);
        return nullptr;
    }

    stream.seekg(0, std::ios::end);
    const auto file_size = stream.tellg();
    stream.seekg(0);

    char *src = static_cast<char *>(calloc(file_size, sizeof(char)));
    if (!src) {
        std::fputs("[[error]] failed to allocate memory for a source buffer\n", stderr);
        return nullptr;
    }
    if (!stream.read(src, file_size)) {
        fputs("[[error]] failed to read from a file\n", stderr);
        return nullptr;
    }

    return src;
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

    char *src = loadSrcIntoMemory("../../samples/sample.asm");
    parse(src);

    free(src);
    for (auto &token : tokens) {
        free(token.operand);
        token.operand = nullptr;
    }

    return 0;
}
