#include "BiList.h"

#include <iostream>
#include <string>
#include <limits>

using namespace akhrameev;

struct Pair
{
  std::string first;
  BiList<unsigned long long> second;
};

int main()
{
  BiList<Pair> sequences;
  std::string name;

  while (std::cin >> name)
  {
    Pair p;
    p.first = name;

    while (std::cin.peek() == ' ')
    {
      unsigned long long value;

      if (!(std::cin >> value))
      {
        if (std::cin.fail())
        {
          std::cerr << "overflow\n";
          return 1;
        }
        break;
      }

      p.second.push_back(value);
    }

    sequences.push_back(p);
  }

  if (sequences.empty())
  {
    std::cout << 0 << "\n";
    return 0;
  }

  bool firstName = true;
  for (auto it = sequences.begin(); it != sequences.end(); ++it)
  {
    if (!firstName)
    {
      std::cout << " ";
    }
    std::cout << (*it).first;
    firstName = false;
  }
  std::cout << "\n";

  bool more = true;
  bool printedNumbers = false;

  BiList<unsigned long long> sums;

  while (more)
  {
    more = false;
    unsigned long long sum = 0;

    bool firstNum = true;

    for (auto it = sequences.begin(); it != sequences.end(); ++it)
    {
      BiList<unsigned long long>& numbers = (*it).second;

      if (!numbers.empty())
      {
        more = true;

        unsigned long long value = numbers.front();

        if (!firstNum)
        {
          std::cout << " ";
        }

        std::cout << value;
        firstNum = false;

        sum += value;

        numbers.pop_front();
      }
    }

    if (more)
    {
      printedNumbers = true;
      std::cout << "\n";
      sums.push_back(sum);
    }
  }

  if (!printedNumbers)
  {
    std::cout << "0\n";
    return 0;
  }

  bool firstSum = true;
  for (auto it = sums.begin(); it != sums.end(); ++it)
  {
    if (!firstSum)
    {
      std::cout << " ";
    }

    std::cout << *it;
    firstSum = false;
  }

  std::cout << "\n";

  return 0;
}
