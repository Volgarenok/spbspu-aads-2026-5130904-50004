#include <iostream>
#include <fstream>
#include <boost/uuid/sha1.hpp>
#include "hash_table.h"
#include "graph.h"

namespace alekseev {
  using str = std::string;
  using ht_graphs = HashTable< str, Graph, size_t (*)(const str &), bool (*)(str, str) >;
  size_t str_hasher(const str & name);
  Graph input_graph(std::ifstream & input);
  bool str_less(str a, str b);

  using command_type = void(*)(ht_graphs &, Vector< str >);
  void graphs(ht_graphs & graphs, Vector< str > args);
  void vertexes(ht_graphs & graphs, Vector< str > args);
  void bounds(ht_graphs & graphs, const Vector< str > & args, bool out);
  void outbound(ht_graphs & graphs, Vector< str > args);
  void inbound(ht_graphs & graphs, Vector< str > args);

  void bind(ht_graphs & graphs, Vector< str > args);
  void cut(ht_graphs & graphs, Vector< str > args);

  void create(ht_graphs & graphs, Vector< str > args);
  void merge(ht_graphs & graphs, Vector< str > args);
  void extract(ht_graphs & graphs, Vector< str > args);
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

void alekseev::graphs(ht_graphs & graphs, Vector< str > args)
{
  Vector< str > names = graphs.keys();
  names.bubbleSort(str_less);

  std::cout << names[0];
  for (size_t i = 1; i < names.getSize(); ++i) {
    std::cout << "\n" << names[i];
  }
}

void alekseev::vertexes(ht_graphs & graphs, Vector< str > args)
{
  if (args.isEmpty()) {
    throw std::invalid_argument("Invalid arguments");
  }
  if (!graphs.contains(args[0])) {
    throw std::invalid_argument("Invalid arguments");
  }
  List< str > * names = graphs.at(args[0]).vertexes();
  List< str > * current = names;
  Vector< str > vect_names;
  while (current->next != names) {
    current = current->next;
    vect_names.pushBack(current->data);
  }
  vect_names.bubbleSort(str_less);
  if (vect_names.isEmpty()) {
    return;
  }
  std::cout << vect_names[0];
  for (size_t i = 1; i < vect_names.getSize(); ++i) {
    std::cout << "\n" << vect_names[i];
  }
}

void alekseev::bounds(ht_graphs & graphs, const Vector< str > & args, bool out)
{
  if (args.getSize() != 2) {
    throw std::invalid_argument("Invalid arguments");
  }
  if (!graphs.contains(args[0])) {
    throw std::invalid_argument("Invalid arguments");
  }
  const Graph & graph = graphs.at(args[0]);
  if (!graph.has_vertex(args[1])) {
    throw std::invalid_argument("Invalid arguments");
  }
  Vector< std::pair< str, Vector< size_t > > > edges;
  if (out) {
    edges = graph.outbounds(args[1]);
  } else {
    edges = graph.inbounds(args[1]);
  }
  edges.bubbleSort(
      [](std::pair< str, Vector< size_t > > p1, std::pair< str, Vector< size_t > > p2) {
        return str_less(p1.first, p2.first);
      });
  for (size_t i = 0; i < edges.getSize(); ++i) {
    Vector< size_t > & weights = edges[i].second;
    std::cout << edges[i].first << " ";

    weights.bubbleSort([](size_t a, size_t b) {
      return a < b;
    });
    std::cout << weights[0];
    for (size_t j = 1; j < weights.getSize(); ++i) {
      std::cout << " " << weights[j];
    }
    if (i < edges.getSize() - 1) {
      std::cout << "\n";
    }
  }
}

void alekseev::outbound(ht_graphs & graphs, Vector< str > args)
{
  bounds(graphs, args, true);
}

void alekseev::inbound(ht_graphs & graphs, Vector< str > args)
{
  bounds(graphs, args, false);
}

void alekseev::bind(ht_graphs & graphs, Vector< str > args)
{
  if (args.getSize() != 4) {
    throw std::invalid_argument("Invalid arguments");
  }
  if (!graphs.contains(args[0])) {
    throw std::invalid_argument("Invalid arguments");
  }
  size_t weight = std::stoull(args[3]);

  Graph & graph = graphs.at(args[0]);
  bool added1 = false, added2 = false;
  try {
    if (!graph.has_vertex(args[1])) {
      graph.add_vertex(args[1]);
      added1 = true;
    }
    if (!graph.has_vertex(args[2])) {
      graph.add_vertex(args[2]);
      added2 = true;
    }
    graph.add_edge(args[1], args[2], weight);
  } catch (...) {
    if (added1) {
      graph.remove_vertex(args[1]);
    }
    if (added2) {
      graph.remove_vertex(args[2]);
    }
  }
}

void alekseev::cut(ht_graphs & graphs, Vector< str > args)
{
  if (args.getSize() != 4) {
    throw std::invalid_argument("Invalid arguments");
  }
  if (!graphs.contains(args[0])) {
    throw std::invalid_argument("Invalid arguments");
  }
  size_t weight = std::stoull(args[3]);
  Graph & graph = graphs.at(args[0]);
  if (!graph.has_vertex(args[1]) || !graph.has_vertex(args[2]) || !graph.has_edge(args[1], args[2],
      weight)) {
    throw std::invalid_argument("Invalid arguments");
  }
  graph.remove_edge(args[1], args[2], weight);
}

void alekseev::create(ht_graphs & graphs, Vector< str > args)
{
  if (args.isEmpty()) {
    throw std::invalid_argument("Invalid arguments");
  }
  if (graphs.contains(args[0])) {
    throw std::invalid_argument("Invalid arguments");
  }
  Graph graph;
  if (args.getSize() > 1) {
    if (args.getSize() != std::stoull(args[1]) + 2) {
      throw std::invalid_argument("Invalid arguments");
    }
    for (size_t i = 2; i < args.getSize(); ++i) {
      graph.add_vertex(args[i]);
    }
  }
  graphs.insert(args[0], graph);
}

void alekseev::merge(ht_graphs & graphs, Vector< str > args)
{
  if (args.getSize() != 3) {
    throw std::invalid_argument("Invalid arguments");
  }
  if (graphs.contains(args[0]) || !graphs.contains(args[1]) || !graphs.contains(args[2])) {
    throw std::invalid_argument("Invalid arguments");
  }
  Graph new_graph = merge_graphs(graphs.at(args[1]), graphs.at(args[2]));
  graphs.insert(args[0], new_graph);
}
