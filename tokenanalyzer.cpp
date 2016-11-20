#include "tokenanalyzer.hpp"

TokenType TokenAnalyzer::get_token_type(const std::string &token, 
    size_t * const stTableIdx)
{
    //try convert to ld -> return number
    try {
        size_t indx = 0;
        std::stold(token, &indx);
        if (indx == token.size()) {
            if (indx > 20) {
                std::cout << "Input the number of very large, possible loss of "
                    << "precision" << std::endl;
            }
            if (stTableIdx != 0) { *stTableIdx = TIoperand; }
            return TAnumber;
        }
    } catch (...) {
        //continue
    }
    
    if (token[0] == '(' || token[0] == ')') {
        if (stTableIdx != 0) { *stTableIdx = TIbracket; }
        return TAbracket;
    }
    
    //try compare with func names -> return func
    for (int i = 0; i < (int)m_funcs.size(); i++) {
        if (token == m_funcs[i]) {
            if (stTableIdx != 0) { *stTableIdx = TIfunc; }
            return TAfunc;
        }
    }
    //check for operation -> return operation
    if (token.size() == 1) {
        for (int i = 0; m_operations[i] != 0; i++) {
            if (token[0] == m_operations[i]) {
                if (stTableIdx != 0) { *stTableIdx = TIoperation; }
                return TAoperation;
            }
        }
    }
    // check for var name
    if (!std::isdigit(token[0])) {
        if (stTableIdx != 0) { *stTableIdx = TIoperand; }
        return TAvar;
    }
    
    if (stTableIdx != 0) { *stTableIdx = TItrash; }
    return TAtrash;
}