#include "../mathexpression.hpp"
#include <iostream>
#include <string>
#include <vector>

int main() {
    //arithmetic tests
    std::vector< std::pair<std::string, long double> > ar_tests = { 
        std::make_pair("2 + 2 + 2 / 2", 5),
        std::make_pair("2 + 2 + 2 * 2", 8),
        std::make_pair("(2 + 2 + 2) / 2", 3),
        std::make_pair("(2 + 2) + 2", 6),
        std::make_pair("-2", -2),
        std::make_pair("-2 - 2", -4),
        std::make_pair("(-2) + 2", 0),
        std::make_pair("-2 + 2", 0),
        std::make_pair("0 - 1 + 1", 0),
        std::make_pair("2 * 2", 4),
        std::make_pair("2 / 2", 1),
        std::make_pair("2 ^ 10", 1024),
        std::make_pair("(2 + 2) ^ 2", 16),
        std::make_pair("1 + 1 * 2", 3),
        std::make_pair("0", 0),
        std::make_pair("1378966878768726871368726781268312362683 + 1", 1378966878768726871368726781268312362683 + 1),
        std::make_pair("-2 * (-2)", 4),
        std::make_pair("(-2) * (-2)", 4),
        std::make_pair("1 ^ 10", 1),
        std::make_pair("2 * 2 / 2", 2),
        std::make_pair("2 / 2 + 1", 2),
        std::make_pair("2 ^ 2 ^ 2", 16),
        std::make_pair("0 + 9 - 0", 9)
    };
    
    MathExpr mE;
    std::cout << "Arithmetic tests:" << std::endl;
    for (int i = 0; i < (int)ar_tests.size(); i++) {
        mE << ar_tests[i].first;
        if (mE.evaluate() == ar_tests[i].second) {
            std::cout << i << " test: OK";  
        } else {
            std::cout << i << " test: FAIL";
        }
        std::cout << ", expression: " << ar_tests[i].first;
        std::cout << ", expected " << ar_tests[i].second << " and return " << 
                mE.evaluate() << std::endl;
    }
    
    
    return 0;
}