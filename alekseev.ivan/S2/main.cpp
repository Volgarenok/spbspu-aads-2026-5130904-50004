#include <iostream>
#include <fstream>
#include "expressions_processing.h"
#include "stack.h"

int main(int argc, char ** argv)
{
  std::ifstream file;
  if (argc == 2) {
    file.open(argv[1]);
  }
  std::istream & input = argc == 2 ? file : std::cin;

  alekseev::Stack< int > res;
  while (!input.eof()) {
    std::string line;
    try {
      std::getline(input, line);
      res.push(alekseev::count_from_string(line));
    } catch (const std::exception & e) {
      std::cout << e.what() << "\n";
      return 1;
    }
  }

  std::cout << res.top();
  res.pop();
  while (!res.empty()) {
    std::cout << " " << res.top();
    res.pop();
  }
  std::cout << "\n";
}
