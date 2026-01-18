#include "BitcoinExchange.hpp"
#include <algorithm>
#include <ctime>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>

int main(int argc, char **argv)
{
    try
    {
        BitcoinExchange             btc;
        BitcoinExchange::value_type a("2011-01-01", 5.0f);
        BitcoinExchange::value_type b("2011-01-02", 5.0f);
        BitcoinExchange::_Tp        map;

        map.insert(a);
        map.insert(b);

        // BitcoinExchange::_Tp::iterator c =
        //     std::lower_bound(map.begin(), map.end(), a);
        std::cout << std::boolalpha << (a > b) << std::endl;

        if (argc != 2)
            throw std::runtime_error("could not open file");
        btc.evaluate(argv[1]);
    }
    catch (std::exception &e)
    {
        std::cerr << "Error: " << e.what() << "." << std::endl;
    }
    return 0;
}
