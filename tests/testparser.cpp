#include "../expressionparser.hpp"
#include <iostream>

int main() {
    ExpressionParser exprp;
    exprp << " 2 + 2sin(2)*tg123__ + int * (2 + 9) / w^(10) wgdjadjsdagwe 1.22 1.";
    std::string lecks;
    exprp >> lecks;
    while (lecks != std::string(1, '\n')) {
        std::cout << lecks << std::endl;
        exprp >> lecks;
    }
    exprp << "";
    exprp >> lecks >> lecks;
    std::cout << lecks;
    return 0;
} 