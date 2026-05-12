#include "graph.hpp"

haliullin::Graph::Graph():
  vertexes_(),
  edges_()
{}

haliullin::Graph::Graph(const Graph& other):
  vertexes_(other.vertexes_),
  edges_(other.edges_)
{}

haliullin::Graph::Graph(Graph&& other) noexcept:
  Graph()
{
  swap(other);
}

haliullin::Graph& haliullin::Graph::operator=(const Graph& other)
{
  if (this != std::addressof(other))
  {
    Graph tmp(other);
    swap(tmp);
  }
  return *this;
}

haliullin::Graph& haliullin::Graph::operator=(Graph&& other) noexcept
{
  if (this != std::addressof(other))
  {
    Graph tmp(std::move(other));
    swap(tmp);
  }
  return *this;
}

void haliullin::Graph::swap(Graph& other) noexcept
{
  vertexes_.swap(other.vertexes_);
  edges_.swap(other.edges_);
}

void haliullin::Graph::addVertex(const std::string& vert)
{
  if (hasVertex(vert))
  {
    return;
  }
  vertexes_.pushBack(vert);
  vertexes_.insSort();
}

bool haliullin::Graph::hasVertex(const std::string& vert) const noexcept
{
  for (size_t i = 0; i < vertexes_.getSize(); ++i)
  {
    if (vertexes_[i] == vert)
    {
      return true;
    }
  }
  return false;
}

void haliullin::Graph::cutVertex(const std::string& vert)
{
  size_t pos = vertexes_.getSize();
  for (size_t i = 0; i < vertexes_.getSize(); ++i)
  {
    if (vertexes_[i] == vert)
    {
      pos = i;
      break;
    }
  }
  if (pos == vertexes_.getSize())
  {
    return;
  }

  Vector< std::string > tmp;
  for (size_t i = 0; i < pos; ++i)
  {
    tmp.pushBack(vertexes_[i]);
  }
  for (size_t i = pos + 1; i < vertexes_.getSize(); ++i)
  {
    tmp.pushBack(vertexes_[i]);
  }

  Vector< std::pair< std::string, std::string > > keysToRemove;
  for (auto it = edges_.cbegin(); it != edges_.cend(); ++it)
  {
    const auto& key = (*it).first;
    if (key.first == vert || key.second == vert)
    {
      keysToRemove.pushBack(key);
    }
  }
  for (size_t i = 0; i < keysToRemove.getSize(); ++i)
  {
    edges_.drop(keysToRemove[i]);
  }

  vertexes_.swap(tmp);
}
