#ifndef BSTMANAGER_H
#define BSTMANAGER_H
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "BSTtree.h"


class BSTManager {
  using tree = BSTtree<int, std::string, std::less<int>>;
public:
  void loadFromFile(const std::string& filename);
  void execute(const std::string& line, bool& isAnything, bool silent);

private:
  std::vector<std::pair<std::string, tree>> datasets;

  tree* getDataset(const std::string& name);
  const tree* getDatasetConst(const std::string& name) const;

  bool contains(const tree& tr, int key) const;
};

inline void BSTManager::loadFromFile(const std::string &filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "File opening error";
    std::exit(1);
  }

  std::string line;
  while (std::getline(file, line)) {
    if (line.empty()) continue;
    std::istringstream iss(line);
    std::string dname;
    if (!(iss >> dname)) continue;

    tree* tr = getDataset(dname);
    if (!tr) {
      datasets.push_back(std::make_pair(dname, tree()));
      tr = &datasets.back().second;
    }

    int key;
    std::string val;
    while (iss >> key >> val) {
      tr->push(key, val);
    }
  }
}

#endif
