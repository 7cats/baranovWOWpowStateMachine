#include <string>
#include <vector>

struct ASTNode 
{
    ASTNode(const std::string &token, ASTNode* const lChild = 0, ASTNode* const rChild = 0);
    
    std::string m_token;
    std::vector<ASTNode*> m_children;
};