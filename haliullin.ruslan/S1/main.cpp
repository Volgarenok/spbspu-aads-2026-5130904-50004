#include <iostream>
#include <string>
#include <utility>
#include "BiList.hpp"

using namespace haliullin;

int main()
{
   try
  {
    BiList<std::pair<std::string, BiList<unsigned long long>>> storage;
    std::string token;
    unsigned long long value = 0;
  }
  catch(const std::exception &e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
}
