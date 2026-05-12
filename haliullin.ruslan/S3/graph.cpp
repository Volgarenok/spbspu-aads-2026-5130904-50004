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

void haliullin::Graph::addEdge(const std::string& fromVert, const std::string& toVert, unsigned long long weight)
{
  addVertex(fromVert);
  addVertex(toVert);

  std::pair< std::string, std::string > key{fromVert, toVert};
  if (!edges_.has(key))
  {
    Vector< unsigned long long > w;
    w.pushBack(weight);
    edges_.add(key, w);
  }
  else
  {
    Vector< unsigned long long >& w = edges_.get(key);
    size_t pos = 0;
    while (pos < w.getSize() && w[pos] < weight)
    {
      ++pos;
    }
    w.insert(pos, weight);
  }
}

bool haliullin::Graph::cutEdge(const std::string& fromVert, const std::string& toVert, unsigned long long weight)
{
  std::pair< std::string, std::string > key{fromVert, toVert};
  if (!edges_.has(key))
    return false;

  Vector< unsigned long long >& w = edges_.get(key);
  for (size_t i = 0; i < w.getSize(); ++i)
  {
    if (w[i] == weight)
    {
      w.erase(i);
      if (w.isEmpty())
      {
        edges_.drop(key);
      }
      return true;
    }
  }
  return false;
}

haliullin::Vector< std::pair< std::string, haliullin::Vector< unsigned long long > > >
haliullin::Graph::getOutbound(const std::string& fromVert) const
{
  Vector< std::pair< std::string, Vector< unsigned long long > > > result;
  for (auto it = edges_.cbegin(); it != edges_.cend(); ++it)
  {
    if ((*it).first.first == fromVert)
    {
      result.pushBack({ (*it).first.second, (*it).second });
    }
  }
  result.insSort();
  return result;
}

