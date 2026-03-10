#include "List.h"

#include <iostream>
#include <limits>
#include <string>
#include <utility>

namespace
{
  using number_t = unsigned long long;
  using number_list_t = oztas::List< number_t >;
  using named_list_t = std::pair< std::string, number_list_t >;
  using cursor_t = std::pair< oztas::LCIter< number_t >, oztas::LCIter< number_t > >;

  bool addChecked(number_t& lhs, const number_t rhs)
  {
    if (std::numeric_limits< number_t >::max() - lhs < rhs) {
      return false;
    }
    lhs += rhs;
    return true;
  }
}

int main()
{
  oztas::List< named_list_t > sequences;
  std::string name;

  while (std::cin >> name) {
    number_list_t numbers;
    oztas::LIter< number_t > last = numbers.beforeBegin();

    while (true) {
      int symbol = std::cin.peek();

      while ((symbol == ' ') || (symbol == '\t') || (symbol == '\r')) {
        std::cin.get();
        symbol = std::cin.peek();
      }

      if (symbol == '\n') {
        std::cin.get();
        break;
      }

      if (symbol == std::char_traits< char >::eof()) {
        break;
      }

      number_t value = 0;
      if (!(std::cin >> value)) {
        std::cerr << "Input error\n";
        return 1;
      }

      last = numbers.insertAfter(last, value);
    }

    sequences.pushBack(named_list_t(name, std::move(numbers)));

    if (!std::cin) {
      break;
    }
  }

  if (sequences.empty()) {
    std::cout << "0\n";
    return 0;
  }

  bool first_name = true;
  for (oztas::LCIter< named_list_t > it = sequences.begin(); it != sequences.end(); ++it) {
    if (!first_name) {
      std::cout << ' ';
    }
    std::cout << it->first;
    first_name = false;
  }
  std::cout << "\n";

  oztas::List< cursor_t > cursors;
  for (oztas::LCIter< named_list_t > it = sequences.begin(); it != sequences.end(); ++it) {
    cursors.pushBack(cursor_t(it->second.begin(), it->second.end()));
  }

  oztas::List< number_t > sums;

  while (true) {
    bool has_values = false;
    bool first_value = true;
    number_t row_sum = 0;

    for (oztas::LIter< cursor_t > it = cursors.begin(); it != cursors.end(); ++it) {
      if (it->first != it->second) {
        const number_t value = *(it->first);

        if (!first_value) {
          std::cout << ' ';
        }
        std::cout << value;
        first_value = false;
        has_values = true;

        if (!addChecked(row_sum, value)) {
          std::cerr << "Overflow\n";
          return 1;
        }

        ++(it->first);
      }
    }

    if (!has_values) {
      break;
    }

    std::cout << "\n";
    sums.pushBack(row_sum);
  }

  bool first_sum = true;
  for (oztas::LCIter< number_t > it = sums.begin(); it != sums.end(); ++it) {
    if (!first_sum) {
      std::cout << ' ';
    }
    std::cout << *it;
    first_sum = false;
  }
  std::cout << "\n";

  return 0;
}
