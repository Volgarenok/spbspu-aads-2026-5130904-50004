#include "graph.h"
#include "../common/ListIterators.h"
#include <cstring>
#include <boost/hash2/hash_append.hpp>
#include <boost/hash2/sha1.hpp>
#include <boost/hash2/flavor.hpp>
#include <boost/hash2/get_integral_result.hpp>

size_t alekseev::str_hasher(const str & name)
{
  boost::hash2::sha1_160 sha;

  boost::hash2::hash_append(sha, {}, name);
  return boost::hash2::get_integral_result< size_t >(sha);
}

size_t alekseev::hasher(const std::pair< str, str > & key)
{
  return str_hasher(key.first) ^ (str_hasher(key.second) << 1);
}

bool alekseev::is_equal(const std::pair< str, str > & lhs, const std::pair< str, str > & rhs)
{
  return lhs.first == rhs.first && lhs.second == rhs.second;
}

alekseev::Graph::~Graph()
{
  if (vertexes_) {
    clear(vertexes_->next, vertexes_);
    rmfake(vertexes_);
  }
}

alekseev::Graph::Graph(const Graph & rhs):
  vertexes_(deep_copy(rhs.vertexes_)),
  edges_(rhs.edges_)
{
}

alekseev::Graph & alekseev::Graph::operator=(const Graph & rhs)
{
  Graph temp(rhs);
  swap(temp);
  return *this;
}

alekseev::Graph::Graph(Graph && rhs) noexcept:
  vertexes_(rhs.vertexes_),
  edges_(std::move(rhs.edges_))
{
  rhs.vertexes_ = nullptr;
}

alekseev::Graph & alekseev::Graph::operator=(Graph && rhs) noexcept
{
  swap(rhs);
  return *this;
}

alekseev::Graph::Graph():
  vertexes_(fake< str >()),
  edges_(&hasher, &is_equal, 1024)
{
}

void alekseev::Graph::swap(Graph & rhs) noexcept
{
  std::swap(vertexes_, rhs.vertexes_);
  edges_.swap(rhs.edges_);
}

void alekseev::Graph::ins_vertex(const str & vertex)
{
  LIter< str > fake = before_begin(vertexes_);
  LIter< str > current = fake;
  while (++current != fake) {
    if (*current == vertex) {
      return;
    }
  }
  add_vertex(vertex);
}

void alekseev::Graph::add_vertex(const str & vertex)
{
  insert_after(vertexes_, vertex);
}

void alekseev::Graph::add_edge(const str & vertex1, const str & vertex2, size_t weight)
{
  try {
    edges_.at(std::pair< str, str >(vertex1, vertex2)).pushBack(weight);
  } catch (std::out_of_range & e) {
    edges_.insert(std::pair< str, str >(vertex1, vertex2), Vector< size_t >(1, weight));
  }
}

void alekseev::Graph::ins_edge(const str & vertex1, const str & vertex2, size_t weight)
{
  if (!has_vertex(vertex1) || !has_vertex(vertex2)) {
    throw std::invalid_argument("Invalid vertex");
  }
  add_edge(vertex1, vertex2, weight);
}

void alekseev::Graph::add_edges(const str & vertex1, const str & vertex2, Vector< size_t > weights)
{
  for (size_t i = 0; i < weights.getSize(); ++i) {
    add_edge(vertex1, vertex2, weights[i]);
  }
}

bool alekseev::Graph::has_vertex(const str & vertex) const
{
  LIter< str > fake = before_begin(vertexes_);
  LIter< str > current = fake;
  while (++current != fake) {
    if (*current == vertex) {
      return true;
    }
  }
  return false;
}

bool alekseev::Graph::has_some_edge(const str & vertex1, const str & vertex2) const
{
  return edges_.contains(std::pair< str, str >(vertex1, vertex2));
}

bool alekseev::Graph::has_edge(const str & vertex1, const str & vertex2, size_t weight) const
{
  try {
    Vector< size_t > weights = edges_.at(std::pair< str, str >(vertex1, vertex2));
    for (size_t i = 0; i < weights.getSize(); ++i) {
      if (weights[i] == weight) {
        return true;
      }
    }
    return false;
  } catch (std::out_of_range & e) {
    return false;
  }
}

void alekseev::Graph::remove_vertex(const str & vertex)
{
  List< str > * current = vertexes_;
  while (current->next != vertexes_ && current->next->data != vertex) {
    current = current->next;
  }
  if (current->next != vertexes_) {
    erase_after(current);
    current = vertexes_->next;
    while (current != vertexes_) {
      edges_.remove(std::pair< str, str >(vertex, current->data));
      edges_.remove(std::pair< str, str >(current->data, vertex));
      current = current->next;
    }
    edges_.remove(std::pair< str, str >(vertex, vertex));
  }
}

void alekseev::Graph::remove_edge(const str & vertex1, const str & vertex2, size_t weight)
{
  Vector< size_t > & edges = edges_.at(std::pair< str, str >(vertex1, vertex2));
  size_t id = 0;
  while (id < edges.getSize()) {
    if (edges[id] == weight) {
      break;
    }
    ++id;
  }
  if (id < edges.getSize()) {
    edges.erase(id);
    if (edges.isEmpty()) {
      edges_.remove(std::pair< str, str >(vertex1, vertex2));
    }
  }
}

alekseev::Vector< std::pair< alekseev::str, alekseev::Vector< size_t > > >
alekseev::Graph::outbounds(const str & vertex) const
{
  Vector< std::pair< str, Vector< size_t > > > res;
  List< str > * current = vertexes_->next;
  while (current != vertexes_) {
    std::pair< str, str > edge(vertex, current->data);
    if (edges_.contains(edge)) {
      Vector< size_t > weights = edges_.at(edge);
      res.pushBack(std::pair< str, Vector< size_t > >(current->data, weights));
    }
    current = current->next;
  }
  return res;
}

alekseev::Vector< std::pair< std::string, alekseev::Vector< size_t > > > alekseev::Graph::inbounds(
    const str & vertex) const
{
  Vector< std::pair< str, Vector< size_t > > > res;
  List< str > * current = vertexes_->next;
  while (current != vertexes_) {
    std::pair< str, str > edge(current->data, vertex);
    if (edges_.contains(edge)) {
      Vector< size_t > weights = edges_.at(edge);
      res.pushBack(std::pair< str, Vector< size_t > >(current->data, weights));
    }
    current = current->next;
  }
  return res;
}

alekseev::List< std::string > * alekseev::Graph::vertexes() const
{
  return deep_copy(vertexes_);
}

alekseev::Graph alekseev::merge_graphs(const Graph & graph1, const Graph & graph2)
{
  Graph merged = graph1;
  List< str > * vertexes2 = graph2.vertexes();
  List< str > * current2 = vertexes2->next;
  try {
    while (current2 != vertexes2) {
      merged.ins_vertex(current2->data);
      current2 = current2->next;
    }

    current2 = vertexes2->next;
    while (current2 != vertexes2) {
      Vector< std::pair< str, Vector< size_t > > > inbounds = graph2.inbounds(current2->data);
      for (size_t i = 0; i < inbounds.getSize(); ++i) {
        merged.add_edges(inbounds[i].first, current2->data, inbounds[i].second);
      }
      current2 = current2->next;
    }
  } catch (...) {
    clear(vertexes2->next, vertexes2);
    rmfake(vertexes2);
    throw;
  }
  clear(vertexes2->next, vertexes2);
  rmfake(vertexes2);
  return merged;
}

alekseev::Graph alekseev::extract_graph(const Graph & source, const List< str > * vertexes)
{
  Graph extracted;
  List< str > * current_vertex = vertexes->next;
  while (current_vertex != vertexes) {
    if (source.has_vertex(current_vertex->data) && !extracted.has_vertex(current_vertex->data)) {
      extracted.add_vertex(current_vertex->data);
    } else {
      throw std::invalid_argument("No such vertex or repeated vertex");
    }
    current_vertex = current_vertex->next;
  }
  current_vertex = vertexes->next;
  while (current_vertex != vertexes) {
    Vector< std::pair< str, Vector< size_t > > > inbounds = source.inbounds(current_vertex->data);
    for (size_t i = 0; i < inbounds.getSize(); ++i) {
      if (extracted.has_vertex(inbounds[i].first)) {
        extracted.add_edges(inbounds[i].first, current_vertex->data, inbounds[i].second);
      }
    }
    current_vertex = current_vertex->next;
  }
  return extracted;
}
