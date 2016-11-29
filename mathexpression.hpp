#pragma once

#include <map>

#include <string>
#include "astbuilder.hpp"

typedef long double ld;

class MathExpr : public ASTBuilder
{
    public:
        MathExpr();
        MathExpr(const std::string &expr);
        //MathExpr(const MathExpr &mathExpr);
        
        ld evaluate() const;
        ld operator[](const std::string &varName) const;
        ld& operator[](const std::string &varName);
        void operator<<(const std::string &expr);
        //void dif(std::string var_name);
        
    private:
        std::map<std::string, ld> m_vars;
};