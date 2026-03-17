#include <iostream>
#include <string>
#include <limits>
#include "BiList.hpp"

int main()
{
  using namespace chadin;
  try
  {
    BiList< std::pair< std::string, BiList< unsigned long long > > > data;
    std::string name = "";

    while (std::cin >> name)
    {
      BiList< unsigned long long > numbers;
      while (std::cin.peek() != '\n' && std::cin.peek() != EOF)
      {
        unsigned long long num = 0;
        if (std::cin >> num)
        {
          numbers.pushBack(num);
        }
        else
        {
          std::cin.clear();
          while (std::cin.peek() != '\n' && std::cin.peek() != EOF && !std::isdigit(std::cin.peek()))
          {
            std::cin.ignore();
          }
        }
      }
      data.pushBack({name, std::move(numbers)});
    }

    if (data.isEmpty())
    {
      return 0;
    }

    size_t nameCount = 0;
    for (auto it = data.cbegin(); it != data.cend(); ++it)
    {
      std::cout << it->first;
      if (++nameCount < data.getSize())
      {
        std::cout << " ";
      }
    }
    std::cout << "\n";

    size_t maxLen = 0;
    for (auto it = data.cbegin(); it != data.cend(); ++it)
    {
      if (it->second.getSize() > maxLen)
      {
        maxLen = it->second.getSize();
      }
    }

    BiList< unsigned long long > sums;
    for (size_t i = 0; i < maxLen; ++i)
    {
      unsigned long long rowSum = 0;
      bool isFirstInRow = true;
      for (auto it = data.cbegin(); it != data.cend(); ++it)
      {
        if (i < it->second.getSize())
        {
          auto numIt = it->second.cbegin();
          for (size_t j = 0; j < i; ++j)
          {
            ++numIt;
          }

          if (!isFirstInRow)
          {
            std::cout << " ";
          }
          std::cout << *numIt;
          isFirstInRow = false;

          if (std::numeric_limits< unsigned long long >::max() - rowSum < *numIt)
          {
            throw std::overflow_error("Sum overflow");
          }
          rowSum += *numIt;
        }
      }
      std::cout << "\n";
      sums.pushBack(rowSum);
    }

    size_t sumCount = 0;
    for (auto it = sums.cbegin(); it != sums.cend(); ++it)
    {
      std::cout << *it;
      if (++sumCount < sums.getSize())
      {
        std::cout << " ";
      }
    }
    std::cout << "\n";
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
  return 0;
}
