#include <map>

#include "astbuilder.hpp"

typedef long double lld;

class MathExpr : public ASTBuilder
{
    public:
        MathExpr();
        MathExpr(const std::string &expr);
        //MathExpr(const MathExpr &mathExpr);
        
        lld evaluate() const;
        lld operator[](std::string varName) const;
        lld& operator[](std::string varName);
        void operator<<(std::string expr);
        //void dif(std::string var_name);
        
        
    private:
        void set_variable(std::string varName, lld varVal);
        lld get_value(std::string varName) const;
    
        std::map<std::string, lld> m_vars;
};