#include "BitcoinExchange.hpp"
#include <exception>
#include <iostream>

int main(int argc, const char **argv)
{
    try
    {
        BitcoinExchange btc;
        btc.evaluate(argc, argv);
    }
    catch (std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}
