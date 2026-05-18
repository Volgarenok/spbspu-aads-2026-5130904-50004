#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <string>
#include <functional>
#include "../S1/list.hpp"
#include "hash-table.hpp"
#include "siphash.hpp"

namespace ali
{
  struct EdgeKey
  {
    std::string from;
    std::string to;

    EdgeKey():
      from(),
      to()
    {}

    EdgeKey(const std::string & f, const std::string & t):
      from(f),
      to(t)
    {}
  };

  struct EdgeEqual
  {
    bool operator()(const EdgeKey & left, const EdgeKey & right) const
    {
      return left.from == right.from && left.to == right.to;
    }
  };

  struct EdgeHash
  {
    std::size_t operator()(const EdgeKey & key) const
    {
      SipHash hash;
      return hash(key.from) ^ (hash(key.to) << 1);
    }
  };

  class Graph
  {
  private:
    HashTable< EdgeKey, List< unsigned int >, EdgeHash, EdgeEqual > edges_;

  public:
    Graph():
      edges_(211)
    {}

    void bind(const std::string & from, const std::string & to, unsigned int weight)
    {
      EdgeKey key(from, to);

      if (!edges_.has(key))
      {
        List< unsigned int > weights;
        weights.push_back(weight);
        edges_.add(key, weights);
      }
      else
      {
        edges_.get(key).push_back(weight);
      }
    }

    bool has_edge(const std::string & from, const std::string & to)
    {
      return edges_.has(EdgeKey(from, to));
    }
  };
}

#endif
