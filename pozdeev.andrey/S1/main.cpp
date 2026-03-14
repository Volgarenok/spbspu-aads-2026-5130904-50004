#include <iostream>
#include <limits>
#include <string>
#include <utility>
#include <stdexcept>

#include "biList.hpp"

int main()
{
  pozdeev::BiList<std::string> listNames;
  pozdeev::BiList<pozdeev::BiList<int>> listValues;
  std::string currentName;

  while (std::cin >> currentName) {
    pozdeev::BiList<int> numbers;
    int ch = std::cin.get();
    while (ch != std::char_traits<char>::eof() && ch != '\n') {
      if (std::isspace(ch)) {
        ch = std::cin.get();
        continue;
      }
      std::cin.unget();

      std::string token;
      int inner_ch = std::cin.get();
      while (inner_ch != std::char_traits<char>::eof() && !std::isspace(inner_ch)) {
        token += static_cast<char>(inner_ch);
        inner_ch = std::cin.get();
      }
      if (inner_ch != std::char_traits<char>::eof()) {
        std::cin.unget();
      }

      try {
        size_t pos;
        long long num = std::stoll(token, &pos);
        if (pos != token.length()) {
          std::cerr << "Invalid input\n";
          return 1;
        }
        if (num > std::numeric_limits<int>::max() || num < std::numeric_limits<int>::min()) {
           std::cerr << "Overflow\n";
           return 1;
        }
        numbers.pushBack(static_cast<int>(num));
      } catch (const std::out_of_range&) {
         std::cerr << "Overflow\n";
         return 1;
      } catch (const std::invalid_argument&) {
         std::cerr << "Invalid input\n";
         return 1;
      }

      ch = std::cin.get();
    }
    listNames.pushBack(currentName);
    listValues.pushBack(std::move(numbers));
  }

  if (listNames.isEmpty()) {
    std::cout << "0\n";
    return 0;
  }

  bool isFirstWord = true;
  auto nameIt = listNames.cbegin();
  while (nameIt != listNames.cend()) {
    if (!isFirstWord) {
      std::cout << " ";
    }
    std::cout << *nameIt;
    isFirstWord = false;
    ++nameIt;
  }
  std::cout << "\n";

  bool hasAnyNumbers = false;
  auto checkIt = listValues.begin();
  while (checkIt != listValues.end()) {
    if (!(*checkIt).isEmpty()) {
      hasAnyNumbers = true;
      break;
    }
    ++checkIt;
  }

  if (!hasAnyNumbers) {
    std::cout << "0\n";
    return 0;
  }

  pozdeev::BiList<pozdeev::LIter<int>> iterators;
  auto setupIt = listValues.begin();
  while (setupIt != listValues.end()) {
    iterators.pushBack((*setupIt).begin());
    ++setupIt;
  }

  pozdeev::BiList<long long> allSums;
  bool hasElements = true;

  while (hasElements) {
    hasElements = false;
    long long currentSum = 0;
    pozdeev::BiList<int> currentLine;

    auto seqIt = listValues.begin();
    auto iterIt = iterators.begin();

    while (seqIt != listValues.end()) {
      if (*iterIt != (*seqIt).end()) {
        hasElements = true;
        int val = *(*iterIt);
        currentLine.pushBack(val);

        if (val > 0 && currentSum > (std::numeric_limits<long long>::max() - val)) {
          std::cerr << "Sum overflow\n";
          return 1;
        }
        if (val < 0 && currentSum < (std::numeric_limits<long long>::min() - val)) {
          std::cerr << "Sum overflow\n";
          return 1;
        }

        currentSum += val;
        ++(*iterIt);
      }
      ++seqIt;
      ++iterIt;
    }

    if (!hasElements) break;

    bool isFirstNum = true;
    auto printIt = currentLine.cbegin();
    while (printIt != currentLine.cend()) {
      if (!isFirstNum) std::cout << " ";
      std::cout << *printIt;
      isFirstNum = false;
      ++printIt;
    }
    std::cout << "\n";
    allSums.pushBack(currentSum);
  }

  bool isFirstSum = true;
  auto sumIt = allSums.cbegin();
  while (sumIt != allSums.cend()) {
    if (!isFirstSum) std::cout << " ";
    std::cout << *sumIt;
    isFirstSum = false;
    ++sumIt;
  }
  std::cout << "\n";

  return 0;
}
