#include "astbuilder.hpp"

//#define ASTDEBUG
//#define ASTDEBUG_HARD

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
        #ifdef ASTDEBUG_HARD
            std::cout << "!!!Get " + lex + " "<< ttype << " types" << std::endl;
            std::cout << "State: " << m_state << " stateIdx: " << stateTIdx << std::endl;
        #endif
        (this->*(ASTBuilder().m_stateTable[m_state][stateTIdx]))(lex, ttype);
        m_expParser >> lex;
    }
    #ifdef ASTDEBUG
        std::cout << "Last call prepare_operat_stack..." << std::endl;
    #endif
        prepare_operat_stack();
    #ifdef ASTDEBUG
        std::cout << "Last prepare_operat_stack finished successfully" << std::endl;
    #endif
    if (m_operandsStack.empty()) {
        std::cout << "Final result not found" << std::endl;
        throw 1;
    }
    m_root = m_operandsStack.top(); m_operandsStack.pop();
    assert(m_operandsStack.empty() == true);
    m_state = WExpression;
}

void ASTBuilder::add_operand(const std::string &operand, TokenType ttype)
{
    m_operandsStack.push(new ASTNode(operand));

    #ifdef ASTDEBUG
        std::cout << "Added operand: " << operand << std::endl;
    #endif
    #ifdef ASTDEBUG_HARD
        std::cout << "State changed to WOperation in add_operand" << std::endl;
    #endif
    m_state = WOperation;
}

void ASTBuilder::add_boperation(const std::string &bOper, TokenType ttype)
{
    assert(bOper.size() == 1);
    #ifdef ASTDEBUG
        std::cout << "Added new boperation: " + bOper << std::endl;
    #endif
    int prior = priority(bOper);
    prepare_operat_stack(prior);

    m_operationsStack.push(make_pair(bOper, prior));
    #ifdef ASTDEBUG_HARD
        std::cout << "State changed to WOperand in add_boperation" << std::endl;
    #endif
    m_state = WOperand;
}

void ASTBuilder::add_bracket(const std::string &bracket, TokenType ttype)
{
    if (bracket[0] == '(') {
        assert(bracket.size() == 1);
        m_operationsStack.push(make_pair(bracket, priority(bracket)));
        #ifdef ASTDEBUG
            std::cout << "Added bracket '('" << std::endl;
        #endif
        #ifdef ASTDEBUG_HARD
            std::cout << "State changed to WExpression in add_bracket" << std::endl;
        #endif
        m_state = WExpression;
    } else {
       assert(bracket[0] == ')');
       #ifdef ASTDEBUG
           std::cout << "Added bracket ')'" << std::endl;
       #endif
       while (m_operationsStack.top().first[0] != '(') {
           exec_top_stack_op();
       }
       m_operationsStack.pop();
       #ifdef ASTDEBUG_HARD
           std::cout << "State changed to WOperation in add_bracket" << std::endl;
        #endif
       m_state = WOperation;
    }
    #ifdef ASTDEBUG_HARD
        std::cout << "Ended add bracket" << std::endl;
    #endif
}

void ASTBuilder::add_uoperation(const std::string &uOper, TokenType ttype)
{
    if (uOper[0] != '-' && ttype == TAoperation) {
        std::cout << "Expected unary operation, but found " + uOper << std::endl;
        throw 1;
    }
    #ifdef ASTDEBUG
        std::cout << "Added uoperation: " + uOper << std::endl;
    #endif

    int prior = priority(uOper);
    prepare_operat_stack(prior);
    
    std::string noConstStr = uOper;
    
    if (uOper[0] == '-') {
        assert(uOper.size() == 1);
        noConstStr[0] = -noConstStr[0];
    }
    
    m_operationsStack.push(make_pair(noConstStr, prior));
    #ifdef ASTDEBUG_HARD
        std::cout << "State changed to WOperand in add_uoperation" << std::endl;
    #endif
    m_state = WOperand;
}

void ASTBuilder::error(const std::string &errorLex, TokenType ttype)
{
    std::cout << "ERROR: found " + errorLex << std::endl;
    throw 1;
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
    #ifdef ASTDEBUG
        std::cout << "In ASTBuilder::priority(std::string) \nReturn function priority" << std::endl;
    #endif    
    //function and unary priority
    return 10;    
}

void ASTBuilder::prepare_operat_stack(int currPrior)
{
    #ifdef ASTDEBUG_HARD
        std::cout << "Start prepare_operat_stack" << std::endl;
        std::cout << "currPrior: " << currPrior << std::endl;
    #endif

    while (!m_operationsStack.empty() && currPrior <= m_operationsStack.top().second) {
        #ifdef ASTDEBUG_HARD
            std::cout << "Called exec_top_stack_op" << std::endl;
            std::cout << "m_operationsStack.top().second = " << m_operationsStack.top().second << std::endl;
        #endif
        exec_top_stack_op();
    }
    #ifdef ASTDEBUG_HARD
        std::cout << "Ended prepare_operat_stack" << std::endl;
    #endif
}

void ASTBuilder::exec_top_stack_op()
{
    std::string op = m_operationsStack.top().first; m_operationsStack.pop();

    assert(op[0]  != ')');
   
    if (m_operandsStack.empty()) {
        std::cout << "Expected right(first for unary) operand for operation: " + op 
            + ", but not found"<< std::endl;
        throw 1;
    }
    ASTNode *anode = new ASTNode(op, m_operandsStack.top());
    m_operandsStack.pop();
    
    #ifdef ASTDEBUG
        std::cout << "Added new child for " + op << std::endl;
    #endif

    if (op[0] == '+' || op[0] == '-' || op[0] == '*' || op[0] == '/' || op[0] == '^') {
        if (m_operandsStack.empty()) {
            std::cout << "Expected left operand for operation: " + op 
                + ", but not found"<< std::endl;
            throw 1;   
        }
        anode->m_children.push_back(m_operandsStack.top());
        m_operandsStack.pop();
        #ifdef ASTDEBUG
            std::cout << "Added new child for " + op << std::endl;
        #endif
    }
    m_operandsStack.push(anode);

    #ifdef ASTDEBUG_HARD
        std::cout << "Ended exec_top_stack_op" << std::endl;
    #endif
}