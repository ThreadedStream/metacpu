#pragma once

#include <fstream>
#include <filesystem>
#include "../common/errors.h"

namespace tools {
	
	static inline char* stripNonAsciiGarbageOff(const char* target, uint32_t size) {
		char* out = static_cast<char*>(calloc(size, sizeof(char)));
		if (!out) {
			fputs(errors[FAILED_TO_ALLOCATE_MEMORY], stderr);
			return nullptr;
		}

		int32_t j = 0;
		for (int32_t i = 0; i < size; ++i) {
			if (isascii(target[i])) {
				out[j] = target[i];
				j++;
			}
		}

		return out;
		
	}

    static char *cppStyleLoadFileIntoMemory(const char *const path) {
        std::ifstream stream(path, std::ios::in | std::ios::app);
        if (!stream) {
            fputs("[[error]] make sure that path to the file is correct\n", stderr);
            return nullptr;
        }

        stream.seekg(stream.beg, stream.end);
        const auto file_size = std::filesystem::file_size(path);
        stream.seekg(stream.beg);

        char *src = static_cast<char *>(calloc(file_size, sizeof(char)));
        if (!src) {
            std::fputs("[[error]] failed to allocate memory for a source buffer\n", stderr);
            return nullptr;
        }

        stream.read(src, file_size);
        if (!stream) {
            fprintf(stderr, "[[error]] failed to read from a file, only %ld character could be read\n",
                    stream.gcount());
            return nullptr;
        }

        stream.close();

        return src;
    }

    static char *cStyleLoadFileIntoMemory(const char *const path, uint32_t *size) {
		// TODO(threadedstream): when opened in binary mode, buffer also retrieves
		// some piece of shitty garbage. I probably should investigate this problem further, inasmuch as
		// comparison of the number of read bytes against the actual file size, which in turn
		// happens to be a result of calling ftell, ends up evaluated as true, thus proceeding 
		// to execution block containing report of an error and returning nullptr. The most 
		// surprising consequence of this whole C++ opera is that buffer does not contain any garbage anymore -- just a plain ascii text. 
        FILE *stream = fopen(path, "r");
        if (!stream) {
            fputs("[[error]] make sure that path to the file is correct\n", stderr);
            return nullptr;
        }

        fseek(stream, 0, SEEK_END);
        const auto len = ftell(stream);
        fseek(stream, 0, SEEK_SET);

        char *buffer = static_cast<char *>(calloc(len, sizeof(char)));
        if (!buffer) {
            std::fputs("[[error]] failed to allocate memory for a source buffer\n", stderr);
            return nullptr;
        }


        const auto read = fread(buffer, sizeof(char), len, stream);
        //if (read != len) {
        //    fprintf(stderr, "[[error]] failed to read from a file, left to read %ld characters", len - read);
        //    return nullptr;
        //}

        fclose(stream);

		*size = len;

        return buffer;
    }

    // TOTEST(threadedstream)
    static bool cppStyleWriteToFile(const char *const path, const std::string &contents) {
        std::ofstream stream(path, std::ios::app | std::ios::out);

        if (!stream) {
            fputs("[[error]] make sure that path to the file is correct\n", stderr);
            return false;
        }

        // writing preamble
        const char preamble[] = "metasm v_1_0";
        stream.write(preamble, sizeof(preamble));
        if (!stream) {
            fputs("[[error]] failed to write preamble to a file\n", stderr);
            return false;
        }

        // writing content buffer
        const auto len = contents.size();
        stream.write(contents.c_str(), len);
        if (!stream) {
            fputs("[[error]] failed to put contents into a file\n", stderr);
            return false;
        }

        // disposing of the held resource
        stream.close();
        return true;
    }

    // TODO(threadedstream): test transfer of an ownership against "const char* const"
    static bool cStyleWriteToFile(const char *const path, const std::vector<uint16_t> &opcodes) {
        FILE *stream = fopen(path, "wb");
        if (!stream) {
            fputs("[[error]] make sure that path to the file is correct\n", stderr);
            return false;
        }

        // writing preamble
        const char preamble[] = "metasm v_1_0";
        if (!fwrite(preamble, 1, sizeof(preamble), stream)) {
            fputs("[[error]] failed to write preamble to a file\n", stderr);
            return false;
        }

        const auto len = opcodes.size();
        if (!fwrite(opcodes.data(), sizeof(uint16_t), len, stream)) {
            fputs("[[error]] failed to put contents into a file\n", stderr);
            return false;
        }

        fclose(stream);

        return true;
    }
}