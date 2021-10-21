#define _CRT_SECURE_NO_WARNINGS 1

#include "vm.h"


int main(int argc, const char* argv[]) {
	if (argc < 2) {
		fputs("nothing to interpret", stderr);
		exit(-1);
	}

	// compiler will implicitly convert const char* to std::string
	Interpreter interp(argv[1]);

	return 0;

}