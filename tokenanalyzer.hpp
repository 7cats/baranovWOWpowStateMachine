#include <string>

enum TokenType {
    number, var, func, trash, operation
};

class TokenAnalyzer 
{
    public:
        TokenType get_token_type(const std::string &token);
};