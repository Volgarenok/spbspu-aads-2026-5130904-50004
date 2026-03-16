#include <iostream>
#include <limits>
#include "ListIterators.h"

namespace alekseev {
  using PStr_ull = std::pair< std::string, List< size_t > * >;
  const size_t MAX_SIZE_T = std::numeric_limits< size_t >::max();
  void destroy_matter_iter(LIter< PStr_ull > matter_iter);
}

int main()
{
  alekseev::List< alekseev::PStr_ull > * matter_list = alekseev::fake< alekseev::PStr_ull >();
  alekseev::LIter< alekseev::PStr_ull > matter_iter = alekseev::before_begin(matter_list);
  size_t matter_size = 0;
  alekseev::List< size_t > * sizes = nullptr;
  try {
    sizes = alekseev::fake< size_t >();
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
    alekseev::List< size_t > * some_list = nullptr;
    try {
      some_list = alekseev::fake< size_t >();
    } catch (const std::bad_alloc & e) {
      alekseev::destroy_matter_iter(matter_iter);
      alekseev::destroy(++sizes_iter);
      std::cerr << e.what() << "\n";
      return 1;
    }
    alekseev::LIter< size_t > some_iter = alekseev::before_begin(some_list);

    try {
      size_t number = 0;
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
        some_iter = alekseev::insert_after(some_iter, number);
        ++current_size;
      }
      alekseev::PStr_ull tmp(name, some_list);
      alekseev::insert_after< alekseev::PStr_ull >(matter_iter, tmp);
      ++matter_size;
      alekseev::insert_after(sizes_iter, current_size);
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
  alekseev::LCIter< size_t > * iterators = new alekseev::LCIter< size_t >[matter_size];
  for (size_t i = 0; i < matter_size; ++i) {
    iterators[i] = alekseev::before_begin((++matter_iter)->second);
  }

  alekseev::List< size_t > * sums = nullptr;
  try {
    sums = alekseev::fake< size_t >();
  } catch (const std::bad_alloc & e) {
    alekseev::destroy_matter_iter(matter_iter);
    delete[] iterators;
    alekseev::destroy(++sizes_iter);
    std::cerr << e.what() << "\n";
    return 1;
  }
  alekseev::LIter< size_t > sums_iter = alekseev::before_begin(sums);

  size_t j = 0;
  size_t zero = 0ll;
  bool is_smth_was = true;
  try {
    while (is_smth_was) {
      is_smth_was = false;

      ++sizes_iter;
      alekseev::insert_after(sums_iter, zero);
      for (size_t i = 0; i < matter_size; ++i) {
        if (j < *(++sizes_iter)) {
          size_t n = *(++iterators[i]);
          if (alekseev::MAX_SIZE_T - n > *sums_iter) {
            *sums_iter += n;
          } else {
            alekseev::destroy_matter_iter(matter_iter);
            delete[] iterators;
            alekseev::destroy(++sizes_iter);
            alekseev::destroy(++sums_iter);
            std::cerr << "cannot count sum. size_t overflow!\n";
            return 1;
          }
          is_smth_was = true;
        }
      }
      if (is_smth_was) {
        ++j;
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
    std::cout << matter_list->next->data.first << "\n";
    std::cout << "0\n";
  } else {
    ++matter_iter;
    std::cout << (++matter_iter)->first;
    for (size_t i = 1; i < matter_size; ++i) {
      std::cout << " " << (++matter_iter)->first;
    }
    std::cout << "\n";

    for (size_t i = 0; i < matter_size; ++i) {
      ++iterators[i];
    }
    for (size_t i = 0; i < j; ++i) {
      ++sizes_iter;
      if (i < *(++sizes_iter)) {
        std::cout << *(++iterators[0]);
      }
      for (size_t k = 1; k < matter_size; ++k) {
        if (i < *(++sizes_iter)) {
          std::cout << " " << *(++iterators[k]);
        }
      }
      std::cout << "\n";
    }

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

void alekseev::destroy_matter_iter(LIter< PStr_ull > matter_iter)
{
  LIter< PStr_ull > start = ++matter_iter;
  while (++start != matter_iter) {
    List< size_t > * li = start->second;
    clear(li->next, li);
    rmfake(li);
  }
  destroy(matter_iter);
}
