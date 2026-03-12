#include "logic.hpp"
#include <exception>
#include <iostream>
#include <stdexcept>

int main()
{
  aydogan::SequenceList data;

  try
  {
    aydogan::readInput(std::cin, data);
    return aydogan::runProgram(data, std::cout, std::cerr);
  }
  catch (const std::overflow_error& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << "\n";
    return 2;
  }
  catch (...)
  {
    std::cerr << "Unknown error\n";
    return 2;
  }
}
