#include "RPN.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    try
    {
        std::cout << RPN::calculate(argc, argv) << std::endl;
    }
    catch (...)
    {
        std::cerr << "Error" << std::endl;
    }
    return 0;
}
