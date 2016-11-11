#include <string>
#include <sstream>

class ExpressionParser 
{
    public:
        ExpressionParser();
        ExpressionParser(const std::string &expr);
        
        ExpressionParser& operator>>(std::string &expr);
        void operator<<(const std::string &expr);
    
    private:
        std::string read(); 
        std::string m_expr;
        int m_indx = 0;
};