#include <iostream>
#include <string>
#include "list.h"

namespace aushev {

struct Sequence {
  std::string name;
  List< int > numbers;
};

int processSequences()
{
  List< Sequence > sequences;
  std::string name;

  while (std::cin >> name) {
    Sequence seq;
    seq.name = name;
    int number;
    while (std::cin.peek() != '\n' && std::cin.peek() != EOF) {
      if (!(std::cin >> number)) {
        if (std::cin.eof()) {
          break;
        }
        std::cerr << "Error: invalid input\n";
        return 1;
      }
      seq.numbers.push_back(number);
    }
    sequences.push_back(seq);
    if (std::cin.eof()) {
      break;
    }
    std::cin.ignore();
  }

  if (sequences.empty()) {
    std::cout << "0\n";
    return 0;
  }

  for (auto it = sequences.begin(); it != sequences.end(); ++it) {
    if (it != sequences.begin()) {
      std::cout << " ";
    }
    std::cout << (*it).name;
  }
  std::cout << "\n";

  return 0;
}

}

int main()
{
  return aushev::processSequences();
}
