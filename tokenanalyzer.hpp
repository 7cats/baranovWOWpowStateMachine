#pragma once

#include <string>
#include <vector>
#include <iostream>

enum TokenType {
    TAoperation = 0, TAnumber = 1, TAvar = 2, TAbracket = 3, TAfunc = 4, TAtrash = 5
};

enum TokenStateIdx {
    TIoperation = 0, TIoperand = 1, TIbracket = 2, TIfunc = 3, TItrash = 4
};

class TokenAnalyzer 
{
    public:
        TokenType get_token_type(const std::string &token, size_t * const stTableIdx = 0);

    private:
        const char m_operations[6 + 1] = {'+', '-', '*', '/','^', -'-'};
        std::vector<std::string> m_funcs = {"sin", "cos", "tg"};
};