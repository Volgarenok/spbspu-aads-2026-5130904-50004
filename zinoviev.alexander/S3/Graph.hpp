#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <string>
#include <boost/hash2/sha1.hpp>
#include <boost/hash2/hash_append.hpp>
#include "hash_table.hpp"

namespace zinoviev
{
  struct StringHasher
  {
    std::size_t operator()(const std::string& p) const;
  };

  struct PairHasher
  {
    std::size_t operator()(const std::pair<std::string, std::string>& p) const;
  };

  class Graph
  {
    std::string name_;
    HashTable <std::string, bool, StringHasher, std::equal_to<std::string>> vertexes_;
    HashTable <std::pair<std::string, std::string>, Vector<unsigned long long>, PairHasher, std::equal_to<std::pair<std::string, std::string>>> edges_;
  public:

    Graph(const std::string name);
    Graph(const Graph& g);

    void add_vertex(const std::string& v);
    void add_edge(const std::string& from, const std::string& to, unsigned long long weight);
    const Vector<unsigned long long>* get_weights(const std::string& from, const std::string& to) const;

    bool has_vertex(const std::string& v) const;
    Vector<std::string> get_vertices() const;
    std::string get_name() const;
    Vector<std::pair<std::string, Vector<unsigned long long>>> get_outbound(const std::string& vertex) const;
    Vector<std::pair<std::string, Vector<unsigned long long>>> get_inbound(const std::string& vertex) const;
    void remove_edge(const std::pair<std::string, std::string>& p, unsigned long long weight);

    void swap(Graph& other) noexcept;
  };
}
#endif
