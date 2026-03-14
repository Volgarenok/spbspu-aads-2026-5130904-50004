#include "List.hpp"
#include "List.cpp"
#include "LIter.hpp"
#include "LIter.cpp"
#include "CLIter.hpp"
#include "CLIter.cpp"
#include <iostream>
#include <string>
#include <limits>

using ull = unsigned long long;

int main()
{
  List<std::string> * fake_str = List<std::string>::fake(nullptr);
  List<List<ull>*> * fake_ll = List<List<ull>*>::fake(nullptr);
  List<LIter<ull>> * fake_LIter = List<LIter<ull>>::fake(nullptr);
  List<LIter<ull>> * fake_CLIter = List<LIter<ull>>::fake(nullptr);
  List<ull> * fake_sum = List<ull>::fake(nullptr);

  LIter<std::string> iter_str = LIter<std::string>(fake_str);
  LIter<List<ull>*> iter_ll = LIter<List<ull>*>(fake_ll);
  LIter<LIter<ull>> iter_LIter = LIter<LIter<ull>>(fake_LIter);
  LIter<ull> iter_sum = LIter<ull>(fake_sum);

  CLIter<std::string> Citer_str = CLIter<std::string>(fake_str);
  LIter<LIter<ull>> Citer_LIter = LIter<LIter<ull>>(fake_CLIter);
  CLIter<List<ull>*> Citer_ll = CLIter<List<ull>*>(fake_ll);
  CLIter<ull> Citer_sum = CLIter<ull>(fake_sum);

  const ull MAX = std::numeric_limits<ull>::max();
  while (true)
  {
    std::string temp_str = "";
    std::cin >> temp_str;
    if (std::cin.eof())
    {
      break;
    }
    iter_str = iter_str.insert_value(temp_str);
    ull temp_ull = 0;
    while (std::cin >> temp_ull)
    {
      try
      {
        if (!iter_ll.hasNext())
        {
          List<ull> * fake_ull = List<ull>::fake(nullptr);
          LIter<ull> iter_ull = LIter<ull>(fake_ull);
          iter_ll = iter_ll.insert_value(fake_ull);
          iter_LIter = iter_LIter.insert_value(iter_ull);
          Citer_LIter = Citer_LIter.insert_value(iter_ull);
          iter_ull = iter_ull.insert_value(temp_ull);
          iter_sum = iter_sum.insert_value(temp_ull);
        }
        else
        {
          iter_sum = iter_sum.next();
          iter_LIter = iter_LIter.next();
          if (iter_LIter.value().hasNext())
          {
            iter_LIter.value() = iter_LIter.value().next();
          }
          iter_ll = iter_ll.next();
          iter_LIter.value() = iter_LIter.value().insert_value(temp_ull);
          try
          {
            if (iter_sum.value() < MAX - temp_ull)
            {
              iter_sum.value() += temp_ull;
            }
            else
            {
              throw std::exception();
            }
          }
          catch (...)
          {
            throw;
          }
        }
      }
      catch (...)
      {
        std::cerr << "Error\n";
        Citer_ll = Citer_ll.list->cut_fake(fake_ll);
        while (Citer_ll.not_empty())
        {
          Citer_ll.value() = Citer_ll.value()->cut_fake(Citer_ll.value());
          Citer_ll.value()->clear(Citer_ll.value());
          Citer_ll = Citer_ll.next();
        }
          Citer_sum = Citer_sum.begin(fake_sum);
          Citer_sum = Citer_sum.list->cut_fake(fake_sum);
          Citer_sum.list->clear(Citer_sum.list);

          Citer_str = Citer_str.begin(fake_str);
          Citer_str = Citer_str.list->cut_fake(fake_str);
          Citer_str.list->clear(Citer_str.list);

          Citer_LIter = Citer_LIter.begin(fake_CLIter);
          Citer_LIter = Citer_LIter.list->cut_fake(Citer_LIter.list);
          Citer_LIter.list->clear(Citer_LIter.list);

          iter_LIter = iter_LIter.begin(fake_LIter);
          iter_LIter = iter_LIter.list->cut_fake(iter_LIter.list);
          iter_LIter.list->clear(iter_LIter.list);

          return 1;
      }
    }
    if (std::cin.eof())
    {
      break;
    }
    else
    {
      std::cin.clear();
      iter_ll = iter_ll.begin(fake_ll);
      iter_LIter = iter_LIter.begin(fake_LIter);
      iter_sum = iter_sum.begin(fake_sum);
    }
  }

  Citer_LIter = Citer_LIter.begin(fake_CLIter);

  while (Citer_str.hasNext())
  {
    Citer_str = Citer_str.next();
    std::cout << Citer_str.value();
    if (Citer_str.hasNext())
    {
      std::cout << " ";
    }
    else
    {
      std::cout << "\n";
    }
  }

  if (!Citer_sum.hasNext())
  {
    std::cout << "0\n";
  }
  while (Citer_LIter.hasNext())
  {
    Citer_LIter = Citer_LIter.next();
    LIter<ull> iter_ull = Citer_LIter.value();
    while (iter_ull.hasNext())
    {
      iter_ull = iter_ull.next();
      std::cout << iter_ull.value();
      if (iter_ull.hasNext())
      {
        std::cout << " ";
      }
      else
      {
        std::cout << "\n";
      }
    }
  }

  while(Citer_sum.hasNext())
  {
    Citer_sum = Citer_sum.next();
    std::cout << Citer_sum.value();
    if (Citer_sum.hasNext())
    {
      std::cout << " ";
    }
    else
    {
      std::cout << "\n";
    }
  }

  Citer_ll = Citer_ll.list->cut_fake(fake_ll);
  while(Citer_ll.not_empty())
  {
    Citer_ll.value() = Citer_ll.value()->cut_fake(Citer_ll.value());
    Citer_ll.value()->clear(Citer_ll.value());
    Citer_ll = Citer_ll.next();
  }
  Citer_sum = Citer_sum.begin(fake_sum);
  Citer_sum = Citer_sum.list->cut_fake(fake_sum);
  Citer_sum.list->clear(Citer_sum.list);

  Citer_str = Citer_str.begin(fake_str);
  Citer_str = Citer_str.list->cut_fake(fake_str);
  Citer_str.list->clear(Citer_str.list);

  Citer_LIter = Citer_LIter.begin(fake_CLIter);
  Citer_LIter = Citer_LIter.list->cut_fake(Citer_LIter.list);
  Citer_LIter.list->clear(Citer_LIter.list);

  iter_LIter = iter_LIter.begin(fake_LIter);
  iter_LIter = iter_LIter.list->cut_fake(iter_LIter.list);
  iter_LIter.list->clear(iter_LIter.list);
}
