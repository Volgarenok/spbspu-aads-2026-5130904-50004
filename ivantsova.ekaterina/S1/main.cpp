#include "list.hpp"
#include <iostream>
#include <string>
#include <utility>
#include <sstream>

using namespace ivantsova;

List<std::pair<std::string, List<int>>> readSequences()
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
  return sequences;
}

void printNames(const List<std::pair<std::string, List<int>>>& sequences)
{
  if (sequences.empty())
  {
    return;
  }
  bool first = true;
  for (auto it = sequences.cbegin(); it != sequences.cend(); ++it)
  {
    if (!first)
    {
      std::cout << ' ';
      std::cout << it->first;
      first = false;
    }
  }
  std::cout << "\n";
}

List<List<int>> transposeSequences(const List<std::pair<std::string, List<int>>>& sequences)
{
  List<List<int>> result;
  if (sequences.empty())
  {
    return result;
  }
  size_t maxLen = 0;
  for (auto it = sequences.cbegin(); it != sequences.cend(); ++it)
  {
    if (it->second.size() > maxLen)
    {
      maxLen = it->second.size();
    }
  }
    
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
    result.push_back(std::move(newList));
  }
  return result;
}

List<int> calculateSums(const List<List<int>>& transposed)
{
  List<int> sums;
  for (auto it = transposed.cbegin(); it != transposed.cend(); ++it)
  {
    int total = 0;
    for (auto elemIt = it->cbegin(); elemIt != it->cend(); ++elemIt)
    {
      sum(total, *elemIt);
    }
    sums.push_back(total);
  }
  return sums;
}

void printList(const List<int>& list)
{
  if (list.empty())
  {
    std::cout << "\n";
    return;
  }
    
  bool first = true;
  for (auto it = list.cbegin(); it != list.cend(); ++it)
  {
    if (!first)
    {
      std::cout << ' ';
    }
    std::cout << *it;
    first = false;
  }
  std::cout << "\n";
}

int main()
{
  try
  {
    auto sequences = readSequences();
    if (sequences.empty())
    {
      std::cout << "0" << "\n";
      return 0;
    }
    printNames(sequences);
        
    auto transposed = transposeSequences(sequences);
    for (auto it = transposed.cbegin(); it != transposed.cend(); ++it)
    {
      printList(*it);
    }
        
    auto sums = calculateSums(transposed);
    printList(sums);
    return 0;
  }
  catch (const std::exception& e)
  {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }
}
