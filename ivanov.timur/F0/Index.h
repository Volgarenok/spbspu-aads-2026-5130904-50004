#ifndef INDEX_H
#define INDEX_H
#include "RBtree.h"

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
};

#endif
