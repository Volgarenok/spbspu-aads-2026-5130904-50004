#include "list.hpp"
#include <iostream>
#include <string>
#include <utility>
#include <sstream>

using namespace ivantsova;

int main()
{
  try
  {
    List<std::pair<std::string, List<int>>> sequences;
    std::string line;

    while (std::getline(std::cin, line))
    {
      if (line.empty())
      {
        continue;
      }
      std::istringstream iss(line);
      std::string name;
      iss >> name;
      List<int> numbers;
      int num;
      while (iss >> num)
      {
        numbers.push_back(num);
      }
      sequences.push_back({name, std::move(numbers)});
    }

    if (sequences.empty())
    {
      std::cout << "0" << "\n";
      return 0;
    }
    bool first = true;
    for (auto it = sequences.cbegin(); it != sequences.cend(); ++it)
    {
      if (!first)
      {
        std::cout << ' ';
      }
      std::cout << it->first;
      first = false;
    }
    std::cout << "\n";
    size_t maxLen = 0;
    for (auto it = sequences.cbegin(); it != sequences.cend(); ++it)
    {
      if (it->second.size() > maxLen)
      {
        maxLen = it->second.size();
      }
    }
    List<List<int>> transposed;
    for (size_t i = 0; i < maxLen; ++i)
    {
      List<int> newList;
      for (auto it = sequences.cbegin(); it != sequences.cend(); ++it)
      {
        if (i < it->second.size())
        {
          auto elemIt = it->second.cbegin();
          for (size_t j = 0; j < i; ++j)
          {
            ++elemIt;
          }
          newList.push_back(*elemIt);
        }
      }
      transposed.push_back(std::move(newList));
    }

    for (auto it = transposed.cbegin(); it != transposed.cend(); ++it)
    {
      if (it->empty())
      {
        std::cout << "\n";
        continue;
      }

      bool firstInRow = true;
      for (auto elemIt = it->cbegin(); elemIt != it->cend(); ++elemIt)
      {
        if (!firstInRow)
        {
          std::cout << ' ';
        }
        std::cout << *elemIt;
        firstInRow = false;
      }
      std::cout << "\n";
    }
    List<int> sums;
    for (auto it = transposed.cbegin(); it != transposed.cend(); ++it)
    {
      int total = 0;
      for (auto elemIt = it->cbegin(); elemIt != it->cend(); ++elemIt)
      {
        total += *elemIt;
      }
      sums.push_back(total);
    }
    first = true;
    for (auto it = sums.cbegin(); it != sums.cend(); ++it)
    {
      if (!first)
      {
        std::cout << ' ';
      }
      std::cout << *it;
      first = false;
    }
    std::cout << "\n";
    return 0;
  }
  catch (const std::exception& e)
  {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }
}
