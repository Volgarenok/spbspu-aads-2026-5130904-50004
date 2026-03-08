#include "BiList.hpp"
#include <iostream>
#include <string>
#include <utility>

using namespace zinoviev;
int main()
{
  BiList<std::pair<std::string, BiList<int>>> outer;
  std::string name{};
  int x = 0;

  while (std::cin >> name)
  {
    BiList<int> inner;

    while (std::cin >> x)
    {
      inner.push_back(x);
    }

    outer.push_back(std::make_pair(name, std::move(inner)));

    if (!std::cin.eof())
    {
      std::cin.clear();
    }
  }

  if (!outer.size())
  {
    std::cout << "0\n";
    return 0;
  }

  CBIter<std::pair<std::string, BiList<int>>> c_iter_outer = outer.cbegin();

  std::cout << c_iter_outer->first;
  ++c_iter_outer;

  while (c_iter_outer != outer.cend())
  {
    std::cout << " " << c_iter_outer->first;
    ++c_iter_outer;
  }
  std::cout << "\n";

  BIter<std::pair<std::string, BiList<int>>> iter_outer = outer.begin();

  BiList<std::pair<BIter<int>, BIter<int>>> list_iter_inner;
  while (iter_outer != outer.end())
  {
    if ((iter_outer->second).size())
    {
      list_iter_inner.push_back(std::make_pair(iter_outer->second.begin(), iter_outer->second.end()));
    }
    ++iter_outer;
  }

  if (list_iter_inner.size() == 0)
  {
    std::cerr << "Error: no numbers to sum\n";
    return 1;
  }
}
