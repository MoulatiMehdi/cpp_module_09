#include "BitcoinExchange.hpp"
#include <algorithm>
#include <cctype>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <exception>
#include <fstream>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

const char *BitcoinExchange::DB_PATH = "data.csv";

BitcoinExchange::BitcoinExchange() : _data()
{
    loadData(DB_PATH);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
    : _data(other._data)
{
}

BitcoinExchange::~BitcoinExchange()
{
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
    if (this == &other)
        return *this;
    _data = other._data;
    return *this;
}

void BitcoinExchange::loadData(const std::string &filename)
{
    std::ifstream ifs(filename.c_str());
    std::string   line;

    if (!ifs.is_open())
        throw std::runtime_error("could not open file");

    std::getline(ifs, line);
    while (std::getline(ifs, line))
    {
        value_type a = readline(line, ',');
        _data.insert(a);
    }
}

void BitcoinExchange::evaluate(const std::string &filename)
{
    std::ifstream ifs(filename.c_str());
    std::string   line;

    if (!ifs.is_open())
        throw std::runtime_error("could not open file");

    std::getline(ifs, line);
    while (std::getline(ifs, line))
    {
        try
        {
            value_type a = readline(line, '|');
            if (a.second < 0)
                throw std::runtime_error("not a positive number");
            if (a.second > 1000)
                throw std::runtime_error("too large number");
            _Tp::iterator b =
                std::lower_bound(_data.begin(), _data.end(), a, compare);
            if (b == _data.end())
                std::cout << "not found" << std::endl;
            else
                std::cout << a.first << " => " << a.second << " = "
                          << b->second * a.second << " (" << b->first << ")"
                          << std::endl;
        }
        catch (std::exception &e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}

bool BitcoinExchange::compare(const value_type &a, const value_type &b)
{
    std::tm tm1 = {};
    std::tm tm2 = {};
    char    buff1[64];
    char    buff2[64];

    strptime(a.first.c_str(), "%Y-%m-%d", &tm1);
    strptime(b.first.c_str(), "%Y-%m-%d", &tm2);

    strftime(buff1, 64, "%Y-%m-%d", &tm1);
    strftime(buff2, 64, "%Y-%m-%d", &tm2);

    long la = tm1.tm_year * (32 * 31) + tm1.tm_mon * 32 + tm1.tm_mday;
    long lb = tm2.tm_year * (32 * 31) + tm2.tm_mon * 32 + tm2.tm_mday;

    std::cout << std::boolalpha << "is " << buff1 << " before " << buff2 << "? "
              << (la < lb) << std::endl;
    return la < lb && (lb > la);
}

BitcoinExchange::value_type
BitcoinExchange::readline(const std::string &line, char c)
{

    std::istringstream iss(line);
    Key                date;
    Val                value;

    size_t idx = line.find(c);
    if (idx == std::string::npos)
        throw std::runtime_error("bad input => " + line);
    getline(iss, date, c);
    if (!formatDate(date))
        throw std::runtime_error("bad input => " + date);
    iss >> value;
    if (iss.fail())
        throw std::runtime_error("not a number");
    iss >> std::ws;
    if (!iss.eof())
        throw std::runtime_error("bad input => " + iss.str());
    return value_type(date, value);
}

bool BitcoinExchange::formatDate(Key &str)
{
    std::tm tm_1 = {};
    std::tm tm_2 = {};
    char    str1[64];
    char    str2[64];
    char   *p;

    p = strptime(str.c_str(), "%t%Y-%m-%d%t", &tm_1);
    if (p == NULL || *p != '\0')
        return false;
    strftime(str1, 64, "%Y-%m-%d", &tm_1);
    str  = str1;
    tm_2 = tm_1;
    if (mktime(&tm_2) == -1)
        return false;
    strftime(str2, 64, "%Y-%m-%d", &tm_2);
    return str == str2;
}
