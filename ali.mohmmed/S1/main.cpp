#include <iostream>
#include <string>
#include <utility>
#include "list.hpp"

int main()
{
  ali::List< std::pair< std::string, ali::List< int > > > sequences;

  std::string name;

  while (std::cin >> name)
  {
    ali::List< int > numbers;
    int value = 0;

    while (std::cin.peek() != '\n' && std::cin >> value)
    {
      numbers.push_back(value);
    }

    sequences.push_back(std::make_pair(name, numbers));
    std::cin.clear();
  }

  if (sequences.empty())
  {
    std::cout << 0 << '\n';
    return 0;
  }

  for (auto it = sequences.begin(); it != sequences.end(); ++it)
  {
    std::cout << (*it).first;

    auto next = it;
    ++next;

    if (next != sequences.end())
    {
      std::cout << ' ';
    }
  }

  std::cout << '\n';

  std::size_t maxSize = 0;

  for (auto it = sequences.begin(); it != sequences.end(); ++it)
  {
    if ((*it).second.size() > maxSize)
    {
      maxSize = (*it).second.size();
    }
  }

  ali::List< int > sums;

  for (std::size_t i = 0; i < maxSize; ++i)
  {
    bool firstNumber = true;
    int sum = 0;

    for (auto seqIt = sequences.begin(); seqIt != sequences.end(); ++seqIt)
    {
      std::size_t pos = 0;

      for (auto numIt = (*seqIt).second.begin(); numIt != (*seqIt).second.end(); ++numIt)
      {
        if (pos == i)
        {
          if (!firstNumber)
          {
            std::cout << ' ';
          }

          std::cout << *numIt;
          sum += *numIt;
          firstNumber = false;
        }

        ++pos;
      }
    }

    sums.push_back(sum);
    std::cout << '\n';
  }

  for (auto it = sums.begin(); it != sums.end(); ++it)
  {
    std::cout << *it;

    auto next = it;
    ++next;

    if (next != sums.end())
    {
      std::cout << ' ';
    }
  }

  std::cout << '\n';

  return 0;
}
