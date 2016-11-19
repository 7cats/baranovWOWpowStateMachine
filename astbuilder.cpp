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

void ASTBuilder::add_operand(const std::string &operand, TokenType ttype)
{
    
}

void ASTBuilder::add_boperation(const std::string &bOper, TokenType ttype)
{
    
}

void ASTBuilder::add_bracket(const std::string &bracket, TokenType ttype)
{
    
}

void ASTBuilder::add_uoperation(const std::string &uOper, TokenType ttype)
{
    
}

void ASTBuilder::error(const std::string &errorLex, TokenType ttype)
{
    
}

void ASTBuilder::optimize_tree()
{
    
}