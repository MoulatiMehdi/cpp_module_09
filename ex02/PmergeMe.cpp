#include "PmergeMe.hpp"
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
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

PmergeMe &PmergeMe::operator=(const PmergeMe &)
{
    return *this;
}

void PmergeMe::sort(int argc, char **argv)
{
    std::vector<value_type> a;

    _nb_cmp = 0;
    prepare(a, argc, argv);
    std::cout << a << std::endl;
    mergeInsertion(a);
    std::cout << a << std::endl;
    std::cout << "nb of comparision : " << _nb_cmp << std::endl;
}

void PmergeMe::prepare(std::vector<value_type> &vec, int argc, char **argv)
{
    std::istringstream iss;
    value_type         a;

    vec.reserve(argc - 1);
    for (int i = 1; i < argc; i++)
    {
        iss.clear();
        iss.str(argv[i]);

        iss >> std::ws >> a;
        if (!iss.eof() || iss.fail() || a < 0)
            throw std::runtime_error("Error");
        vec.push_back(a);
    }
}

void PmergeMe::mergeInsertion(Vector &vec, size_t size)
{
    std::cout << "merge " << size << std::endl;
    if (vec.size() / size < 2)
        return;
    pairwize(vec, size);
    mergeInsertion(vec, size * 2);
    permute(vec, size);
}

void PmergeMe::pairwize(Vector &vec, size_t size)
{
    std::cout << "pairwize " << size << std::endl;
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
    std::cout << "permute" << size << std::endl;
    if (vec.size() / size < 2)
        return;
    std::vector<Vector> main;
    std::vector<Vector> pend;

    main.reserve(vec.size() / size + 1);
    pend.reserve(vec.size() / 2);

    for (size_t i = 0; i <= vec.size() - size * 2; i += size * 2)
    {
        Vector::iterator mid  = vec.begin() + i + size;
        Vector::iterator last = vec.begin() + i + 2 * size;

        main.push_back(Vector(mid, last));
    }
    for (size_t i = 0; i <= vec.size() - size; i += size * 2)
    {
        Vector::iterator first = vec.begin() + i;
        Vector::iterator mid   = vec.begin() + i + size;

        pend.push_back(Vector(first, mid));
    }
    Vector res(vec.end() - vec.size() % size, vec.end());

    insertion(main, pend);
    flat(vec, main, size);
}

void PmergeMe::flat(Vector &vec, std::vector<Vector> &main, size_t size)
{
    Vector tmp;

    tmp.reserve(vec.size());
    std::vector<Vector>::iterator first = main.begin();
    while (first != main.end())
    {
        tmp.insert(tmp.end(), first->begin(), first->end());
        first++;
    }
    if (vec.size() % size != 0)
        tmp.insert(tmp.end(), vec.end() - vec.size() % size, vec.end());
    std::swap(tmp, vec);
}

void PmergeMe::insertion(std::vector<Vector> &main, std::vector<Vector> &pend)
{
    size_t k      = 2;
    size_t prev_t = 1;
    size_t curr_t = 1;
    size_t added  = 0;

    main.insert(main.begin(), pend[0]);
    while (prev_t < pend.size())
    {
        prev_t       = curr_t;
        curr_t       = (1 << k) - prev_t;
        size_t min_t = std::min(curr_t, pend.size());
        for (size_t i = min_t; i > prev_t; i--)
        {
            std::vector<Vector>::iterator it = std::lower_bound(
                main.begin(),
                main.begin() + i + added,
                pend[i - 1],
                greater<Vector>
            );
            main.insert(it, pend[i - 1]);
            added++;
        }
        k++;
    }
}

std::ostream &operator<<(std::ostream &out, PmergeMe::Vector &vec)
{
    PmergeMe::Vector::iterator begin;
    PmergeMe::Vector::iterator end;

    begin = vec.begin();
    end   = vec.end();

    while (begin != end)
    {
        if (begin != vec.begin())
            out << " ";
        out << std::setw(2) << *begin;
        begin++;
    }
    return out;
}

std::ostream &operator<<(std::ostream &out, std::vector<PmergeMe::Vector> &vec)
{
    std::vector<PmergeMe::Vector>::iterator begin;
    std::vector<PmergeMe::Vector>::iterator end;

    begin = vec.begin();
    end   = vec.end();

    while (begin != end)
    {
        if (begin != vec.begin())
            out << "\033[1;31m | \033[0m";
        out << *begin;
        begin++;
    }
    return out;
}
