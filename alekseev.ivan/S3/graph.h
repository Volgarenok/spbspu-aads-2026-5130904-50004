#ifndef GRAPH_H
#define GRAPH_H

#include "hash_table.h"

namespace alekseev {
  using str = std::string;
  size_t hasher(const std::pair< str, str > & key);
  using hasher_ptr = size_t(*)(const std::pair< str, str > & key);
  bool is_equal(const std::pair< str, str > & lhs, const std::pair< str, str > & rhs);
  using is_equal_ptr = bool(*)(const std::pair< str, str > & lhs,
      const std::pair< str, str > & rhs);

  struct Graph {
    ~Graph();
    Graph(const Graph & rhs);
    Graph & operator=(const Graph & rhs);
    Graph(Graph && rhs) noexcept;
    Graph & operator=(Graph && rhs) noexcept;
    Graph();

    void swap(Graph & rhs) noexcept;

    private:
      List< str > * vertexes_;
      HashTable< std::pair< str, str >, List< size_t >, hasher_ptr, is_equal_ptr > edges_;
  };
}

#endif
