#include <string>

enum TokenAnalyzerRes {
    number, var, func, trash, operation
};

class TokenAnalyzer 
{
    public:
        TokenAnalyzerRes get_token_type(const std::string &token);
};