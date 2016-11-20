#pragma once

#include <string>
#include <stack>
#include <cassert>
#include <climits>
#include <iostream>

#include "astnode.hpp"
#include "expressionparser.hpp"
#include "tokenanalyzer.hpp"

enum State {
    WExpression = 0, WOperation = 1, WOperand = 2
};

class ASTBuilder
{
    public:
        ASTBuilder();
        ASTBuilder(const std::string &expr);
        void build_tree(const std::string &expr);
        
    protected:
        ASTNode *m_root;
        
    private:
        void add_operand(const std::string &operand, TokenType ttype);
        void add_boperation(const std::string &bOper, TokenType ttype);
        void add_uoperation(const std::string &uOper, TokenType ttype);
        void add_bracket(const std::string &bracket, TokenType ttype);
        void error(const std::string &errorLex, TokenType ttype);
        void optimize_tree();
        int priority(const std::string &oper);
        void prepare_operat_stack(int currPrior = -1);
        void exec_top_stack_op();
        
        TokenAnalyzer m_tAnalyzer;
        ExpressionParser m_expParser;
        State m_state = WExpression;
        std::stack< std::pair< std::string, int > > m_operationsStack;
        std::stack<ASTNode*> m_operandsStack;
        
        std::vector< std::vector <void(ASTBuilder::*)(const std::string&, TokenType)> > m_stateTable = {
        //  TIoperation                    TIOperand                  TIbracket                 TIfunc                       TItrash
/*WExpr*/   {&ASTBuilder::add_uoperation,  &ASTBuilder::add_operand,  &ASTBuilder::add_bracket, &ASTBuilder::add_uoperation, &ASTBuilder::error},            
/*WOprt*/   {&ASTBuilder::add_boperation,  &ASTBuilder::error      ,  &ASTBuilder::add_bracket, &ASTBuilder::error         , &ASTBuilder::error},
/*WOptd*/   {&ASTBuilder::error         ,  &ASTBuilder::add_operand,  &ASTBuilder::add_bracket, &ASTBuilder::add_uoperation, &ASTBuilder::error}
        };
};