#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "HashTable.hpp"
#include "vector.hpp"
#include "SipHash.hpp"
#include "Equal.hpp"
#include <utility>
#include <string>

namespace haliullin
{
  class Graph
  {
  public:
    ~Graph() = default;
    Graph();

    void addVertex(const std::string& name);
    bool hasVertex(const std::string& name) const;
    void removeVertex(const std::string& name);

    void addEdge(const std::string& from, const std::string& to, unsigned long long weight);
    void removeEdge(const std::string& from, const std::string& to, unsigned long long weight);

    Vector< std::string > getVertices() const;

    Graph merge(const Graph& other) const;
    Graph extract(const Vector< std::string >& vertices) const;

  private:
    Vector< std::string > vertices_;
    HashTable< std::pair< std::string, std::string >, Vector< unsigned long long >, SipHash, Equal > edges_;
  };
}

#endif
