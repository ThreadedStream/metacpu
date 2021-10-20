#include "vm.h"



int main(int argc, const char* argv[]) {
	// TODO(threadedstream): make paths more 
	const char* path = "D:/toys/metacpu/assembler/samples/sample.bin";

	Interpreter interp;

	interp.initializeVm(path);
	
	interp.simulate();
	return 0;

}