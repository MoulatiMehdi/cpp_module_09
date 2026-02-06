#include "PmergeMe.hpp"
#include <exception>
#include <iostream>

int main(int argc, char *argv[])
{
    try
    {
        PmergeMe::sort(argc, argv);
    }
    catch (std::exception &e)
    {
        std::cerr << "Error" << std::endl;
    }

    return 0;
}
