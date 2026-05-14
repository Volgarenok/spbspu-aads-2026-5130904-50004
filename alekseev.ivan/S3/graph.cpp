#include "graph.h"
#include <boost/uuid/sha1.hpp>
#include "../common/ListIterators.h"

size_t alekseev::hasher(const std::pair< str, str > & key)
{
  boost::uuids::detail::sha1 first;
  first.process_bytes(key.first.c_str(), key.first.size());
  size_t digest1[5];
  first.get_digest(digest1);

  boost::uuids::detail::sha1 second;
  second.process_bytes(key.second.c_str(), key.second.size());
  size_t digest2[5];
  first.get_digest(digest2);

  size_t result = 0;
  for (int i = 0; i < 5; i++) {
    result ^= digest1[i];
    result ^= digest2[i];
  }
  return result;
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

inline alekseev::Graph & alekseev::Graph::operator=(Graph && rhs) noexcept
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
  } catch (...) {
    edges_.insert(std::pair< str, str >(vertex1, vertex2), Vector< size_t >(1, weight));
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

bool alekseev::Graph::has_edge(const str & vertex1, const str & vertex2) const
{
  return edges_.contains(std::pair< str, str >(vertex1, vertex2));
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
