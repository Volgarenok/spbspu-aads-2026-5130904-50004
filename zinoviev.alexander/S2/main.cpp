#include "evaluate.hpp"
#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[])
{
  using namespace zinoviev;

  std::ifstream input;
  std::istream* in = &std::cin;

  if (argc == 2)
  {
    input.open(argv[1]);
    if (!input)
    {
      std::cerr << "Cannot open file\n";
      return 1;
    }
    in = &input;
  }
}
