#include "biList.hpp"

#include <iostream>
#include <string>
#include <utility>
#include <limits>
#include <stdexcept>
#include <cctype>

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
      std::string token;

      while (std::cin >> token && std::isdigit(token[0]))
      {
        try
        {
          unsigned long long num = std::stoull(token);
          numbers.pushBack(num);
        }
        catch (const std::out_of_range&)
        {
          sequences.pushBack(std::make_pair(name, std::move(numbers)));
          throw std::overflow_error("Overflow");
        }
      }

      sequences.pushBack(std::make_pair(name, std::move(numbers)));

      if (std::cin.eof()) break;
      std::cin.clear();
    }

    if (sequences.isEmpty())
    {
      std::cout << "0\n";
      return 0;
    }

    bool first = true;
    for (auto it = sequences.cbegin(); it != sequences.cend(); ++it)
    {
      if (!first) std::cout << " ";
      std::cout << it->first;
      first = false;
    }
    std::cout << "\n";

    size_t maxLen = 0;
    for (auto it = sequences.cbegin(); it != sequences.cend(); ++it)
    {
      if (it->second.getSize() > maxLen)
      {
        maxLen = it->second.getSize();
      }
    }

    BiList<BiList<unsigned long long>> transp;
    for (size_t i = 0; i < maxLen; ++i)
    {
      BiList<unsigned long long> newList;
      for (auto it = sequences.cbegin(); it != sequences.cend(); ++it)
      {
        if (i < it->second.getSize())
        {
          auto elemIt = it->second.cbegin();
          for (size_t j = 0; j < i; ++j) ++elemIt;
          newList.pushBack(*elemIt);
        }
      }
      if (!newList.isEmpty())
      {
        transp.pushBack(std::move(newList));
      }
    }

    BiList<unsigned long long> sums;
    for (auto it = transp.cbegin(); it != transp.cend(); ++it)
    {
      bool firstInRow = true;
      unsigned long long total = 0;
      for (auto elemIt = it->cbegin(); elemIt != it->cend(); ++elemIt)
      {
        if (!firstInRow) std::cout << " ";
        std::cout << *elemIt;
        firstInRow = false;

        if (total > std::numeric_limits<unsigned long long>::max() - *elemIt)
        {
          std::cout << "\n";
          throw std::overflow_error("Overflow");
        }
        total += *elemIt;
      }
      std::cout << "\n";
      sums.pushBack(total);
    }

    if (!sums.isEmpty())
    {
      first = true;
      for (auto it = sums.cbegin(); it != sums.cend(); ++it)
      {
        if (!first) std::cout << " ";
        std::cout << *it;
        first = false;
      }
      std::cout << "\n";
    }

    return 0;
  }
  catch (const std::overflow_error &e)
  {
    std::cerr << "Overflow\n";
    return 1;
  }
  catch (const std::exception &e)
  {
    return 1;
  }
}
