#include "PmergeMe.hpp"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

int PmergeMe::_nb_cmp = 0;

PmergeMe::PmergeMe()
{
}

PmergeMe::PmergeMe(const PmergeMe &)
{
}

PmergeMe::~PmergeMe()
{
}

PmergeMe &PmergeMe::operator=(const PmergeMe &)
{
    return *this;
}

void PmergeMe::sort(int argc, char **argv)
{

    Vector  main_chain;
    VecPair pairs;

    _nb_cmp = 0;
    prepare(pairs, argc, argv);
    main_chain.reserve(argc - 1);
    std::cout << _nb_cmp << std::endl;

    mergeSort(pairs, pairs.begin(), pairs.end());

    std::cout << std::string(50, '-') << std::endl;
    std::cout << pairs;

    insert(main_chain, pairs);
    std::cout << std::string(50, '-') << std::endl;
    std::cout << main_chain << std::endl;
    std::cout << _nb_cmp << std::endl;
}

void PmergeMe::insert(Vector &chain, VecPair &pairs)
{
    VecPair::iterator first = pairs.begin();
    VecPair::iterator last  = pairs.end();

    int index      = 1;
    int prev_jacob = 1;
    int curr_jacob = 1;

    chain.push_back(first->second);
    while (first != last)
    {
        chain.push_back(first->first);
        ++first;
    }
}

long PmergeMe::jacob(int i)
{
    long value;

    value = 1 << (i + 1);
    if (i % 2 != 0)
        value -= 1;
    else
        value += 1;
    return value / 3;
}

void PmergeMe::prepare(VecPair &vec, int argc, char **argv)
{
    value_type         a[2];
    std::istringstream iss;

    vec.reserve(argc - 1);

    for (int i = 1; i < argc; i++)
    {
        iss.clear();
        iss.str(argv[i]);

        iss >> std::ws >> a[i % 2 == 0];
        if (!iss.eof() || iss.fail() || a[i % 2 == 0] < 0)
            throw std::runtime_error("Error");

        if (i % 2 == 0)
        {
            if (cmp(a[0], a[1]))
                std::swap(a[0], a[1]);
            vec.push_back(Pair(a[0], a[1]));
        }
    }
}

void PmergeMe::mergeSort(
    VecPair &vec, VecPair::iterator first, VecPair::iterator last
)
{
    VecPair           buffer;
    VecPair::iterator mid  = first;
    const long        dist = std::distance(first, last);

    if (std::distance(first, last) <= 1)
        return;

    std::advance(mid, dist / 2);

    mergeSort(vec, first, mid);
    mergeSort(vec, mid, last);

    buffer.reserve(dist);
    std::merge(
        first, mid, mid, last, std::back_inserter(buffer), cmp<PmergeMe::Pair>
    );
    std::copy(buffer.begin(), buffer.end(), first);
}

std::ostream &operator<<(std::ostream &out, PmergeMe::VecPair &vec)
{
    PmergeMe::VecPair::iterator begin;
    PmergeMe::VecPair::iterator end;

    begin = vec.begin();
    end   = vec.end();

    while (begin != end)
    {
        out << begin->first << " - " << begin->second << std::endl;
        begin++;
    }
    return out;
}

std::ostream &operator<<(std::ostream &out, PmergeMe::Vector &vec)
{
    PmergeMe::Vector::iterator begin;
    PmergeMe::Vector::iterator end;

    begin = vec.begin();
    end   = vec.end();

    while (begin != end)
    {
        out << *begin << " -> ";
        begin++;
    }
    return out;
}
