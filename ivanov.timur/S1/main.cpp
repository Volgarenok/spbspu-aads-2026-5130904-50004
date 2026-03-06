#include<iostream>
#include "List.h"

using namespace ivanov;

int main(){
  std::string wtmp;
  int ntmp;

  List<std::string> names;
  List<List<int>> nums;

  try {
    while (!std::cin.eof()) {
      std::cin >> wtmp;
      names.push_back(wtmp);
      List<int> curr;
      while (wtmp != "\n") {
        std::cin >> wtmp;
        ntmp = std::stoi(wtmp);
        curr.push_back(ntmp);
      }
      nums.push_back(std::move(curr));
    }
  } catch (std::bad_alloc& e) {
    std::cerr << "Bad allocation failure\n";
    return 1;
  }

  auto name = names.cbegin();
  for (size_t i = 0; i < names.size(); ++i) {
    std::cout << *name;
    if (i != names.size() - 1) std::cout << " ";
    else std::cout << "\n";
    ++name;
  }

  List<Iter<int>> iters;
  Iter<List<int>> it = nums.begin();
  size_t max = it->size();
  iters.push_back(it->begin());
  for (size_t i = 0; i < nums.size(); ++i) {
    ++it;
    iters.push_back(it->begin());
    if (it->size() > max) max = it->size();
  }

  Iter<Iter<int>> tm = iters.begin();
  List<int> sums;
  try {
    int s = 0;
    for (size_t i = 0; i < max; ++i) {
      Iter<Iter<int>> tmp = tm;
      for (size_t j = 0; j < i; ++j) tmp->operator++();
      try {
        int t = tmp->operator*();
        std::cout << t;
        if (i != max - 1) std::cout << " ";
        sum(s, t);
      }
      catch (std::bad_alloc& e) {
      }
    }
    std::cout << "\n";
    sums.push_back(s);
  } catch (...) {
    std::cerr << "Something went wrong\n";
    return 1;
  }

  Iter<int> sms = sums.begin();
  for (size_t i = 0; i < nums.size(); ++i) {
    std::cout << *sms;
    if (i != nums.size() - 1) std::cout << " ";
    else std::cout << "\n";
    ++sms;
  }

  return 0;
}
