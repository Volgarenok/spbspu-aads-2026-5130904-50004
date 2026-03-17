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

    for (auto it = data.cbegin(); it != data.cend(); ++it)
    {
      std::cout << it->first << (std::next(it) == data.cend() ? "" : " ");
    }
    std::cout << "\n";

    size_t max_len = 0;
    for (auto it = data.cbegin(); it != data.cend(); ++it)
    {
      if (it->second.getSize() > max_len)
      {
        max_len = it->second.getSize();
      }
    }

    BiList< unsigned long long > sums;
    for (size_t i = 0; i < max_len; ++i)
    {
      unsigned long long row_sum = 0;
      bool first = true;
      for (auto it = data.cbegin(); it != data.cend(); ++it)
      {
        if (i < it->second.getSize())
        {
          auto num_it = it->second.cbegin();
          for (size_t j = 0; j < i; ++j)
          {
            ++num_it;
          }

          std::cout << (first ? "" : " ") << *num_it;
          first = false;

          if (std::numeric_limits< unsigned long long >::max() - row_sum < *num_it)
          {
            throw std::overflow_error("Sum overflow");
          }
          row_sum += *num_it;
        }
      }
      std::cout << "\n";
      sums.pushBack(row_sum);
    }

    for (auto it = sums.cbegin(); it != sums.cend(); ++it)
    {
      std::cout << *it << (std::next(it) == sums.cend() ? "" : " ");
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
