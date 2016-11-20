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
        size_t stateTIdx = 0;
        TokenType ttype = m_tAnalyzer.get_token_type(lex, &stateTIdx);
    
        (this->*(ASTBuilder().m_stateTable[m_state][stateTIdx]))(lex, ttype);
        m_expParser >> lex;
    }
    
}

void ASTBuilder::add_operand(const std::string &operand, TokenType ttype)
{
    m_operandsStack.push(new ASTNode(operand));
}

void ASTBuilder::add_boperation(const std::string &bOper, TokenType ttype)
{
    assert(bOper.size() == 1);
    int prior = priority(bOper);
    prepare_operat_stack(prior);

    m_operationsStack.push(make_pair(bOper, prior));
}

void ASTBuilder::add_bracket(const std::string &bracket, TokenType ttype)
{
    if (bracket[0] == '(') {
        assert(bracket.size() == 1);
        m_operationsStack.push(make_pair(bracket, priority(bracket)));
    } else {
        assert(bracket[0] == ')');
        //TODO: выталкиваем операции, пока не встретим '(' в стеке операций
    }
}

void ASTBuilder::add_uoperation(const std::string &uOper, TokenType ttype)
{
    int prior = priority(uOper);
    prepare_operat_stack(prior);
    
    std::string noConstStr = uOper;
    
    if (uOper[0] == '-') {
        assert(uOper.size() == 1);
        noConstStr[0] = -noConstStr[0];
    }
    
    m_operationsStack.push(make_pair(noConstStr, prior));
}

void ASTBuilder::error(const std::string &errorLex, TokenType ttype)
{
    std::cout << "Found " + errorLex << std::endl;
}

void ASTBuilder::optimize_tree()
{
    
}

int ASTBuilder::priority(const std::string &oper)
{
    if (oper[0] == '(' || oper[0] == ')') { return 0; }
    if (oper[0] == '+' || oper[0] == '-') { return 1; }
    if (oper[0] == '*' || oper[0] == '/') { return 2; }
    if (oper[0] == '^')                   { return 3; }
    //unary '-'
    if (oper[0] == -(int)'-')             { return 4; }
    
    assert(oper.size() > 1);
#ifdef DEBUG
    std::cout << "In ASTBuilder::priority(std::string) \nReturn function priority" << std::endl;
#endif    
    //function and unary priority
    return 10;    
}

void ASTBuilder::prepare_operat_stack(int currPrior)
{
    while (currPrior >= m_operationsStack.top().second) {
        exec_top_stack_op();
        m_operationsStack.pop();
    }
}

void ASTBuilder::exec_top_stack_op()
{
    //TODO: выполнение 1 операции на вершине стека
}