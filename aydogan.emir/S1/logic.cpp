#include "logic.hpp"

#include <iostream>
#include <limits>
#include <stdexcept>

namespace aydogan
{

void readInput(std::istream& in, SequenceList& data)
{
    std::string name;
  auto seqTail = data.beforeBegin();

  while (in >> name)
  {
    NumberList numbers;
    auto numTail = numbers.beforeBegin();

    while (true)
    {
      int c = in.peek();

      if (c == '\n' || c == EOF)
      {
        break;
      }

      unsigned long long value = 0;

      if (!(in >> value))
      {
        throw std::overflow_error("Overflow");
      }

      numTail = numbers.insertAfter(numTail, value);
    }

    seqTail = data.insertAfter(
      seqTail,
      std::make_pair(name, numbers)
    );
  }
}

int runProgram(
  const SequenceList& data,
  std::ostream& out,
  std::ostream& err
)
{
  return 0;
}

}