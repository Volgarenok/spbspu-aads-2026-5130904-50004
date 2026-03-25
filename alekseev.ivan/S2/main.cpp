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
    std::getline(input, line);
    res.push(alekseev::count_from_string(line));
  }

  std::cout << res.top();
  res.pop();
  while (!res.empty()) {
    std::cout << " " << res.top();
    res.pop();
  }
}
