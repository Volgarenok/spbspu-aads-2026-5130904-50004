#ifndef CODE_H
#define CODE_H

#include <iostream>
#include <string>
#include <stdexcept>
#include "List.h"

using namespace ivanov;

inline int run(std::istream& in, std::ostream& out, std::ostream& err) {
  std::string token;
  List<std::string> names;
  List<List<int>> nums;

  try {
    if (!(in >> token)) return 0;

    names.push_back(token);
    List<int> currentList;
    while (in >> token) {
      try {
        size_t pos;
        int val = std::stoi(token, &pos);
        if (pos == token.length()) {
          currentList.push_back(val);
        } else {
          throw std::invalid_argument("not a number");
        }
      } catch (const std::invalid_argument&) {
        nums.push_back(std::move(currentList));
        names.push_back(token);
        currentList = List<int>();
      } catch (const std::out_of_range&) {
        throw;
      }
    }
    nums.push_back(std::move(currentList));
  } catch (const std::exception& e) {
    err << "Error\n";
    return 1;
  }

  if (names.empty()) return 0;

  bool first_name = true;
  for (auto it = names.cbegin(); it != names.cend(); ++it) {
    if (!first_name) out << " ";
    out << *it;
    first_name = false;
  }
  out << "\n";

  size_t max_size = 0;
  List<CIter<int>> iters;
  for (auto it = nums.cbegin(); it != nums.cend(); ++it) {
    if (it->size() > max_size) max_size = it->size();
    iters.push_back(it->cbegin());
  }

  if (max_size == 0) return 0;

  List<int> sums;
  try {
    for (size_t col = 0; col < max_size; ++col) {
      int current_sum = 0;
      bool first_in_row = true;

      if (!iters.empty()) {
        auto iters_it = iters.begin();
        auto nums_it = nums.cbegin();

        for (size_t i = 0; i < iters.size(); ++i) {
          if (*iters_it != nums_it->cend()) {
            if (!first_in_row) out << " ";
            out << **iters_it;
            ivanov::sum(current_sum, **iters_it);
            first_in_row = false;
            ++(*iters_it);
          }
          if (i < iters.size() - 1) {
            ++iters_it;
            ++nums_it;
          }
        }
      }

      if (!first_in_row) {
        out << "\n";
        sums.push_back(current_sum);
      } else {
        break;
      }
    }
  } catch (const std::bad_alloc&) {
    err << "Bad allocation failure\n";
    return 1;
  } catch (const std::exception&) {
    err << "Error during sum processing\n";
    return 1;
  } catch (...) {
    err << "Something went wrong\n";
    return 1;
  }

  bool first_sum = true;
  for (auto it = sums.cbegin(); it != sums.cend(); ++it) {
    if (!first_sum) out << " ";
    out << *it;
    first_sum = false;
  }
  out << "\n";

  return 0;
}

#endif
