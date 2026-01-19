
#include <forward_list>
#include <string>

class RPN
{
  public:
    typedef std::forward_list<char> _Tp;

    static const int         EOI;
    static const std::string VALID_CHARS;

    RPN();
    RPN(const std::string &str);
    RPN(const RPN &other);
    ~RPN();
    RPN &operator=(const RPN &other);

    int  next();
    bool isValid(char c);

  private:
    _Tp _data;
};
