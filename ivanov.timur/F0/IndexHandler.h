#ifndef INDEXHANDLER_H
#define INDEXHANDLER_H
#include "Index.h"
#include "RBtree.h"

#include <algorithm>
#include <cmath>

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
    }); //i know tp, big smart
    return result;
  }

  void searchTFIDF(const std::string& query) {
    std::istringstream iss(query);
    std::vector<std::string> queryWords;
    std::string w;
    while (iss >> w) {
        std::string norm = Index::normalize_(w);
        if (!norm.empty()) queryWords.push_back(norm);
    }
    if (queryWords.empty()) {
        std::cout << "Empty query\n";
        return;
    }

    auto indexes = getAllIndexes();
    int N = static_cast<int>(indexes.size());
    if (N == 0) {
        std::cout << "No active indexes\n";
        return;
    }

    ivanov::RBtree<std::string, double> idfTree;
    std::vector<std::string> uniqueWords;
    for (const auto& qw : queryWords) {
        bool found = false;
        for (const auto& uw : uniqueWords) {
            if (uw == qw) { found = true; break; }
        }
        if (!found) uniqueWords.push_back(qw);
    }

    for (const auto& word : uniqueWords) {
        int df = 0;
        for (const auto& p : indexes) {
            if (p.second->contains(word)) ++df;
        }
        double idf = (df > 0) ? std::log(static_cast<double>(N) / df) : 0.0;
        idfTree.insert(word, idf);
    }

    std::vector<std::pair<std::string, double>> scores;
    for (const auto& p : indexes) {
        double score = 0.0;
        int totalWords = p.second->totalWords();
        if (totalWords == 0) continue;
        idfTree.forEach([&](const std::string& word, double idf) {
            int tf = p.second->wordFrequency(word);
            if (tf > 0) {
                double tfNorm = static_cast<double>(tf) / totalWords;
                score += tfNorm * idf;
            }
        });
        if (score > 0.0) {
            scores.emplace_back(p.first, score);
        }
    }
    std::sort(scores.begin(), scores.end(),
              [](const auto& a, const auto& b) { return a.second > b.second; });

    std::cout << "Search results for '" << query << "':\n";
    if (scores.empty()) {
        std::cout << "  (no matches)\n";
    } else {
        for (const auto& sc : scores) {
            std::cout << "- " << sc.first << " (score: " << sc.second << ")\n";
        }
    }
}
public:
    IndexHandler() = default;
    ~IndexHandler() {
        indexesTree_.forEach([this](const std::string& name, Index* idx) {
            delete idx;
        });
    }
    void search(const std::string& query) {
        searchTFIDF(query);
    }

    void readIndex(const std::string& name, const std::string& filename) {
        Index* existing = findIndex(name);
        if (existing) {
            indexesTree_.remove(name);
            delete existing;
        }

        Index* newIdx = new Index();
        if (!newIdx->buildFromFile(filename)) {
            std::cerr << "Error: cannot open file " << filename << "\n";
            delete newIdx;
            return;
        }
        indexesTree_.insert(name, newIdx);
        std::cout << "Index '" << name << "' created from " << filename << " (" << newIdx->totalWords() << " words)" << "\n";
    }

};

#endif
