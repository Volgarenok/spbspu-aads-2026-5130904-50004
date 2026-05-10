#include "graph.hpp"
#include <algorithm>
#include <stdexcept>

ivantsova::Graph::Graph() :
  vertices_(), edges_()
{}

void ivantsova::Graph::addVertex(const std::string& name) {
  for (size_t i = 0; i < vertices_.getSize(); ++i) {
    if (vertices_[i] == name) {
      return;
    }
  }
  vertices_.pushBack(name);
}

bool ivantsova::Graph::hasVertex(const std::string& name) const {
  for (size_t i = 0; i < vertices_.getSize(); ++i) {
    if (vertices_[i] == name) {
      return true;
    }
  }
  return false;
}

ivantsova::Vector<std::string> ivantsova::Graph::getVertices() const {
  return vertices_;
}

void ivantsova::Graph::addEdge(const std::string& from, const std::string& to, unsigned long long weight) {
  addVertex(from);
  addVertex(to);
  EdgeKey key(from, to);
  if (edges_.has(key)) {
    edges_.get(key).pushBack(weight);
  } else {
    Vector<unsigned long long> weights;
    weights.pushBack(weight);
    edges_.add(key, weights);
  }
}

bool ivantsova::Graph::removeEdge(const std::string& from, const std::string& to, unsigned long long weight) {
  if (!hasVertex(from) || !hasVertex(to)) {
    return false;
  }
  EdgeKey key(from, to);
  if (!edges_.has(key)) {
    return false;
  }
  Vector<unsigned long long>& weights = edges_.get(key);
  for (size_t i = 0; i < weights.getSize(); ++i) {
    if (weights[i] == weight) {
      for (size_t j = i; j < weights.getSize() - 1; ++j) {
        weights[j] = weights[j + 1];
      }
      weights.popBack();
      if (weights.getSize() == 0) {
        edges_.drop(key);
      }
      return true;
    }
  }
  return false;
}
