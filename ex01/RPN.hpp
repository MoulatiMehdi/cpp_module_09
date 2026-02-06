#include <stack>
#include <string>

class RPN
{
  public:
    typedef std::stack<long> Container;

    static long calculate(int argc, char **argv);

  private:
    static const std::string OPERATORS;

    RPN();
    RPN(const RPN &other);
    ~RPN();
    RPN &operator=(const RPN &other);

    static bool isOperator(char c);
    static void execute(Container &s, char op);
};
