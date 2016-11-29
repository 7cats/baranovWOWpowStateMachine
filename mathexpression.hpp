#pragma once
#define _USE_MATH_DEFINES

#include <map>
#include <string>
#include <cmath>
#include <exception>
#include "astnode.hpp"
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
        ld eval(const ASTNode &astnode) const;
        std::map<std::string, ld> m_vars;
};