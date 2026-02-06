#ifndef PMERGE_ME_HPP
#define PMERGE_ME_HPP
#include <cstddef>
#include <deque>
#include <iostream>
#include <vector>

class PmergeMe
{
  public:
    typedef int                     value_type;
    typedef std::deque<value_type>  Deque;
    typedef std::vector<value_type> Vector;
    static void                     sort(int argc, char **argv);

  private:
    static int _nb_cmp;

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

    static void mergeInsertion(std::deque<value_type> &vec, size_t size = 1);
    static void pairwize(Deque &vec, size_t size);
    static void permute(Deque &vec, size_t size);
    static void insertion(std::deque<Deque> &main, std::deque<Deque> &pend);
    static void flat(Deque &vec, std::deque<Deque> &main, size_t size);

    static bool greater(const value_type &a, const value_type &b);
    static bool greater(const Vector &a, const Vector &b);
    static bool greater(const Deque &a, const Deque &b);
};

std::ostream &operator<<(std::ostream &out, const PmergeMe::Vector &vec);
std::ostream &operator<<(std::ostream &out, const PmergeMe::Deque &vec);

#endif
