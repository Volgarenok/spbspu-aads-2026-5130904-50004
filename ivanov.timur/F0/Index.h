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

  std::string reconstructText() const {
    if (!canReconstruct_) return {};
    std::ostringstream oss;
    for (size_t i = 0; i < wordOrder_.size(); ++i) {
      if (i > 0) oss << ' ';
      oss << wordOrder_[i];
    }
    return oss.str();
  }
  const std::vector<int>* getPositions(const std::string& word) const {
    return invIndex_.search(word);
  }

  int totalWords() const { return totalWords_; }
  int uniqueWords() const { return invIndex_.size(); }
  bool canReconstruct() const { return canReconstruct_; }

  template<typename Func>
  void forEachEntry(Func f) const {
    invIndex_.forEach(f);
  }
};

#endif
