#include "../mathexpression.hpp"
#include <iostream>
#include <string>
#include <vector>

void exec_test(const std::string &testSetName,
        const std::vector< std::pair<std::string, long double> > &tests,
        MathExpr &mE, 
        const std::vector< std::pair<std::string, long double> > &vars) {
    std::cout << testSetName + " tests:" << std::endl;
    for (int i = 0; i < (int)vars.size(); i++) {
        mE[vars[i].first] = vars[i].second;
    }
    for (int i = 0; i < (int)tests.size(); i++) {
        mE << tests[i].first;
        if (mE.evaluate() == tests[i].second) {
            std::cout << i << " test: OK";  
        } else {
            std::cout << i << " test: FAIL";
        }
        std::cout << ", expression: " << tests[i].first;
        std::cout << ", expected " << tests[i].second << " and return " << 
                mE.evaluate() << std::endl;
    }
    return;
}
 
int main() {
    //arithmetic tests
    std::vector< std::pair<std::string, long double> > tests = { 
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
        std::make_pair("0 + 9 - 0", 9),
        std::make_pair("2 ^ (2 - 2)", 1)
    };
    std::vector< std::pair<std::string, long double > > vars = {
        std::make_pair("x", 1),
        std::make_pair("y", 2),
        std::make_pair("y", 3),
        std::make_pair("sina", 4),
        std::make_pair("sda11", 5),
        std::make_pair("sda12", 6),
        std::make_pair("qwerty", 7)
    };

    MathExpr mE;
    exec_test("Arithmetic", tests, mE, vars);

    //func tests
    tests = {
        std::make_pair("sin(180)", 0),
        std::make_pair("sin(90 + 90)", 0),
        std::make_pair("sin(90 * 2)", 0),
        std::make_pair("cos(1) * cos(1) + sin(1) * sin(1)", 1),
        std::make_pair("cos(1)^2 + sin(1)^2", 1),
        std::make_pair("cos(123123)^2 + sin(123123)^2", 1)  
    };
    exec_test("Func", tests, mE, vars);
      
    //Vars tests  
    tests = {
        std::make_pair("x + y", 4),
        std::make_pair("x + y / 2", 2.5),
        std::make_pair("qwerty + sda12 + sda11 + sina + y + x", 26),
    };
    exec_test("Vars", tests, mE, vars);

    //"Vars, arithmetic and func"
    tests = {
        std::make_pair("cos(x * x * x + y)^2 + sin(x * x * x + y)^2 ", 1),
        std::make_pair("x + sina / 2 ^ 2", 2),
        std::make_pair("sda11 + y + x ^ (2 - 2) + sda12 - qwerty * sina", -13),
    };
    exec_test("Vars, arithmetic and func", tests, mE, vars);    
    return 0;
}