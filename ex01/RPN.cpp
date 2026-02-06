#include "RPN.hpp"
#include <cctype>
#include <cstring>
#include <stdexcept>
#include <string>

const std::string RPN::OPERATORS = "/*-+";

RPN::RPN()
{
}

RPN::RPN(const RPN &)
{
}

RPN::~RPN()
{
}

RPN &RPN::operator=(const RPN &)
{
    return *this;
}

bool RPN::isOperator(char c)
{
    return OPERATORS.find(c) != std::string::npos;
}

void RPN::execute(Container &s, char op)
{
    long lhs;
    long rhs;

    if (s.size() < 2)
        throw std::runtime_error("Error");

    rhs = s.top();
    s.pop();
    lhs = s.top();
    s.pop();

    switch (op)
    {
        case '-':
            lhs -= rhs;
            break;
        case '+':
            lhs += rhs;
            break;
        case '*':
            lhs *= rhs;
            break;
        case '/':
            lhs /= rhs;
            break;
        default:
            throw std::runtime_error("Error");
    }
    s.push(lhs);
}

long RPN::calculate(int argc, char **argv)
{
    if (argc != 2)
        throw std::runtime_error("Error");

    Container                   n;
    const std::string           expr  = argv[1];
    std::string::const_iterator first = expr.begin();
    std::string::const_iterator last  = expr.end();

    if (!std::isdigit(*first))
        throw std::runtime_error("Error");

    n.push(*(first++) - '0');
    while (first != last)
    {
        char c = *(first++);
        if (c != ' ' || first == last)
            throw std::runtime_error("Error");

        c = *(first++);
        if (std::isdigit(c))
            n.push(c - '0');
        else if (isOperator(c))
            execute(n, c);
        else
            throw std::runtime_error("Error");
    }

    if (n.size() != 1)
        throw std::runtime_error("Error");
    return n.top();
}
