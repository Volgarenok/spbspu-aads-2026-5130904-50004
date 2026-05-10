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
