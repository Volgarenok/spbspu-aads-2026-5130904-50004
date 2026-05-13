#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "vector.hpp"
#include "hashTable.hpp"
#include <string>
#include <utility>

namespace kuchukbaeva {

  struct EdgeHash {
    std::size_t operator()(const std::pair< std::string, std::string >& p) const
    {
      boost::hash2::siphash_64 hasher;
      boost::hash2::hash_append(hasher, {}, p.first);
      boost::hash2::hash_append(hasher, {}, p.second);
      return hasher.result();
    }
  };

  struct EdgeEqual {
    bool operator()(const std::pair< std::string, std::string >& a, const std::pair< std::string, std::string >& b) const
    {
      return a.first == b.first && a.second == b.second;
    }
  };

  struct Graph {
    Vector< std::string > vertexes;
    HashTable< std::pair< std::string, std::string >, Vector< unsigned int >, EdgeHash, EdgeEqual > edges;

    Graph() :
      vertexes(),
      edges(16)
    {
    }
  };

}

#endif
