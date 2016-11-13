#include "tokenanalyzer.hpp"

TokenType TokenAnalyzer::get_token_type(const std::string &token)
{
    //try convert to ld -> return number
    try {
        size_t indx = 0;
        std::stold(token, &indx);
        if (indx == token.size()) {
            return TAnumber;
        }
    } catch (...) {
        //continue
    }
    //try compare with func names -> return func
    for (int i = 0; i < (int)m_funcs.size(); i++) {
        if (token == m_funcs[i]) {
            return TAfunc;
        }
    }
    //check for operation -> return operation
    if (token.size() == 1) {
        for (int i = 0; m_operations[i] != 0; i++) {
            if (token[0] == m_operations[i]) {
                return TAoperation;
            }
        }
    }
    // check for var name
    if (!std::isdigit(token[0])) {
        return TAvar;
    }
    return TAtrash;
}