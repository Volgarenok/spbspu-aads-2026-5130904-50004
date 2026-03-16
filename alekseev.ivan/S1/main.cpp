#include <iostream>
#include "ListIterators.h"

namespace alekseev {
  using PStrI = std::pair< std::string, List< int > * >;
  void destroy_matter_iter(LIter< PStrI > matter_iter);
}

int main()
{
  alekseev::List< alekseev::PStrI > * matter_list = alekseev::fake< alekseev::PStrI >();
  alekseev::LIter< alekseev::PStrI > matter_iter = alekseev::before_begin(matter_list);
  size_t matter_size = 0;
  alekseev::List< size_t > * sizes = nullptr;
  try {
    sizes = alekseev::fake< size_t >(); //
  } catch (const std::bad_alloc & e) {
    alekseev::rmfake(matter_list);
  }
  alekseev::LIter< size_t > sizes_iter = alekseev::before_begin(sizes);

  std::string name;
  while (std::cin >> name && !std::cin.eof()) {
    if (std::cin.fail()) {
      alekseev::destroy_matter_iter(matter_iter);
      alekseev::destroy(++sizes_iter);
      std::cerr << "bad input\n";
      return 1;
    }
    alekseev::List< int > * some_list = nullptr;
    try {
      some_list = alekseev::fake< int >(); //
    } catch (const std::bad_alloc & e) {
      alekseev::destroy_matter_iter(matter_iter);
      alekseev::destroy(++sizes_iter);
      std::cerr << e.what() << "\n";
      return 1;
    }
    alekseev::LIter< int > some_iter = alekseev::before_begin(some_list);

    try {
      int number = 0;
      size_t current_size = 0;
      while (true) {
        while (std::cin.peek() == ' ') {
          std::cin.ignore();
        }
        if (std::cin.peek() == '\n' || std::cin.peek() == EOF) {
          break;
        }
        std::cin >> number;
        if (std::cin.fail()) {
          alekseev::destroy_matter_iter(matter_iter);
          alekseev::destroy(++sizes_iter);
          alekseev::destroy(++some_iter);
          std::cerr << "bad input\n";
          return 1;
        }
        some_iter = alekseev::insert_after(some_iter, number); //
        ++current_size;
      }
      alekseev::PStrI tmp(name, some_list);
      alekseev::insert_after< alekseev::PStrI >(matter_iter, tmp); //
      ++matter_size;
      alekseev::insert_after(sizes_iter, current_size); //
    } catch (const std::bad_alloc & e) {
      alekseev::destroy_matter_iter(matter_iter);
      alekseev::destroy(++sizes_iter);
      alekseev::destroy(++some_iter);
      std::cerr << e.what() << "\n";
      return 1;
    }
  }
  if (matter_size == 0) {
    std::cout << "0\n";
    alekseev::destroy_matter_iter(matter_iter);
    alekseev::destroy(++sizes_iter);
    return 0;
  }

  ++matter_iter;
  alekseev::LCIter< int > * iterators = new alekseev::LCIter< int >[matter_size];
  for (size_t i = 0; i < matter_size; ++i) {
    ++matter_iter;
    std::cout << matter_iter->first;
	if (i < matter_size - 1) {
      std::cout << " ";
	}
    iterators[i] = alekseev::before_begin(matter_iter->second);
  }
  std::cout << "\n";

  alekseev::List< int64_t > * sums = nullptr;
  try {
    sums = alekseev::fake< int64_t >();
  } catch (const std::bad_alloc & e) {
    alekseev::destroy_matter_iter(matter_iter);
    delete[] iterators;
    alekseev::destroy(++sizes_iter);
    std::cerr << e.what() << "\n";
    return 1;
  }
  alekseev::LIter< int64_t > sums_iter = alekseev::before_begin(sums);

  size_t j = 0;
  int64_t zero = 0ll;
  bool is_smth_printed = true;
  try {
    while (is_smth_printed) {
      is_smth_printed = false;

      ++sizes_iter;
      alekseev::insert_after(sums_iter, zero);
      for (size_t i = 0; i < matter_size; ++i) {
        if (j < *(++sizes_iter)) {
          int n = *(++iterators[i]);
          std::cout << n << " ";
          *sums_iter += n;
          is_smth_printed = true;
        }
      }
      if (is_smth_printed) {
        ++j;
        std::cout << "\n";
      }
    }
  } catch (const std::bad_alloc & e) {
    alekseev::destroy_matter_iter(matter_iter);
    delete[] iterators;
    alekseev::destroy(++sizes_iter);
    alekseev::destroy(++sums_iter);
    std::cerr << e.what() << "\n";
    return 1;
  }

  if (!j) {
    std::cout << "0\n";
  } else {
    ++sums_iter;
    std::cout << *(++sums_iter);
    for (size_t i = 1; i < j; ++i) {
      std::cout << " " << *(++sums_iter);
    }
    std::cout << "\n";
  }

  alekseev::destroy_matter_iter(matter_iter);
  delete[] iterators;
  alekseev::destroy(++sizes_iter);
  alekseev::destroy(++sums_iter);
}

void alekseev::destroy_matter_iter(LIter< PStrI > matter_iter)
{
  LIter< PStrI > start = ++matter_iter;
  while (++start != matter_iter) {
    List< int > * li = start->second;
    clear(li->next, li);
    rmfake(li);
  }
  destroy(matter_iter);
}
