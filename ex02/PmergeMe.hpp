#ifndef PMERGE_ME_HPP
#define PMERGE_ME_HPP
#include <cstddef>
#include <deque>
#include <iostream>
#include <ostream>
#include <utility>
#include <vector>

class PmergeMe
{
  public:
    static int _nb_cmp;

    typedef int                               value_type;
    typedef std::deque<value_type>            Deque;
    typedef std::vector<value_type>           Vector;
    typedef std::pair<value_type, value_type> Pair;
    typedef std::vector<Pair>                 VecPair;

    static void sort(int argc, char **argv);

  private:
    PmergeMe();
    PmergeMe(const PmergeMe &other);
    ~PmergeMe();

    PmergeMe &operator=(const PmergeMe &other);

    static void prepare(std::vector<value_type> &vec, int argc, char **argv);
    static void mergeInsertion(std::vector<value_type> &vec, size_t size = 1);
    static void pairwize(Vector &vec, size_t size);
    static void permute(Vector &vec, size_t size);
    static void insertion(std::vector<Vector> &main, std::vector<Vector> &pend);
    static void flat(Vector &vec, std::vector<Vector> &main, size_t size);

    template <typename T>
    static bool greater(const T &a, const T &b);
};

std::ostream &operator<<(std::ostream &out, PmergeMe::Vector &vec);
std::ostream &operator<<(std::ostream &out, std::vector<PmergeMe::Vector> &vec);

template <typename T>
bool PmergeMe::greater(const T &a, const T &b)
{
    PmergeMe::_nb_cmp++;
    return a > b;
}

template <>
inline bool
PmergeMe::greater<PmergeMe::Vector>(const Vector &a, const Vector &b)
{
    PmergeMe::_nb_cmp++;
    if (a.empty() || b.empty())
        throw std::logic_error("Cannot compare empty vectors");
    return *a.rbegin() < *b.rbegin();
}

#endif
