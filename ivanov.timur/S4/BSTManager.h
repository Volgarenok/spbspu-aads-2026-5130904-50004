#ifndef BSTMANAGER_H
#define BSTMANAGER_H
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "BSTtree.h"

inline void invalid() {
  std::cout << "<INVALID COMMAND>\n";
}

class BSTManager {
  using tree = BSTtree<int, std::string, std::less<int>>;
public:
  void loadFromFile(const std::string& filename);
  void execute(const std::string& line, bool& isAnything, bool silent);

private:
  std::vector<std::pair<std::string, tree>> datasets;

  tree* getDataset(const std::string& name);
  const tree* getDatasetConst(const std::string& name) const;

  const bool contains(const tree& tr, int key) const;
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

inline void BSTManager::execute(const std::string &line, bool &isAnything, bool silent) {
  std::istringstream iss(line);
  std::string cmd;
  if (!(iss >> cmd)) return;

  if (cmd == "print") {
    std::string dname;
    if (!(iss >> dname)) {
      if (!silent) invalid();
      return;
    }

    const tree* tr = getDatasetConst(dname);
    if (!tr) {
      if (!silent) invalid();
      return;
    }

    tree::const_iterator begin = tr->begin();
    tree::const_iterator end = tr->end();

    if (begin == end) {
      if (!silent) invalid();
      else isAnything = false;
      return;
    }
    if (silent) {
      isAnything = true;
      return;
    }

    std::cout << dname << ' ';
    for (tree::const_iterator it = begin; it != end; ++it) {
      std::pair<const int&, std::string&> kv = *it;
      std::cout << kv.first << ' ' << kv.second;
    }
    std::cout << '\n';
  }
  else if (...)
}

inline BSTManager::tree * BSTManager::getDataset(const std::string &name) {
  for (size_t i = 0; i < datasets.size(); ++i)
    if (datasets[i].first == name) return &datasets[i].second;
  return nullptr;
}

inline const BSTManager::tree * BSTManager::getDatasetConst(const std::string &name) const {
  for (size_t i = 0; i < datasets.size(); ++i)
    if (datasets[i].first == name) return &datasets[i].second;
  return nullptr;
}

inline const bool BSTManager::contains(const tree &tr, int key) const {
  try {
    tr.get(key);
    return true;
  } catch (...) {
    return false;
  }
}

#endif
