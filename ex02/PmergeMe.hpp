#include <deque>
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
    static long jacob(int i);

    PmergeMe();

  private:
    PmergeMe(const PmergeMe &other);
    ~PmergeMe();

    PmergeMe &operator=(const PmergeMe &other);

    void static mergeSort(
        VecPair &vec, VecPair::iterator first, VecPair::iterator last
    );
    static void insert(Vector &chain, VecPair &pairs);
    static void prepare(VecPair &vec, int argc, char **argv);

    template <typename T>
    static bool cmp(const T &a, const T &b);
};

std::ostream &operator<<(std::ostream &out, PmergeMe::VecPair &vec);
std::ostream &operator<<(std::ostream &out, PmergeMe::Vector &vec);

template <typename T>
bool PmergeMe::cmp(const T &a, const T &b)
{
    PmergeMe::_nb_cmp++;
    return a < b;
}

template <>
inline bool
PmergeMe::cmp<PmergeMe::Pair>(const PmergeMe::Pair &a, const PmergeMe::Pair &b)
{
    PmergeMe::_nb_cmp++;
    return a.first < b.first;
}
