#include <iostream>
#include <fstream>
#include <boost/uuid/sha1.hpp>
#include "hash_table.h"
#include "graph.h"

namespace alekseev {
  using str = std::string;
  size_t graph_name_hasher(const str & name);
  Graph input_graph(std::ifstream & input);

  std::ostream & graphs(std::ostream & output, Vector< str > & names);
  std::ostream & vertexes(std::ostream & output, List< str > * names);
  std::ostream & outbounds(std::ostream & output,
      Vector< std::pair< str, Vector< size_t > > > * edges);
  std::ostream & inbounds(std::ostream & output,
      Vector< std::pair< str, Vector< size_t > > > * edges);
  void bound(Graph & graph, const str & vertex1, const str & vertex2, size_t weight);
  void cut(Graph & graph, const str & vertex1, const str & vertex2, size_t weight);
  void create(
      HashTable< str, Graph, size_t(*)(const str &), bool (*)(const str &, const str &) > & ht,
      const str & name);
  void merge(
      HashTable< str, Graph, size_t(*)(const str &), bool (*)(const str &, const str &) > & ht,
      const str & new_name, const str & name1, const str & name2);
  void extract(
      HashTable< str, Graph, size_t(*)(const str &), bool (*)(const str &, const str &) > & ht,
      const str & new_name, const str & name, Vector< str > * vertexes);
}

int main()
{
}

size_t alekseev::graph_name_hasher(const str & name)
{
  boost::uuids::detail::sha1 h;
  h.process_bytes(name.c_str(), name.size());
  unsigned int digest[5];
  h.get_digest(digest);

  size_t result = 0;
  for (int i = 0; i < 5; i++) {
    result ^= digest[i];
  }
  return result;
}
