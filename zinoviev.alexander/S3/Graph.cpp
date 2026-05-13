#include <algorithm>
#include "Graph.hpp"

namespace zinoviev
{

  std::size_t StringHasher::operator()(const std::string& p) const
  {
    boost::hash2::sha1_160 hasher;
    boost::hash2::hash_append(hasher, {}, p);
    return boost::hash2::get_integral_result(hasher.result());
  }

  std::size_t PairHasher::operator()(const std::pair<std::string, std::string>& p) const
  {
    boost::hash2::sha1_160 hasher;
    boost::hash2::hash_append(hasher, {}, p.first);
    boost::hash2::hash_append(hasher, {}, p.second);
    return boost::hash2::get_integral_result(hasher.result());
  }

  bool Graph::has_vertex(const std::string& v) const
  {
    return vertexes_.has(v);
  }

  Vector<std::string> Graph::get_vertices() const
  {
    Vector<std::string> tmp;

    auto slot_pt = vertexes_.cbegin();
    auto end = vertexes_.cend();
    while (slot_pt != end)
    {
      tmp.push_back((*slot_pt).first);
      ++slot_pt;
    }

    sortVector(tmp);
    return tmp;
  }

  const Vector<unsigned long long>* Graph::get_weights(const std::string& from, const std::string& to) const
  {
    return edges_.find({ from, to });
  }

  void Graph::swap(Graph& other) noexcept
  {
    std::swap(this->name_, other.name_);
    edges_.swap(other.edges_);
    vertexes_.swap(other.vertexes_);
  }

  std::string Graph::get_name() const
  {
    return name_;
  }

  Vector<std::pair<std::string, Vector<unsigned long long>>> Graph::get_outbound(const std::string& vertex) const
  {
    Vector<std::pair<std::string, Vector<unsigned long long>>> res;

    auto edge = edges_.cbegin();
    auto end = edges_.cend();
    while (edge != end)
    {
      if ((*edge).first.first == vertex)
        res.push_back({ (*edge).first.second, (*edge).second });
      ++edge;
    }

    sortPair(res);
    for (size_t i = 0; i < res.getSize(); ++i)
      sortVector(res[i].second);
    return res;
  }

  Vector<std::pair<std::string, Vector<unsigned long long>>> Graph::get_inbound(const std::string& vertex) const
  {
    Vector<std::pair<std::string, Vector<unsigned long long>>> res;

    auto edge = edges_.cbegin();
    auto end = edges_.cend();
    while (edge != end)
    {
      if ((*edge).first.second == vertex)
        res.push_back({ (*edge).first.first, (*edge).second });
      ++edge;
    }

    sortPair(res);
    for (size_t i = 0; i < res.getSize(); ++i)
      sortVector(res[i].second);
    return res;
  }

  void Graph::remove_edge(const std::pair<std::string, std::string>& p, unsigned long long weight)
  {
    Vector<unsigned long long>* ptr = edges_.find(p);

    if (!ptr)
      throw std::out_of_range("Can't find this edge");

    size_t id = ptr->getSize();
    for (size_t i = 0; i < ptr->getSize(); ++i)
      if (ptr->operator[](i) == weight)
      {
        id = i;
        break;
      }

    if (id == ptr->getSize())
      throw std::out_of_range("Can't find this weight");

    ptr->erase(id);

    if (ptr->is_empty())
      edges_.erase(p);
  }
}
