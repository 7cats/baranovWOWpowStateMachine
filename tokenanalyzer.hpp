#pragma once

#include <string>
#include <vector>

enum TokenType {
    TAnumber, TAvar, TAfunc, TAtrash, TAoperation
};

class TokenAnalyzer 
{
    public:
        TokenType get_token_type(const std::string &token);

    private:
        const char m_operations[5 + 1] = {'+', '-', '*', '/','^'};
        std::vector<std::string> m_funcs = {"sin", "cos", "tg"};
};