#include <iostream>
#include <fstream>
#include <boost/uuid/sha1.hpp>
#include "hash_table.h"
#include "graph.h"

namespace alekseev {
  using str = std::string;
  size_t str_hasher(const str & name);
  Graph input_graph(std::ifstream & input);
  bool str_less(str a, str b);


}

int main()
{
}

size_t alekseev::str_hasher(const str & name)
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

bool alekseev::str_less(str a, str b)
{
  return a < b;
}

std::ostream & alekseev::graphs(std::ostream & output, Vector< str > names)
{
  if (names.isEmpty()) {
    return output;
  }
  names.bubbleSort(str_less);

  output << names[0];
  for (size_t i = 1; i < names.getSize(); ++i) {
    output << "\n" << names[i];
  }
  return output;
}

std::ostream & alekseev::vertexes(std::ostream & output, List< str > * names)
{
  List< str > * current = names->next;
  Vector< str > vect;
  while (current != names) {
    vect.pushBack(current->data);
  }
  vect.bubbleSort(str_less);
  output << vect[0];
  for (size_t i = 1; i < vect.getSize(); ++i) {
    output << "\n" << vect[i];
  }
  return output;
}

std::ostream & alekseev::outbounds(std::ostream & output,
    Vector< std::pair< str, Vector< size_t > > > edges)
{
  edges.bubbleSort(
      [](std::pair< str, Vector< size_t > > p1, std::pair< str, Vector< size_t > > p2) {
        return str_less(p1.first, p2.first);
      });
  for (size_t i = 0; i < edges.getSize(); ++i) {
    Vector< size_t > & weights = edges[i].second;
    if (weights.isEmpty()) {
      output << edges[i].first << "\n";
      continue;
    }
    output << edges[i].first << " ";

    weights.bubbleSort([](size_t a, size_t b) {
      return a < b;
    });
    output << weights[0];
    for (size_t j = 1; j < weights.getSize(); ++i) {
      output << " " << weights[j];
    }
    if (i < edges.getSize() - 1) {
      output << "\n";
    }
  }
  return output;
}
