#include "BiList.h"
#include <iostream>
#include <string>

using namespace akhrameev;

struct Pair
{
  std::string first;
  BiList<int> second;
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
      int value;

      if (!(std::cin >> value))
        break;

      p.second.push_back(value);
    }

    sequences.push_back(p);
  }

  if (sequences.empty())
  {
    std::cout << 0 << "\n";
    return 0;
  }

  for (auto it = sequences.begin(); it != sequences.end(); ++it)
  {
    std::cout << (*it).first << " ";
  }

  std::cout << "\n";

  bool more = true;

  BiList<int> sums;

  while (more)
  {
    more = false;

    int sum = 0;

    for (auto it = sequences.begin(); it != sequences.end(); ++it)
    {
      BiList<int>& numbers = (*it).second;

      if (!numbers.empty())
      {
        more = true;

        int value = numbers.front();

        std::cout << value << " ";

        sum += value;

        numbers.pop_front();
      }
    }

    if (more)
    {
      std::cout << "\n";
      sums.push_back(sum);
    }
  }

  for (auto it = sums.begin(); it != sums.end(); ++it)
  {
    std::cout << *it << " ";
  }

  std::cout << "\n";

  return 0;
}
