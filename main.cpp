
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
void show(std::vector<int> &);

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

  return 0;
}

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


inline
void show(std::vector<int> & av) {
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
