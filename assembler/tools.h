#pragma once
#include <fstream>

namespace tools {
    static char *loadFileIntoMemory(const char *const path) {
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

}