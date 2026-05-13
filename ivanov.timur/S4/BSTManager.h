#ifndef BSTMANAGER_H
#define BSTMANAGER_H
#include <string>
#include <vector>
#include "BSTtree.h"


class BSTManager {
public:
  void loadFromFile(const std::string& filename);
  void execute(const std::string& line, bool& isAnything, bool silent);

private:
  std::vector<std::pair<std::string,
    BSTtree<int, std::string, std::less<int>>>> datasets;

  BSTtree<int, std::string, std::less<int>>* getDataset(const std::string& name);
  const BSTtree<int, std::string, std::less<int>>* getDatasetConst(const std::string& name) const;

  bool contains(const BSTtree<int, std::string, std::less<int>>& tree, int key) const;
};

#endif
