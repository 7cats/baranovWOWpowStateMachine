#include <string>

class ExpressionParser 
{
    public:
        ExpressionParser();
        ExpressionParser(const std::string &expr);
        
        ExpressionParser& operator>>(const std::string &expr);
        void operator<<(const std::string &expr);
    
    private:
        std::string read(); 
        std::string expr;
        int indx;
};