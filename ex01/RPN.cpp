#include "RPN.hpp"
#include <cctype>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>

const char        RPN::EOI       = -1;
const std::string RPN::OPERATORS = "/*-+";

RPN::RPN()
{
}

RPN::RPN(int argc, char **argv)
{
    if (argc != 2)
        throw std::runtime_error("Error");

    std::string                   str   = argv[1];
    std::string::reverse_iterator first = str.rbegin();
    std::string::reverse_iterator last  = str.rend();

    while (1)
    {
        if (last == first || !isValid(*first))
            throw std::runtime_error("Error");
        _data.push(*first);
        ++first;
        if (last == first)
            break;
        if (*first != ' ')
            throw std::runtime_error("Error");
        first++;
    }
}

RPN::RPN(const RPN &other)
{
    _data = other._data;
}

RPN::~RPN()
{
}

RPN &RPN::operator=(const RPN &other)
{
    if (&other == this)
        return *this;
    _data = other._data;
    return *this;
}

bool RPN::isValid(char c)
{
    return isOperator(c) || std::isdigit(c);
}

bool RPN::isOperator(char c)
{
    return OPERATORS.find(c) != std::string::npos;
}

char RPN::next()
{
    int c;

    if (_data.empty())
        return EOI;
    c = _data.top();
    _data.pop();
    return c;
}

void RPN::calculate()
{
    char rh;
    char op;

    _result = next();
    if (!std::isdigit(_result))
        throw std::runtime_error("Error");
    _result -= '0';
    while (!_data.empty())
    {
        rh = next();
        op = next();

        if (!std::isdigit(rh))
            throw std::runtime_error("Error");
        rh -= '0';
        switch (op)
        {
            case '-':
                _result -= rh;
                break;
            case '+':
                _result += rh;
                break;
            case '*':
                _result *= rh;
                break;
            case '/':
                _result /= rh;
                break;
            default:
                throw std::runtime_error("Error");
        }
    }
    std::cout << _result << std::endl;
}
