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

int main()
{
}
