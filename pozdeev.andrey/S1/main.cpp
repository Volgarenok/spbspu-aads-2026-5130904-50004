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
    std::string line;

    while (std::getline(std::cin, line))
    {
      if (line.empty())
      {
        continue;
      }

      size_t i = 0;
      while (i < line.size() && std::isspace(line[i]))
      {
        i++;
      }
      if (i == line.size())
      {
        continue;
      }

      size_t start = i;
      while (i < line.size() && !std::isspace(line[i]))
      {
        i++;
      }
      std::string name = line.substr(start, i - start);

      BiList<unsigned long long> numbers;
      while (i < line.size())
      {
        while (i < line.size() && std::isspace(line[i]))
        {
          i++;
        }
        if (i == line.size())
        {
          break;
        }

        start = i;
        while (i < line.size() && !std::isspace(line[i]))
        {
          i++;
        }
        std::string token = line.substr(start, i - start);

        try
        {
          unsigned long long num = std::stoull(token);
          numbers.pushBack(num);
        }
        catch (const std::out_of_range&)
        {
          sequences.pushBack(std::make_pair(name, std::move(numbers)));
          bool isFirstInHeader = true;
          for (auto it = sequences.cbegin(); it != sequences.cend(); ++it)
          {
            if (!isFirstInHeader)
            {
              std::cout << " ";
            }
            std::cout << it->first;
            isFirstInHeader = false;
          }
          std::cout << "\n";
          throw std::overflow_error("Overflow");
        }
      }
      sequences.pushBack(std::make_pair(name, std::move(numbers)));
    }

    if (sequences.isEmpty())
    {
      std::cout << "0\n";
      return 0;
    }

    bool isFirstHeader = true;
    size_t maxLen = 0;
    bool allEmpty = true;
    for (auto it = sequences.cbegin(); it != sequences.cend(); ++it)
    {
      if (!isFirstHeader)
      {
        std::cout << " ";
      }
      std::cout << it->first;
      isFirstHeader = false;

      if (it->second.getSize() > maxLen)
      {
        maxLen = it->second.getSize();
      }
      if (!it->second.isEmpty())
      {
        allEmpty = false;
      }
    }
    std::cout << "\n";

    if (allEmpty)
    {
      std::cout << "0\n";
      return 0;
    }

    BiList<unsigned long long> resultSums;
    for (size_t i = 0; i < maxLen; ++i)
    {
      bool isFirstInRow = true;
      unsigned long long currentTotal = 0;

      for (auto it = sequences.cbegin(); it != sequences.cend(); ++it)
      {
        if (i < it->second.getSize())
        {
          auto elemIt = it->second.cbegin();
          for (size_t j = 0; j < i; ++j)
          {
            ++elemIt;
          }

          unsigned long long val = *elemIt;
          if (!isFirstInRow)
          {
            std::cout << " ";
          }
          std::cout << val;
          isFirstInRow = false;

          if (currentTotal > std::numeric_limits<unsigned long long>::max() - val)
          {
            std::cout << "\n";
            throw std::overflow_error("Overflow");
          }
          currentTotal += val;
        }
      }
      std::cout << "\n";
      resultSums.pushBack(currentTotal);
    }

    bool isFirstSum = true;
    for (auto it = resultSums.cbegin(); it != resultSums.cend(); ++it)
    {
      if (!isFirstSum)
      {
        std::cout << " ";
      }
      std::cout << *it;
      isFirstSum = false;
    }
    std::cout << "\n";

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
