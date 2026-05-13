#ifndef GRAPH_H
#define GRAPH_H

#include "hash_table.h"
#include <boost/uuid/sha1.hpp>

namespace alekseev {
  size_t hasher(std::pair< std::string, std::string > key);
  bool is_equal(std::pair< std::string, std::string > lhs,
      std::pair< std::string, std::string > rhs);

  struct Graph {
    private:
      HashTable< std::pair< std::string, std::string >, List< size_t >, hasher, is_equal > graph;
  };

  size_t hasher(std::pair< std::string, std::string > key)
  {
    boost::uuids::detail::sha1 first;
    first.process_bytes(key.first.c_str(), key.first.size());
    size_t digest1[5];
    first.get_digest(digest1);

    boost::uuids::detail::sha1 second;
    second.process_bytes(key.first.c_str(), key.first.size());
    size_t digest2[5];
    first.get_digest(digest2);

    size_t result = 0;
    for (int i = 0; i < 5; i++) {
      result ^= digest1[i];
      result ^= digest2[i];
    }
    return result;
  }
}

#endif
