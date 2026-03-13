#include "List.hpp"
#include "List.cpp"
#include "LIter.hpp"
#include "LIter.cpp"
#include "CLIter.hpp"
#include "CLIter.cpp"
#include <iostream>
#include <string>

int main()
{
  List<std::string> * fake_str = List<std::string>::fake(nullptr);
  List<List<int>*> * fake_ll = List<List<int>*>::fake(nullptr);
  List<LIter<int>> * fake_LIter = List<LIter<int>>::fake(nullptr);
  List<LIter<int>> * fake_CLIter = List<LIter<int>>::fake(nullptr);
  List<int> * fake_sum = List<int>::fake(nullptr);

  LIter<std::string> iter_str = LIter<std::string>(fake_str);
  LIter<List<int>*> iter_ll = LIter<List<int>*>(fake_ll);
  LIter<LIter<int>> iter_LIter = LIter<LIter<int>>(fake_LIter);
  LIter<int> iter_sum = LIter<int>(fake_sum);

  CLIter<std::string> Citer_str = CLIter<std::string>(fake_str);
  LIter<LIter<int>> Citer_LIter = LIter<LIter<int>>(fake_CLIter);
  CLIter<List<int>*> Citer_ll = CLIter<List<int>*>(fake_ll);
  CLIter<int> Citer_sum = CLIter<int>(fake_sum);

  while (true)
  {
    std::string temp_str = "";
    std::cin >> temp_str;
    if (std::cin.eof())
    {
      break;
    }
   iter_str = iter_str.insert_value(temp_str);
  }
}
