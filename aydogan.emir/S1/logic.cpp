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
  if (data.empty())
  {
    out << "0\n";
    return 0;
  }

  bool first = true;

  for (auto it = data.cbegin(); it != data.cend(); ++it)
  {
    if (!first)
    {
      out << " ";
    }

    out << it->first;
    first = false;
  }

  out << "\n";
List< ConstIterator< unsigned long long > > iters;
auto iterTail = iters.beforeBegin();

for (auto it = data.cbegin(); it != data.cend(); ++it)
{
  iterTail = iters.insertAfter(iterTail, it->second.cbegin());
}
  return 0;
}

}
