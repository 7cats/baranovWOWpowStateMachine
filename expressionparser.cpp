#include "expressionparser.hpp"

ExpressionParser::ExpressionParser()
{
}

ExpressionParser::ExpressionParser(const std::string &expr)
    : m_expr(expr)
{
}

ExpressionParser& ExpressionParser::operator>>(std::string &expr)
{
    expr = read();
    return *this;
}

void ExpressionParser::operator<<(const std::string &expr)
{
    m_expr = expr;
    m_indx = 0;
}

std::string ExpressionParser::read()
{
    while (m_expr[m_indx] == ' ') {
        m_indx++;
    }
    
    std::stringstream ss;
    if ((int)m_expr.size() == m_indx) {
        return std::string(1, '\n');
    } else if (m_expr[m_indx] == '+' || m_expr[m_indx] == '-'
        || m_expr[m_indx] == '*' || m_expr[m_indx] == '/'
        || m_expr[m_indx] == '(' || m_expr[m_indx] == ')' || m_expr[m_indx] == '^')
    {
        return std::string(1, m_expr[m_indx++]);
    } else if (m_expr[m_indx] >= '0' && m_expr[m_indx] <= '9') {
        //read number with .
        while (((m_expr[m_indx] >= '0' && m_expr[m_indx] <= '9' )
            || m_expr[m_indx] == '.') &&  (int)m_expr.size() > m_indx)
        {
            ss << m_expr[m_indx];
            ++m_indx;
        }
    } else {
        //read var name, func name or trash
        while (m_expr[m_indx] != ' ' && m_expr[m_indx] != '+' && m_expr[m_indx] != '-'
            && m_expr[m_indx] != '*' && m_expr[m_indx] != '/'
            && m_expr[m_indx] != '(' && m_expr[m_indx] != ')' && m_expr[m_indx] != '^'
            && (int)m_expr.size() > m_indx)
        {
            ss << m_expr[m_indx];
            ++m_indx;
        }
    }
    return ss.str();
}

int ExpressionParser::get_index() const
{
    return m_indx;
}