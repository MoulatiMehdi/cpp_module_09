#include "PmergeMe.hpp"
#include <algorithm>
#include <cmath>
#include <ctime>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <sys/time.h>
#include <vector>

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

static time_t now_us()
{
    timeval tv;
    gettimeofday(&tv, 0);
    return tv.tv_sec * 1000000LL + tv.tv_usec;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &)
{
    return *this;
}

void PmergeMe::sort(int argc, char **argv)
{
    Vector    a;
    Deque     b;
    long long start;
    long long end;

    _nb_cmp = 0;
    prepare(a, argc, argv);

    b.insert(b.end(), a.begin(), a.end());

    std::cout << "Before: " << a << std::endl;
    start = now_us();
    mergeInsertion(a);
    end = now_us();
    std::cout << "After:  " << a << std::endl;

    std::cout << "Time to process a range of " << a.size()
              << " elements with std::vector : " << end - start << " us"
              << std::endl;

    start = now_us();
    mergeInsertion(b);
    end = now_us();

    std::cout << "Time to process a range of " << b.size()
              << " elements with std::deque  : " << end - start << " us"
              << std::endl;
}

void PmergeMe::prepare(Vector &vec, int argc, char **argv)
{
    std::istringstream iss;
    value_type         a;

    if (argc == 1)
        throw std::runtime_error("Error");
    for (int i = 1; i < argc; i++)
    {
        iss.clear();
        iss.str(argv[i]);

        iss >> std::noskipws >> a;
        if (!iss.eof() || iss.fail() || a < 0)
            throw std::runtime_error("Error");
        vec.push_back(a);
    }
}

void PmergeMe::mergeInsertion(Vector &vec, size_t size)
{
    if (vec.size() / size < 2)
        return;
    pairwize(vec, size);
    mergeInsertion(vec, size * 2);
    permute(vec, size);
}

void PmergeMe::pairwize(Vector &vec, size_t size)
{
    Vector::iterator first;
    Vector::iterator last;

    for (size_t i = size; i < vec.size() - size + 1; i += 2 * size)
    {
        first = vec.begin() + i - size;
        last  = vec.begin() + i;

        if (greater(vec[i - 1], vec[size + i - 1]))
            std::swap_ranges(first, last, last);
    }
}

void PmergeMe::permute(Vector &vec, size_t size)
{
    if (vec.size() / size < 2)
        return;
    std::vector<Vector> main_chain;
    std::vector<Vector> pend;

    for (size_t i = 0; i <= vec.size() - size * 2; i += size * 2)
    {
        Vector::iterator mid  = vec.begin() + i + size;
        Vector::iterator last = vec.begin() + i + 2 * size;

        main_chain.push_back(Vector(mid, last));
    }
    for (size_t i = 0; i <= vec.size() - size; i += size * 2)
    {
        Vector::iterator first = vec.begin() + i;
        Vector::iterator mid   = vec.begin() + i + size;

        pend.push_back(Vector(first, mid));
    }

    insertion(main_chain, pend);
    flat(vec, main_chain, size);
}

void PmergeMe::flat(Vector &vec, std::vector<Vector> &main_chain, size_t size)
{
    Vector tmp;

    std::vector<Vector>::iterator first = main_chain.begin();
    while (first != main_chain.end())
    {
        tmp.insert(tmp.end(), first->begin(), first->end());
        first++;
    }
    if (vec.size() % size != 0)
        tmp.insert(tmp.end(), vec.end() - vec.size() % size, vec.end());
    std::swap(tmp, vec);
}

void PmergeMe::insertion(
    std::vector<Vector> &main_chain, std::vector<Vector> &pend
)
{
    size_t k      = 2;
    size_t prev_t = 1;
    size_t curr_t = 1;
    size_t added  = 0;

    main_chain.insert(main_chain.begin(), pend[0]);
    while (prev_t < pend.size())
    {
        prev_t       = curr_t;
        curr_t       = (1 << k) - prev_t;
        size_t min_t = std::min(curr_t, pend.size());
        for (size_t i = min_t; i > prev_t; i--)
        {
            std::vector<Vector>::iterator it = std::lower_bound(
                main_chain.begin(),
                main_chain.begin() + i + added,
                pend[i - 1],
                static_cast<bool (*)(const Vector &a, const Vector &b)>(greater)
            );
            main_chain.insert(it, pend[i - 1]);
            added++;
        }
        k++;
    }
}

void PmergeMe::mergeInsertion(Deque &vec, size_t size)
{
    if (vec.size() / size < 2)
        return;
    pairwize(vec, size);
    mergeInsertion(vec, size * 2);
    permute(vec, size);
}

void PmergeMe::pairwize(Deque &vec, size_t size)
{
    Deque::iterator first;
    Deque::iterator last;

    for (size_t i = size; i < vec.size() - size + 1; i += 2 * size)
    {
        first = vec.begin() + i - size;
        last  = vec.begin() + i;

        if (greater(vec[i - 1], vec[size + i - 1]))
            std::swap_ranges(first, last, last);
    }
}

void PmergeMe::permute(Deque &vec, size_t size)
{
    if (vec.size() / size < 2)
        return;
    std::deque<Deque> main_chain;
    std::deque<Deque> pend;

    for (size_t i = 0; i <= vec.size() - size * 2; i += size * 2)
    {
        Deque::iterator mid  = vec.begin() + i + size;
        Deque::iterator last = vec.begin() + i + 2 * size;

        main_chain.push_back(Deque(mid, last));
    }
    for (size_t i = 0; i <= vec.size() - size; i += size * 2)
    {
        Deque::iterator first = vec.begin() + i;
        Deque::iterator mid   = vec.begin() + i + size;

        pend.push_back(Deque(first, mid));
    }

    insertion(main_chain, pend);
    flat(vec, main_chain, size);
}

void PmergeMe::flat(Deque &vec, std::deque<Deque> &main_chain, size_t size)
{
    Deque tmp;

    std::deque<Deque>::iterator first = main_chain.begin();
    while (first != main_chain.end())
    {
        tmp.insert(tmp.end(), first->begin(), first->end());
        first++;
    }
    if (vec.size() % size != 0)
        tmp.insert(tmp.end(), vec.end() - vec.size() % size, vec.end());
    std::swap(tmp, vec);
}

void PmergeMe::insertion(std::deque<Deque> &main_chain, std::deque<Deque> &pend)
{
    size_t k      = 2;
    size_t prev_t = 1;
    size_t curr_t = 1;
    size_t added  = 0;

    main_chain.insert(main_chain.begin(), pend[0]);
    while (prev_t < pend.size())
    {
        prev_t       = curr_t;
        curr_t       = (1 << k) - prev_t;
        size_t min_t = std::min(curr_t, pend.size());
        for (size_t i = min_t; i > prev_t; i--)
        {
            std::deque<Deque>::iterator it = std::lower_bound(
                main_chain.begin(),
                main_chain.begin() + i + added,
                pend[i - 1],
                static_cast<bool (*)(const Deque &a, const Deque &b)>(greater)
            );
            main_chain.insert(it, pend[i - 1]);
            added++;
        }
        k++;
    }
}

std::ostream &operator<<(std::ostream &out, const PmergeMe::Vector &vec)
{
    PmergeMe::Vector::const_iterator begin;
    PmergeMe::Vector::const_iterator end;

    begin = vec.begin();
    end   = vec.end();

    while (begin != end)
    {
        if (begin != vec.begin())
            out << " ";
        out << *begin;
        begin++;
    }
    return out;
}

std::ostream &operator<<(std::ostream &out, const PmergeMe::Deque &vec)
{
    PmergeMe::Deque::const_iterator begin;
    PmergeMe::Deque::const_iterator end;

    begin = vec.begin();
    end   = vec.end();

    while (begin != end)
    {
        if (begin != vec.begin())
            out << " ";
        out << *begin;
        begin++;
    }
    return out;
}

bool PmergeMe::greater(const value_type &a, const value_type &b)
{
    PmergeMe::_nb_cmp++;
    return a > b;
}

bool PmergeMe::greater(const Vector &a, const Vector &b)
{
    PmergeMe::_nb_cmp++;
    return *a.rbegin() < *b.rbegin();
}

bool PmergeMe::greater(const Deque &a, const Deque &b)
{
    PmergeMe::_nb_cmp++;
    return *a.rbegin() < *b.rbegin();
}
