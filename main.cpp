
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>
#include <utility>
#include <random>

size_t constexpr max_elmts(10);

enum Style {
  PROMPT, RANDOM, FIXED,
};

inline
std::vector<int> & collect(std::vector<int> &, Style style = PROMPT);
inline
void show(std::vector<int> const &);
void do_it_with_an_array(size_t len, int * ap);

/*
 *  MARK: main()
 */
int main(int argc, char const * argv[]) {

  Style style;
  int choice(0);
  while (choice == 0) {
    std::cout << "Menu:\n"
              << "  1: Prompt for input\n"
              << "  2: Use fixed input\n"
              << "  3: Use random input\n";
    std::cout.flush();
    std::cin >> choice;
    switch (choice) {
    case 1:
      style = PROMPT;
      break;
    case 2:
      style = FIXED;
      break;
    case 3:
      style = RANDOM;
      break;
    default:
      choice = 0;
      break;
    }
  }

  std::vector<int> av(max_elmts);
  av = collect(av, style);
  show(av);

  auto sum = std::accumulate(av.cbegin(), av.cend(), 0);
  auto avg = static_cast<double>(sum) / av.size();

  auto ip = [& avg](auto n_) { return n_ > static_cast<int>(avg); };

  auto nct = std::count_if(av.cbegin(), av.cend(), ip);

  std::cout << "sum: " << sum << '\n'
            << "average: " << avg << '\n'
            << "elements .GT. average: " << nct << '\n'
            << std::endl;

  std::vector<int> rv(nct);
  std::copy_if(av.cbegin(),av.cend(), rv.begin(), ip);
  std::sort(rv.begin(), rv.end(), std::greater_equal<>());
  show(rv);

  auto rsum = std::accumulate(rv.cbegin(), rv.cend(), 0);
  std::cout << "sum of results: " << rsum << std::endl;
  std::cout << std::endl;

  do_it_with_an_array(av.size(), av.data());

  return 0;
}

/*
 *  MARK: do_it_with_an_array()
 */
void do_it_with_an_array(size_t len, int * ap) {
  int aa[max_elmts] { 0, };
  for (size_t i_(0); i_ < (len < max_elmts ? len : max_elmts); ++i_) {
    aa[i_] = ap[i_];
  }

  auto sum = std::accumulate(std::cbegin(aa), std::cend(aa), 0);
  auto avg = static_cast<double>(sum) / max_elmts;

  auto ip = [& avg](auto n_) { return n_ > static_cast<int>(avg); };

  auto nct = std::count_if(std::cbegin(aa), std::cend(aa), ip);

  show(std::vector<int>(std::cbegin(aa), std::cend(aa)));
  std::cout << "sum: " << sum << '\n'
            << "average: " << avg << '\n'
            << "elements .GT. average: " << nct << '\n'
            << std::endl;

  std::vector<int> rv(nct);
  std::copy_if(std::cbegin(aa),std::cend(aa), rv.begin(), ip);
  std::sort(rv.begin(), rv.end(), std::greater_equal<>());
  show(rv);

  auto rsum = std::accumulate(rv.cbegin(), rv.cend(), 0);
  std::cout << "sum of results: " << rsum << std::endl;
  std::cout << std::endl;
}

/*
 *  MARK: collect()
 */
inline
std::vector<int> & collect(std::vector<int> & av, Style style) {
  size_t av_s = av.size();

  switch (style) {
  case RANDOM:
    {
      std::random_device rd; //used to obtain a seed for the prng
      std::mt19937 prng(rd()); //mersenne_twister prng seeded w. rd()
      std::uniform_int_distribution<> distrib(100, 9'999);
      std::vector<int> nr(av.size());
      std::iota(nr.begin(), nr.end(), 0);
      for (auto ix : nr) {
        int rn(0);
        do {
          rn = distrib(prng);
        } while (rn % 2 == 0);
        av[ix] = rn;
      }
    }
    break;

  case FIXED:
    {
      std::vector<int> fx {
        11, 13, 15, 17, 19, 21, 23, 25, 27, 29,
      };
      av.clear();
      std::move(fx.begin(), fx.end(), std::back_inserter(av));
    }
    break;

  case PROMPT:
  default:
    {
      int val(0);
      for (size_t ct(0); ct < av_s; ++ct) {
        val = 0;
        while (val % 2 == 0) {
          std::cout << "element " << std::setw(2) << ct + 1 << ": ";
          std::cout.flush();
          std::cin >> val;
          av[ct] = val;
        }
      }
      std::cout << std::endl;
    }
    break;
  }

  return av;
}

/*
 *  MARK: show()
 */
inline
void show(std::vector<int> const & av) {
  auto cc(0);
  auto constexpr cc_max(5);
  auto vp = [& cc](auto n_) {
    std::cout << std::setw(10) << n_
              << ((++cc % cc_max == 0) ? "\n" : "");
  };
  cc = 0;
  std::for_each(av.cbegin(), av.cend(), vp);
  std::cout << std::endl;
}
