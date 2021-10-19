#include <stdio.h>
#include <stdlib.h>

#include "utils.h"


int16_t* readBinaryData(const char* path, const int32_t offset) {
    FILE *stream = fopen(path, "rb");
    if (!stream) {
        return NULL;
    }	
  

	uint16_t* buffer = (uint16_t*) (calloc(10, sizeof(uint16_t)));
	if (!buffer) {
		return NULL;
	}
	
	fseek(stream, offset, SEEK_SET);

	if (!fread(buffer, sizeof(uint16_t), 6, stream)) {
		return NULL;
	}
	
	fclose(stream);

	return buffer;   
}


