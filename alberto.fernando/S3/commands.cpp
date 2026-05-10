#include "commands.hpp"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

void alberto::cmdGraphs(const GraphTable& graphs)
{
  const auto keys = sortedKeys(graphs);
  for (const auto& k : keys) {
    std::cout << k << "\n";
  }
}

void alberto::cmdVertexes(const GraphTable& graphs,
                           const std::vector< std::string >& tok)
{
  if (tok.size() < 2 || !graphs.has(tok[1])) {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }
  const Graph& g    = graphs.get(tok[1]);
  const auto   keys = sortedKeys(g.vertices);
  for (const auto& k : keys) {
    std::cout << k << "\n";
  }
}
