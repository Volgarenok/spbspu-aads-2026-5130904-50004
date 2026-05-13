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
  second.process_bytes(key.first.c_str(), key.first.size());
  size_t digest2[5];
  first.get_digest(digest2);

  size_t result = 0;
  for (int i = 0; i < 5; i++) {
    result += digest1[i] + digest2[i];
  }
  return result;
}

bool alekseev::is_equal(const std::pair< str, str > & lhs, const std::pair< str, str > & rhs)
{
  return lhs.first == rhs.first && lhs.second == rhs.second || lhs.first == rhs.second && lhs.second
      == rhs.first;
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
  edges_(HashTable< std::pair< str, str >, List< size_t >, hasher_ptr, is_equal_ptr >(hasher,
      is_equal, 1024))
{
}

void alekseev::Graph::swap(Graph & rhs) noexcept
{
  std::swap(vertexes_, rhs.vertexes_);
  edges_.swap(rhs.edges_);
}

void alekseev::Graph::ins_vertex(str vertex)
{
  LIter< str > fake = before_begin(vertexes_);
  LIter< str > current = fake;
  while (current++ != fake) {
    if (*current == vertex) {
      return;
    }
  }
  add_vertex(vertex);
}

void alekseev::Graph::add_vertex(str vertex)
{
  insert_after(vertexes_, vertex);
}
