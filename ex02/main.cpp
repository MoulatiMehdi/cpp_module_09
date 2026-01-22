#include "PmergeMe.hpp"
#include <exception>
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    try
    {
        PmergeMe::sort(argc, argv);
        std::cout << std::string(50, '-') << std::endl;
        for (int i = 0; i < 5; i++)
        {
            std::cout << PmergeMe::jacob(i) << std::endl;
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "Error" << std::endl;
    }

    return 0;
}
