#include <iostream>
#include <string>
#include <cctype>
#include "List.hpp"

using namespace em;

int main() {
  List<std::string> names;
  List<List<unsigned long long>> nums;
  std::string token;
  char c;
  bool is_new_line = true;

  while (std::cin.get(c)) {
    if (std::isspace(static_cast<unsigned char>(c))) {
      if (!token.empty()) {
        if (is_new_line) {
          names.push_back(token);
          nums.push_back(List<unsigned long long>());
          is_new_line = false;
        } else {
          try {
            size_t pos;
            unsigned long long val = std::stoull(token, &pos);
            if (pos == token.length()) {
              nums.back().push_back(val);
            }
          } catch (const std::out_of_range&) {
            std::cout << "\n";
            std::cerr << "Overflow\n";
            return 1;
          } catch (const std::exception&) {
          }
        }
        token.clear();
      }
      if (c == '\n') {
        is_new_line = true;
      }
    } else {
      token += c;
    }
  }

  if (!token.empty()) {
    if (is_new_line) {
      names.push_back(token);
      nums.push_back(List<unsigned long long>());
    } else {
      try {
        size_t pos;
        unsigned long long val = std::stoull(token, &pos);
        if (pos == token.length()) {
          nums.back().push_back(val);
        }
      } catch (const std::out_of_range&) {
        std::cout << "\n";
        std::cerr << "Overflow\n";
        return 1;
      } catch (const std::exception&) {
      }
    }
  }

  if (names.empty()) {
    std::cout << "0\n";
    return 0;
  }

  bool first_name = true;
  for (auto it = names.cbegin(); it != names.cend(); ++it) {
    if (!first_name) {
      std::cout << " ";
    }
    std::cout << *it;
    first_name = false;
  }
  std::cout << "\n";

  return 0;
}
