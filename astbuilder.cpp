#include "astbuilder.hpp"

ASTBuilder::ASTBuilder()
{
}

ASTBuilder::ASTBuilder(const std::string &expr) 
{
    build_tree(expr);
}

void ASTBuilder::build_tree(const std::string &expr) 
{
    m_expParser << expr;
    std::string lex;
    m_expParser >> lex;
    while (lex != EXPRPARSEREOF) {
        TokenType ttype = m_tAnalyzer.get_token_type(lex);
        /*
            в зависимости от типа токена и состояния ДКА вызываем нужную функцию
        */
    }
}

void ASTBuilder::add_number(lld number) 
{
    
}

void ASTBuilder::add_var(const std::string &varName)
{
    
}

void ASTBuilder::add_binary_operation(const std::string &bOper)
{
    
}

void ASTBuilder::add_unary_operation(char uOper)
{
    
}

void ASTBuilder::add_function(const std::string &funcName)
{
    
}

void ASTBuilder::optimize_tree()
{
    
}