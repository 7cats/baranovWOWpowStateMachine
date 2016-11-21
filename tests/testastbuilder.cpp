#include "../astbuilder.hpp"
#include <iostream>

int main() {
    ASTBuilder ast("-(1+1) + sin(cos(sin(2)) +  1^(2^2^2) - 1 + 1 * 1 / 1 + 1 - 1 + 1");
    ASTNode *a = ast.get_ast_root();
    //std::cout << a->m_token <<" right: " << a->m_children[0]->m_token << std::endl;
    return 0;
}

/* " left: " << (a->m_children[1]->m_children[1]->m_token) <<*/ 