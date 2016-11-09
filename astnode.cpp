#include "astnode.hpp"

ASTNode::ASTNode(const std::string &token, ASTNode* const lChild, ASTNode* const rChild) 
    : m_token(token)
{
    if (lChild != 0) {
        m_children.push_back(lChild);
    }    
    if (rChild != 0) {
        m_children.push_back(rChild);
    }
}