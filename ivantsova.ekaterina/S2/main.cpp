#include "operations.hpp"
#include <iostream>
#include <fstream>

int main(int argc, char* argv[])
{
  try {
    std::istream* input = &std::cin;
    std::ifstream file;
    if (argc >= 2) {
      file.open(argv[1]);
      if (!file.is_open()) {
        std::cerr << "Cannot open file" << "\n";
        return 1;
      }
      input = &file;
    }
    long long results[100];
    int count = 0;
    std::string line;
    while (std::getline(*input, line)) {
      if (line.empty() || line.find_first_not_of(" \t") == std::string::npos) {
        continue;
      }
      results[count++] = ivantsova::calculateExpression(line);
    }
    if (count > 0) {
      for (int i = count - 1; i >= 0; --i) {
        if (i != count -1) {
          std::cout << " ";
        }
        std::cout << results[i];
      }
      std::cout << "\n";
    }
    return 0;
  } catch (const std::exception& e) {
    std::cerr << e.what() << "\n";
    return 1;
  }
}
