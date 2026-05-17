#ifndef INDEXHANDLER_H
#define INDEXHANDLER_H
#include "Index.h"
#include "RBtree.h"

class IndexHandler {
private:
  ivanov::RBtree<std::string, Index*> indexesTree_;

  Index* findIndex(const std::string& name) const {
    Index** ptr = indexesTree_.search(name);
    return ptr ? *ptr : nullptr;
  }

  void addIndex(const std::string& name, Index* newIdx) {
    if (findIndex(name)) {
      indexesTree_.remove(name);
      delete findIndex(name);
    }
    indexesTree_.insert(name, newIdx);
  }
public:

};

#endif
