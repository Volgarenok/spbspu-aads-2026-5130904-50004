#include <iostream>
#include "ListIterators.h"

namespace alekseev {
  using PStrI = std::pair< std::string, List< int > * >;

  std::ostream & print(std::ostream & out, PStrI p)
  {
    out << p.first << "\n";
    alekseev::LIter< int > start = alekseev::begin(p.second);
    alekseev::LIter< int > end = alekseev::next(alekseev::end(p.second));
    while (start != end) {
      std::cout << *start << " ";
      ++start;
    }
    std::cout << "\n";
    std::cerr << "3\n";
    return out;
  }
}

int main()
{
  alekseev::List< alekseev::PStrI > * matter_list = alekseev::fake< alekseev::PStrI >();
  alekseev::LIter< alekseev::PStrI > matter_iter = alekseev::before_begin(matter_list);

  std::string name;
  while (std::cin >> name && !std::cin.eof()) {
    alekseev::List< int > * some_list = alekseev::fake< int >();
    alekseev::LIter< int > some_iter = alekseev::before_begin(some_list);

    int number = 0;
    while (std::cin >> number) {
      some_iter = alekseev::insert_after(some_iter, number);

      while (std::cin.peek() == ' ') {
        std::cin.ignore();
      }
      if (std::cin.peek() == '\n' || std::cin.peek() == EOF) {
        break;
      }
    }
    alekseev::PStrI tmp(name, some_list);
    matter_iter = alekseev::insert_after< alekseev::PStrI >(matter_iter, tmp);

    alekseev::print(std::cout, *matter_iter);
  }
}
