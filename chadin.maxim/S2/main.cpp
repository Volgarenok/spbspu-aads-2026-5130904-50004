#include <iostream>
#include <fstream>
#include <string>
#include "stack.hpp"
#include "expression_processor.hpp"

int main(int argc, char * argv[])
{
  std::ifstream file;
  if (argc == 2)
  {
    file.open(argv[1]);
    if (!file.is_open())
    {
      std::cerr << "Error: File" << std::endl;
      return 1;
    }
  }

  std::istream & in = (argc == 2) ? file : std::cin;
  chadin::Stack< long long > results;
  std::string line = "";

  try
  {
    while (std::getline(in, line))
    {
      if (line.empty()) continue;
      results.push(chadin::evaluateInfix(line));
    }
  }
  catch (const std::exception & e)
  {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }

  bool space = false;
  while (!results.isEmpty())
  {
    if (space) std::cout << " ";
    std::cout << results.top();
    results.pop();
    space = true;
  }
  if (space) std::cout << std::endl;

  return 0;
}
