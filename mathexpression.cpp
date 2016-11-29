#include "mathexpression.hpp"

MathExpr::MathExpr()
{
}

MathExpr::MathExpr(const std::string &expr)
{
    build_tree(expr);
}

ld MathExpr::evaluate() const
{
    //считаем значение в дереве и возвращаем результат
    //TODO: продумать архитектуру реализации с переменными, и функциями,
    //и переменными
}

ld MathExpr::operator[](const std::string &varName) const
{
    auto ans = m_vars.find(varName);
    if (ans != m_vars.end()) {
        return ans->second;
    } else {
        std::cout << "Variable with name: " + varName + " not found" << std::endl;
        throw 1;
    }
}

ld& MathExpr::operator[](const std::string &varName)
{
    auto ans = m_vars.find(varName);
    if (ans == m_vars.end()) {
        m_vars[varName] = 0;
    }
    return m_vars.find(varName)->second;
}

void MathExpr::operator<<(const std::string &expr)
{
    build_tree(expr);
}