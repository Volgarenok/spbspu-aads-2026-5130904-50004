#include "graph.hpp"
#include <algorithm>

kuchukbaeva::Graph::Graph():
  vertexes_(),
  edges_(16)
{}

void kuchukbaeva::Graph::addVertex(const std::string& v)
{
  if (!hasVertex(v))
  {
    vertexes_.pushBack(v);
    for (size_t i = vertexes_.getSize() - 1; i > 0; --i)
    {
      if (vertexes_[i] < vertexes_[i - 1])
      {
        std::swap(vertexes_[i], vertexes_[i - 1]);
      }
    }
  }
}

bool kuchukbaeva::Graph::hasVertex(const std::string& v) const noexcept
{
  for (size_t i = 0; i < vertexes_.getSize(); ++i)
  {
    if (vertexes_[i] == v)
    {
      return true;
    }
  }
  return false;
}

void kuchukbaeva::Graph::addEdge(const std::string& src, const std::string& dest, unsigned int weight)
{
  addVertex(src);
  addVertex(dest);
  std::pair< std::string, std::string > key = std::make_pair(src, dest);
  Vector< unsigned int >* weights = edges_.find(key);
  if (weights)
  {
    weights->pushBack(weight);
  }
  else
  {
    Vector< unsigned int > newWeights;
    newWeights.pushBack(weight);
    edges_.add(key, newWeights);
  }
}

bool kuchukbaeva::Graph::cutEdge(const std::string& src, const std::string& dest, unsigned int weight)
{
  std::pair< std::string, std::string > key = std::make_pair(src, dest);
  Vector< unsigned int >* weights = edges_.find(key);
  if (!weights)
  {
    return false;
  }
  for (size_t i = 0; i < weights->getSize(); ++i)
  {
    if ((*weights)[i] == weight)
    {
      weights->erase(i);
      if (weights->isEmpty())
      {
        edges_.drop(key);
      }
      return true;
    }
  }
  return false;
}

kuchukbaeva::Graph kuchukbaeva::Graph::merge(const Graph& other) const
{
  Graph res = *this;
  for (size_t i = 0; i < other.vertexes_.getSize(); ++i)
  {
    res.addVertex(other.vertexes_[i]);
  }
  for (auto it = other.edges_.cbegin(); it != other.edges_.cend(); ++it)
  {
    const std::pair< std::string, std::string >& key = it->first;
    const Vector< unsigned int >& weights = it->second;
    for (size_t i = 0; i < weights.getSize(); ++i)
    {
      res.addEdge(key.first, key.second, weights[i]);
    }
  }
  return res;
}

kuchukbaeva::Graph kuchukbaeva::Graph::extract(const Vector< std::string >& vToExtract) const
{
  Graph res;
  for (size_t i = 0; i < vToExtract.getSize(); ++i)
  {
    res.addVertex(vToExtract[i]);
  }
  for (auto it = edges_.cbegin(); it != edges_.cend(); ++it)
  {
    if (res.hasVertex(it->first.first) && res.hasVertex(it->first.second))
    {
      const Vector< unsigned int >& weights = it->second;
      for (size_t i = 0; i < weights.getSize(); ++i)
      {
        res.addEdge(it->first.first, it->first.second, weights[i]);
      }
    }
  }
  return res;
}

const kuchukbaeva::Vector< std::string >& kuchukbaeva::Graph::getVertexes() const noexcept
{
  return vertexes_;
}

void kuchukbaeva::Graph::getOutbound(const std::string& v, Vector< std::pair< std::string, unsigned int > >& out) const
{
  for (auto it = edges_.cbegin(); it != edges_.cend(); ++it)
  {
    if (it->first.first == v)
    {
      for (size_t i = 0; i < it->second.getSize(); ++i)
      {
        out.pushBack(std::make_pair(it->first.second, it->second[i]));
      }
    }
  }
  sortPairs(out);
}

void kuchukbaeva::Graph::getInbound(const std::string& v, Vector< std::pair< std::string, unsigned int > >& out) const
{
  for (auto it = edges_.cbegin(); it != edges_.cend(); ++it)
  {
    if (it->first.second == v)
    {
      for (size_t i = 0; i < it->second.getSize(); ++i)
      {
        out.pushBack(std::make_pair(it->first.first, it->second[i]));
      }
    }
  }
  sortPairs(out);
}

void kuchukbaeva::Graph::sortPairs(Vector< std::pair< std::string, unsigned int > >& vec) const
{
  for (size_t i = 0; i < vec.getSize(); ++i)
  {
    for (size_t j = i + 1; j < vec.getSize(); ++j)
    {
      if (vec[j].first < vec[i].first || (vec[j].first == vec[i].first && vec[j].second < vec[i].second))
      {
        std::swap(vec[i], vec[j]);
      }
    }
  }
}
