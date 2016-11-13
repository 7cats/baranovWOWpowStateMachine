#include <string>
#include <stack>

#include "astnode.hpp"
#include "expressionparser.hpp"
#include "tokenanalyzer.hpp"

typedef long double lld;

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
        void add_number(lld number);
        void add_var(const std::string &varName);
        void add_binary_operation(const std::string &bOper);
        void add_unary_operation(char uOper);
        void add_function(const std::string &funcName);
        void optimize_tree();
        
        TokenAnalyzer m_tAnalyzer;
        ExpressionParser m_expParser;
        State m_state = WExpression;
        std::stack< std::pair< std::string, int> > m_operationsStack;
        std::stack<ASTNode*> m_operandsStack;
};