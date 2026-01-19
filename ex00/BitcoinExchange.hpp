#include <ctime>
#include <map>
#include <string>

class BitcoinExchange
{
  public:
    static const char *DB_PATH;

    typedef std::string        Key;
    typedef float              Val;
    typedef std::map<Key, Val> _Tp;
    typedef _Tp::value_type    value_type;

    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange &other);
    ~BitcoinExchange();

    BitcoinExchange &operator=(const BitcoinExchange &other);

    void loadData(const std::string &name);
    void evaluate(int argc, const char **argv);

    static bool       compare(const value_type &a, const value_type &b);
    static value_type readline(const std::string &line, char c);

    static long hashDate(const std::string &str);
    static bool formatDate(std::string &str);

  private:
    _Tp _data;
};
