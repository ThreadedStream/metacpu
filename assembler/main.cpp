#define _CRT_SECURE_NO_WARNINGS 1

#include <map>
#include <fstream>
#include <vector>
#include <cstring>

#include "tokenizer.h"
#include "assembler.h"

// Phases of a metacpu assembler
// 1) resolve aliases (labels)
// 2) parse the resolved assembly code
// 3) generate an equivalent machine code

int main(int argc, const char *argv[]) {
	if (argc < 2) {
		fputs("nothing to assemble", stderr);
		exit(-1);
	}
	
	std::string output_file;
	if (argc > 3) {
		output_file = argv[3];
	}
	else {
		std::string source = argv[1];
		const auto idx = source.find_first_of(".");
		if (idx != std::string::npos) {
			output_file = source.substr(0, idx) + ".bin";
		}
		else {
			output_file = "main.bin";
		}
	}
	

    Assembler assembler(argv[1], output_file);

    return 0;
}
