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

  Index* buildFromWords(const std::vector<std::string>& words, bool skipMarkers) {
    Index* idx = new Index();
    int pos = 0;
    for (const std::string& w : words) {
      idx->addWordToOrder(w);
      if (skipMarkers && w == "\n") {
        continue;
      }
      auto* vec = idx->getPositionsForUpdate(w);
      if (vec) {
        vec->push_back(pos);
      } else {
        idx->addEntry(w, std::vector<int>{pos});
      }
      ++pos;
    }
    idx->setTotalWords(pos);
    idx->setReconstructable(true);
    return idx;
  }

  std::vector<std::pair<std::string, Index*>> getAllIndexes() const {
    std::vector<std::pair<std::string, Index*>> result;
    indexesTree_.forEach([&](const std::string& name, Index* idx) {
        result.emplace_back(name, idx);
    });
    return result;
  }
public:

};

#endif
