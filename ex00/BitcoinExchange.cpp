#include "BitcoinExchange.hpp"
#include <algorithm>
#include <fstream>
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
        throw std::runtime_error("could not open file.");

    std::getline(ifs, line);
    while (std::getline(ifs, line))
    {
        value_type a = readline(line, ',');
        _data.insert(a);
    }
}

void BitcoinExchange::evaluate(int argc, const char **argv)
{
    std::ifstream ifs(argv[1]);
    std::string   line;

    if (_data.empty())
        throw std::runtime_error("database empty");
    if (argc != 2)
        throw std::runtime_error("could not open file");
    if (!ifs.is_open())
        throw std::runtime_error("could not open file.");

    std::getline(ifs, line);
    while (std::getline(ifs, line))
    {
        try
        {
            value_type a = readline(line, '|');
            if (a.second < 0)
                throw std::runtime_error("not a positive number.");
            if (a.second > 1000)
                throw std::runtime_error("too large a number.");

            _Tp::iterator b =
                std::lower_bound(_data.begin(), _data.end(), a, compare);
            if (b != _data.begin() && (b == _data.end() || a.first != b->first))
                --b;
            std::cout << a.first << " => " << a.second;
            std::cout << " = " << b->second * a.second << std::endl;
        }
        catch (std::exception &e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}

bool BitcoinExchange::compare(const value_type &a, const value_type &b)
{
    return hashDate(a.first) < hashDate(b.first);
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

long BitcoinExchange::hashDate(const std::string &str)
{

    std::tm tm1 = {};
    char    buff1[64];

    strptime(str.c_str(), "%Y-%m-%d", &tm1);
    strftime(buff1, 64, "%Y-%m-%d", &tm1);

    return tm1.tm_year * 10000 + tm1.tm_mon * 100 + tm1.tm_mday;
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
