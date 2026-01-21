#include "RPN.hpp"
#include <exception>
#include <iostream>

int main(int argc, char **argv)
{
    try
    {
        RPN rpn(argc, argv);
        rpn.calculate();
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
