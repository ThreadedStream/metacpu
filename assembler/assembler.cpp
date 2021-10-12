#include "assembler.h"
#include <string>

Token Parser::addi(const char* src, int32_t src_len, int32_t& pos) {
    Token addi_token = {
            .type = TokenType::OPCODE,
            .name = "addi",
    };

    addi_token.operand = Parser::number(src, src_len, pos);

    return addi_token;
}

Token Parser::subi(const char* src, int32_t src_len, int32_t& pos) {
    Token subi_token = {
        .type = TokenType::OPCODE,
        .name = "subi"
    };

    subi_token.operand = Parser::number(src, src_len, pos);

    return subi_token;
}

Token Parser::add(const char* src, int32_t src_len, int32_t &pos) {
    Token add_token = {
            .type = TokenType::OPCODE,
            .name = "add"
    };

    add_token.operand = Parser::label(src, src_len, pos);

    return add_token;
}

Token Parser::sub(const char* src, int32_t src_len, int32_t &pos) {
    Token sub_token = {
            .type = TokenType::OPCODE,
            .name = "sub"
    };

    sub_token.operand = Parser::label(src, src_len, pos);

    return sub_token;
}

Token Parser::clac(const char* src, int32_t src_len, int32_t& pos) {
    Token clac_token = {
            .type = TokenType::OPCODE,
            .name = "clac"
    };

    return clac_token;
}
Token* Parser::number(const char* src, int32_t len, int32_t& pos) {
    std::string str_num;
    for (auto curr = *(src + pos); isdigit(curr) && curr != ';'; pos++, curr = *(src + pos)) {
        str_num += curr;
    }

    auto number_token = static_cast<Token*>(malloc(sizeof(Token)));
    number_token->type = TokenType::NUMBER;
    number_token->name = str_num.c_str();
    number_token->value_int = std::atoi(str_num.c_str());

    return number_token;
}

Token Parser::str(const char* src, int32_t& pos) {
    Token str_token = {
            .type = TokenType::OPCODE,
            .name = "str"
    };



    return str_token;
}

Token* Parser::label(const char* src, int32_t len, int32_t& pos) {
    std::string str;
    for (auto curr = *(src + pos); isalpha(curr) && curr != ';'; pos++, curr = *(src + pos)){
        str += curr;
    }
    auto address_token = static_cast<Token*>(malloc(sizeof(Token)));
    address_token->type = TokenType::LABEL;
    address_token->name = str.c_str();
    address_token->value_str = str.c_str();

    return address_token;
}

Token* Parser::operand(const char* src, int32_t src_len, int32_t& pos) {
    std::string token;
    for ( auto curr_c = *(src + pos); curr_c != ';' && pos < src_len; pos++, curr_c = *(src + pos)) {
        if (curr_c == ' '  || curr_c == '\t' || curr_c == '\r')
            continue;
        else if (isdigit(curr_c))
            return Parser::number(src, src_len, pos);
        else if (isalpha(curr_c))
            return Parser::label(src, src_len, pos);
        else
            // NOTE(threadedstream): for now, we know FOR SURE that the last option is a label
            token += curr_c;
    }

    return nullptr;
}

Token Parser::bz(const char *src, int32_t &pos) {
    Token token{};

    return token;
}
