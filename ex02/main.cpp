#include "PmergeMe.hpp"
#include <exception>
#include <iostream>

int main(int argc, char *argv[])
{
    try
    {
        PmergeMe::Vector a;
        PmergeMe::Deque  b;

        PmergeMe::prepare(a, argc, argv);
        b.assign(a.begin(), a.end());

        PmergeMe::sort(a);
        PmergeMe::sort(b);
    }
    catch (std::exception &e)
    {
        std::cerr << "Error" << std::endl;
    }

    return 0;
}
