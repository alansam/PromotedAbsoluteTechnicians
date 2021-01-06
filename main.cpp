
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>

size_t constexpr max_elmts(10);

inline
std::vector<int> & collect(std::vector<int> &);
inline
void show(std::vector<int> const &);

void do_it_with_an_array(size_t len, int * ap);

/*
 *  MARK: main()
 */
int main(int argc, char const * argv[]) {
  std::vector<int> av(max_elmts);
  av = collect(av);
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
std::vector<int> & collect(std::vector<int> & av) {
  size_t av_s = av.size();
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
