#include <map>
#include <cstdint>
#include <fstream>
#include <cstdlib>
#include <cassert>


static uint8_t current_address = 0x0;

constexpr uint8_t addr_inc = 0x1;

// Phases of a metacpu assembler
// 1) resolve aliases (labels)
// 2) parse the resolved assembly code
// 3) generate an equivalent machine code

char* loadSrcIntoMemory(const char* const path) {
	std::ifstream stream(path, std::ios::in | std::ios::app);
	
	stream.seekg(0, std::ios::end);
	const auto file_size = stream.tellg();
	stream.seekg(0);
	
	char* src = static_cast<char*>(calloc(file_size, sizeof(char)));
	if (!src){
		std::fputs(stderr, "[[error]] failed to allocate memory for loading source");
		return nullptr;
	}
	
	return src;
}

void resolveLabels(char* src) {
	assert(src != nullptr && "src is nullptr!!!");
	char curr_char = *src;	
	std::string buf; 
	switch(curr_char) {
	case ' ':
	case '\t':
	case '\n':
	case '\r':
		break;
	case '.':
		parseDirective();
		break;
	}
}	

void parseDirective(){
}
int main(int argc, const char* argv[]){ 
	
	
	return 0;
}
