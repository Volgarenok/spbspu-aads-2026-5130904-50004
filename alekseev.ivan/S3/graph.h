#ifndef GRAPH_H
#define GRAPH_H

#include "hash_table.h"
#include <boost/uuid/sha1.hpp>

namespace alekseev {
  size_t hasher(const std::pair< std::string, std::string > & key);
  bool is_equal(const std::pair< std::string, std::string > & lhs,
      const std::pair< std::string, std::string > & rhs);

  struct Graph {
    ~Graph();
    Graph(const Graph & rhs);
    Graph & operator=(const Graph & rhs);
    Graph(Graph && rhs) noexcept;
    Graph & operator=(Graph && rhs) noexcept;

    void swap(Graph & rhs) noexcept;

    private:
      List< std::string > * vertexes_;
      HashTable< std::pair< std::string, std::string >, List< size_t >, hasher, is_equal > edges_;
  };

  size_t hasher(const std::pair< std::string, std::string > & key)
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
      result += digest1[i] + digest2[i];
    }
    return result;
  }

  bool is_equal(const std::pair< std::string, std::string > & lhs,
      const std::pair< std::string, std::string > & rhs)
  {
    return lhs.first == rhs.first && lhs.second == rhs.second || lhs.first == rhs.second && lhs.
        second == rhs.first;
  }

  Graph::~Graph()
  {
    if (vertexes_) {
      clear(vertexes_->next, vertexes_);
      rmfake(vertexes_);
    }
  }

  Graph::Graph(const Graph & rhs):
    vertexes_(deep_copy(rhs.vertexes_)),
    edges_(rhs.edges_)
  {
  }

  Graph & Graph::operator=(const Graph & rhs)
  {
    Graph temp(rhs);
    swap(temp);
    return *this;
  }

  Graph::Graph(Graph && rhs) noexcept:
    vertexes_(rhs.vertexes_),
    edges_(std::move(rhs.edges_))
  {
    rhs.vertexes_ = nullptr;
  }

  inline Graph & Graph::operator=(Graph && rhs) noexcept
  {
    swap(rhs);
    return *this;
  }

  inline void Graph::swap(Graph & rhs) noexcept
  {
    std::swap(vertexes_, rhs.vertexes_);
    edges_.swap(rhs.edges_);
  }
}

#endif
