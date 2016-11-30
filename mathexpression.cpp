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
    return eval(*m_root);
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

ld MathExpr::eval(const ASTNode &astnode) const
{
    const std::string& token = astnode.m_token;
    TokenType ttype = m_tAnalyzer.get_token_type(token);
    if (ttype == TAoperation) {
        assert(token.size() == 1);
        switch(token[0]) {
        case '+':
            return eval(*astnode.m_children[0]) + eval(*astnode.m_children[1]);
            break;
        //unary -
        case -'-':
            return -eval(*astnode.m_children[0]);
            break;
        case '-':
            return eval(*astnode.m_children[0]) - eval(*astnode.m_children[1]);
            break;
        case '*':
            return eval(*astnode.m_children[0]) * eval(*astnode.m_children[1]);
            break;
        case '/':
            return eval(*astnode.m_children[0]) / eval((*astnode.m_children[1]));
            break;
        case '^':
            return powl(eval(*astnode.m_children[0]), eval(*astnode.m_children[1]));
            break;
        default:
            std::cerr << "Invalid operation in 69" << std::endl;
            throw 1;
            break;
        }
    } else if (ttype == TAnumber) {
        return std::stold(token);
    } else if (ttype == TAvar) {
        auto sRes = m_vars.find(token);
        if (sRes == m_vars.end()) {
            std::cerr << "Invalid var in 77" << std::endl;
            throw 1;
        }
        return sRes->second;
    } else if (ttype == TAfunc) {
        //TODO: fix it
        assert(astnode.m_children.size() == 1);

        ld number = eval(*astnode.m_children[0]);
        number = fmod(number, 360);
        if (number > 270) {
            number -= 360;
        } else if (number > 90) {
            number = 180 - number;
        }

        if (token == "sin") {            
            return std::sin(number * M_PI / 180.0);
        } else if (token == "cos") {
            return std::cos(number * M_PI / 180.0);
        } else if (token == "tg") {
            return std::tan(number * M_PI / 180.0);
        } else {
            std::cerr << "Invalid func in 90" << std::endl;
            throw 1;
        }
    } else {
        std::cerr << "Wrong type in 93" << std::endl;
        throw "Wrong type in 93";
    }
}
