#include <iostream>
#include "ListIterators.h"

namespace alekseev {
  using PStrI = std::pair< std::string, List< int > * >;

  std::ostream & print(std::ostream & out, PStrI p)
  {
    out << p.first << "\n";
    LIter< int > start = begin(p.second);
    LIter< int > end = alekseev::end(p.second);
    while (start != end) {
      std::cout << *(start++) << " ";
    }
    std::cout << "\n";
    return out;
  }
}

int main()
{
  alekseev::List< alekseev::PStrI > * matter_list = alekseev::fake< alekseev::PStrI >();
  alekseev::LIter< alekseev::PStrI > matter_iter = alekseev::before_begin(matter_list);
  size_t matter_size = 0;
  alekseev::List< size_t > * sizes = alekseev::fake< size_t >();
  alekseev::LIter< size_t > sizes_iter = alekseev::before_begin(sizes);

  std::string name;
  size_t counter_for_eof = 0;
  while (++counter_for_eof < 5 && std::cin >> name && !std::cin.eof()) {
    alekseev::List< int > * some_list = alekseev::fake< int >();
    alekseev::LIter< int > some_iter = alekseev::before_begin(some_list);

    int number = 0;
    size_t current_size = 0;
    while (true) {
      while (std::cin.peek() == ' ') {
        std::cin.ignore();
      }
      if (std::cin.peek() == '\n' || std::cin.peek() == EOF) {
        break;
      }
      std::cin >> number;
      some_iter = alekseev::insert_after(some_iter, number);
      ++current_size;
    }
    alekseev::PStrI tmp(name, some_list);
    alekseev::insert_after< alekseev::PStrI >(matter_iter, tmp);
    ++matter_size;
    alekseev::insert_after(sizes_iter, current_size);

    //alekseev::print(std::cout, *matter_iter);
  }

  ++matter_iter;
  alekseev::LCIter< int > * iterators = new alekseev::LCIter< int >[matter_size];
  for (size_t i = 0; i < matter_size; ++i) {
    ++matter_iter;
    std::cout << matter_iter->first << " ";
    iterators[i] = alekseev::before_begin(matter_iter->second);
  }
  std::cout << "\n";

  alekseev::List< int64_t > * sums = alekseev::fake< int64_t >();
  alekseev::LIter< int64_t > sums_iter = alekseev::before_begin(sums);
  size_t j = 0;
  int64_t zero = 0ll;
  while (true) {
    bool flag = false;

    ++sizes_iter;
    alekseev::insert_after(sums_iter, zero);
    for (size_t i = 0; i < matter_size; ++i) {
      if (j < *(++sizes_iter)) {
        int n = *(++iterators[i]);
        std::cout << n << " ";
        *sums_iter += n;
        flag = true;
      }
    }

    if (!flag) {
      break;
    }
    ++j;
    std::cout << "\n";
  }

  ++sums_iter;
  for (size_t i = 0; i < j; ++i) {
    std::cout << *(++sums_iter) << " ";
  }
  std::cout << "\n";
}
