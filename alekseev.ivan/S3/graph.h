#ifndef GRAPH_H
#define GRAPH_H

#include "hash_table.h"
#include <boost/uuid/sha1.hpp>

namespace alekseev {
  size_t hasher(std::pair<std::string, std::string> key);
  bool is_equal(std::pair<std::string, std::string> lhs, std::pair<std::string, std::string> rhs);

  struct Graph {
    private:
      HashTable<std::pair<std::string, std::string>, List< size_t >, hasher, is_equal> graph;
  };
}

#endif
