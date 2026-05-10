#include "commands.hpp"
#include "vector.hpp"
#include "hashIters.hpp"
#include <sstream>
#include <algorithm>
#include <limits>

void ivantsova::printInvalid(std::ostream& out) {
  out << "<INVALID COMMAND>\n";
}

void ivantsova::cmdGraphs(std::istream&, std::ostream& out, ivantsova::GraphSet& graphs) {
  ivantsova::Vector< std::string > names;
  for (auto it = graphs.begin(); it != graphs.end(); ++it) {
    names.pushBack((*it).first);
  }
  for (size_t i = 0; i < names.getSize() - 1; ++i) {
    for (size_t j = 0; j < names.getSize() - i - 1; ++j) {
      if (names[j] > names[j + 1]) {
        std::swap(names[j], names[j + 1]);
      }
    }
  }
  for (size_t i = 0; i < names.getSize(); ++i) {
    out << names[i] << '\n';
  }
}

void ivantsova::cmdVertexes(std::istream& in, std::ostream& out, ivantsova::GraphSet& graphs) {
  std::string name;
  in >> name;
  if (!graphs.has(name)) {
    printInvalid(out);
    return;
  }
  ivantsova::Vector< std::string > verts = graphs.get(name).getVertices();
  for (size_t i = 0; i < verts.getSize() - 1; ++i) {
    for (size_t j = 0; j < verts.getSize() - i - 1; ++j) {
      if (verts[j] > verts[j + 1]) {
        std::swap(verts[j], verts[j + 1]);
      }
    }
  }
  for (size_t i = 0; i < verts.getSize(); ++i) {
    out << verts[i] << '\n';
  }
}
