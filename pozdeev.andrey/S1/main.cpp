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
}
