#include <string>
#include <vector>
#include <iostream>

#include "../tokenanalyzer.hpp"

int main() {
    TokenAnalyzer ta;
    std::vector<std::string> tests       = {"123123123.1231231231", "x", "1234242!x123.12321",
        "+", "-", "/", "*", "^", "sin", "cos", "tg",
        "1dasdasd", "_dsjfhskf@_____dssf", "1e-9"
    };
    std::vector<TokenType> cAnswers      = {TAnumber,                TAvar, TAtrash,
        TAoperation, TAoperation, TAoperation, TAoperation, TAoperation, TAfunc, TAfunc, TAfunc,
        TAtrash, TAvar, TAnumber
    };
    std::vector<std::string> nameOfTests = {"Basic number", "Basic var", "Wrong number",
        "Op +", "Op -", "Op /", "Op *", "Op ^", "func", "func", "func",
        "Wrong var", "Advanced var", "Advanced number" 
    };
    
    for (int i = 0; i < (int)tests.size(); i++) {
        std::cout << nameOfTests[i] + ' ' + "test";
        if (cAnswers[i] == ta.get_token_type(tests[i])) {
            std::cout << " complited" << std::endl; 
        } else {
            std::cout << " failed" << std::endl;
            std::cout << "Test: " << tests[i] << std::endl;
            std::cout << "Expected " << cAnswers[i] << " but found " << ta.get_token_type(tests[i]) << std::endl;
        }
    }
    return 0;
}