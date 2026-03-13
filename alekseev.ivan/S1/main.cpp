#include <iostream>
#include "ListIterators.h"

namespace alekseev {
  using PStrI = std::pair< std::string, List< int > * >;

  std::ostream & print(std::ostream & out, PStrI p)
  {
    out << p.first << "\n";
    LIter< int > start = begin(p.second);
    LIter< int > end = next(alekseev::end(p.second));
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

  std::string name;
  size_t counter = 0;
  while (++counter < 5 && std::cin >> name && !std::cin.eof()) {
    alekseev::List< int > * some_list = alekseev::fake< int >();
    alekseev::LIter< int > some_iter = alekseev::before_begin(some_list);

    int number = 0;
    while (true) {
      while (std::cin.peek() == ' ') {
        std::cin.ignore();
      }
      if (std::cin.peek() == '\n' || std::cin.peek() == EOF) {
        break;
      }
      std::cin >> number;
      some_iter = alekseev::insert_after(some_iter, number);
    }
    alekseev::PStrI tmp(name, some_list);
    alekseev::insert_after< alekseev::PStrI >(matter_iter, tmp);

    //alekseev::print(std::cout, *matter_iter);
  }

  alekseev::LIter< alekseev::PStrI > matter_iter_start = alekseev::before_begin(matter_list);
  while (matter_iter_start != matter_iter) {
    std::cout << (++matter_iter_start)->first << " ";
  }
  std::cout << "\n";
}
