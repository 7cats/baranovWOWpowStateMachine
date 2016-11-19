#pragma once

#include <string>
#include <sstream>

#define EXPRPARSEREOF (std::string(1, '\n'))

class ExpressionParser 
{
    public:
        ExpressionParser();
        ExpressionParser(const std::string &expr);
        
        ExpressionParser& operator>>(std::string &expr);
        void operator<<(const std::string &expr);
        int get_index() const;

    private:
        std::string read(); 
        std::string m_expr;
        int m_indx = 0;
};