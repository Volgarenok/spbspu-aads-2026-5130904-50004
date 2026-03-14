#include <iostream>
#include <limits>
#include <string>
#include <utility>

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

      int num = 0;
      std::cin >> num;
      if (std::cin.fail()) {
        std::cerr << "Input error\n";
        return 1;
      }
      numbers.pushBack(num);
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
  pozdeev::LCIter<std::string> nameIt = listNames.cbegin();
  while (nameIt != listNames.cend()) {
    if (isFirstWord == false) {
      std::cout << " ";
    }
    std::cout << *nameIt;
    isFirstWord = false;
    ++nameIt;
  }
  std::cout << "\n";

  pozdeev::BiList<pozdeev::LIter<int>> iterators;
  pozdeev::LIter<pozdeev::BiList<int>> setupIt = listValues.begin();
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

    pozdeev::LIter<pozdeev::BiList<int>> seqIt = listValues.begin();
    pozdeev::LIter<pozdeev::LIter<int>> iterIt = iterators.begin();

    while (seqIt != listValues.end()) {
      if (*iterIt != (*seqIt).end()) {
        hasElements = true;
        int val = *(*iterIt);
        currentLine.pushBack(val);

        if (currentSum > (std::numeric_limits<long long>::max() - val)) {
          std::cerr << "Sum is too big\n";
          return 2;
        }
        currentSum = currentSum + val;

        ++(*iterIt);
      }
      ++seqIt;
      ++iterIt;
    }

    if (hasElements == false) {
      break;
    }
}
