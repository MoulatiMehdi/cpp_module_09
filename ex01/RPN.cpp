#include "RPN.hpp"
#include <cctype>
#include <stdexcept>
#include <string>

const int         RPN::EOI    = -1;
const std::string VALID_CHARS = "0123456789/*-+";

RPN::RPN()
{
}

RPN::RPN(const std::string &str)
{
    std::string::const_iterator first = str.begin();
    std::string::const_iterator last  = str.end();

    while (first < last)
    {
        if (isValid(*first))
            _data.push_front(*first);
        first++;
        if (*first != ' ' || *first != '\0')
            throw std::runtime_error("");
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

int RPN::next()
{
    if (_data.empty())
        return EOI;
    char c = _data.front();
    _data.pop_front();
    return c;
}

bool RPN::isValid(char c)
{
    return VALID_CHARS.find(c) != std::string::npos;
}
