#include <iostream>
#include <limits>
#include <string>
#include <utility>
#include <stdexcept>

#include "biList.hpp"

using namespace pozdeev;

int main()
{
  try
  {
    BiList<std::pair<std::string, BiList<unsigned long long>>> sequences;
    std::string name;

    while (std::cin >> name)
    {
      BiList<unsigned long long> numbers;
      unsigned long long num;
      while (std::cin >> num)
      {
        numbers.push_back(num);
      }

      if (!std::cin.eof())
      {
        std::cin.clear();
      }

      sequences.push_back(std::make_pair(name, std::move(numbers)));
    }

    if (sequences.is_empty())
    {
      std::cout << "0\n";
      return 0;
    }

    bool first = true;
    for (auto it = sequences.cbegin(); it != sequences.cend(); ++it)
    {
      if (!first)
      {
        std::cout << " ";
      }
      std::cout << it->first;
      first = false;
    }
    std::cout << "\n";

    size_t maxLen = 0;
    for (auto it = sequences.cbegin(); it != sequences.cend(); ++it)
    {
      if (it->second.getsize() > maxLen)
      {
        maxLen = it->second.getsize();
      }
    }

    BiList<unsigned long long> sums;
    for (size_t i = 0; i < maxLen; ++i)
    {
      unsigned long long currentSum = 0;
      bool firstInRow = true;

      for (auto it = sequences.cbegin(); it != sequences.cend(); ++it)
      {
        if (i < it->second.getsize())
        {
          auto elemIt = it->second.cbegin();
          for (size_t j = 0; j < i; ++j)
          {
            ++elemIt;
          }

          unsigned long long val = *elemIt;

          if (firstInRow)
          {
            firstInRow = false;
          }
          else
          {
            std::cout << " ";
          }
          std::cout << val;

          if (currentSum > std::numeric_limits<unsigned long long>::max() - val)
          {
            throw std::overflow_error("Overflow");
          }
          currentSum += val;
        }
      }
      std::cout << "\n";
      sums.push_back(currentSum);
    }

    if (sums.is_empty())
    {
      std::cout << "0\n";
    }
    else
    {
      bool firstSum = true;
      for (auto it = sums.cbegin(); it != sums.cend(); ++it)
      {
        if (!firstSum)
        {
          std::cout << " ";
        }
        std::cout << *it;
        firstSum = false;
      }
      std::cout << "\n";
    }

    return 0;
  }
  catch (const std::overflow_error &e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
  catch (const std::exception &e)
  {
    std::cerr << "Error\n";
    return 1;
  }
}
