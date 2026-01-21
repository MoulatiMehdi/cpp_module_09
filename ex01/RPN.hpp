#include <stack>
#include <string>

class RPN
{
  public:
    typedef std::stack<int> _Tp;

    static const char        EOI;
    static const std::string OPERATORS;

    RPN();
    RPN(int argc, char **argv);
    RPN(const RPN &other);
    ~RPN();
    RPN &operator=(const RPN &other);

    void calculate();
    bool isValid(char c);
    bool isOperator(char c);
    char  next();

  private:
    _Tp  _data;
    long _result;
};
