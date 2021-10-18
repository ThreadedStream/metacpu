#pragma once

#include <cstdint>
#include "token.h"


class Tokenizer {
public:

	static Token addi(const char *src, int32_t src_len, int32_t &pos);

    static Token subi(const char *src, int32_t src_len, int32_t &pos);

    static Token add(const char *src, int32_t src_len, int32_t &pos);

    static Token sub(const char *src, int32_t src_len, int32_t &pos);

    static Token str(const char *src, int32_t &pos);

    static Token bz(const char *src, int32_t &pos);

    static Token clac(const char *src, int32_t src_len, int32_t &pos);

    static Token *number(const char *src, int32_t len, int32_t &pos);

    static Token *label(const char *src, int32_t len, int32_t &pos);

    static Token *operand(const char *src, int32_t src_len, int32_t &pos);
};
