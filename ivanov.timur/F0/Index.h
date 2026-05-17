#ifndef INDEX_H
#define INDEX_H
#include "RBtree.h"

#include <fstream>
#include <sstream>
#include <vector>

class Index {
private:
  ivanov::RBtree<std::string, std::vector<int>> invIndex_;
  std::vector<std::string> wordOrder_;
  bool canReconstruct_;
  int totalWords_;

  std::string normalize_(const std::string& raw) {
    std::string out;
    for (char ch : raw) {
      if (std::isalnum(static_cast<unsigned char>(ch)))
        out += static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
    }
    return out;
  }

public:
  Index() : canReconstruct_(false), totalWords_(0) {}

  bool buildFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;
    clear();

    std::string line, word;
    int pos = 0;
    canReconstruct_ = true;

    while (std::getline(file, line)) {
      std::istringstream iss(line);
      while (iss >> word) {
        word = normalize_(word);
        if (word.empty()) continue;

        wordOrder_.push_back(word);

        auto* positions = invIndex_.search(word);
        if (positions) {
          positions->push_back(pos);
        } else {
          invIndex_.insert(word, std::vector<int>{pos});
        }
        ++pos;
      }
    }
    totalWords_ = pos;
    return true;
  }

  void clear() {
    invIndex_.clear();
    wordOrder_.clear();
    canReconstruct_ = false;
    totalWords_ = 0;
  }
};

#endif
