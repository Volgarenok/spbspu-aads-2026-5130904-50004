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
void alberto::cmdOutbound(const GraphTable& graphs,
                           const std::vector< std::string >& tok)
{
  if (tok.size() < 3 || !graphs.has(tok[1])) {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }
  const Graph& g = graphs.get(tok[1]);
  if (!g.hasVertex(tok[2])) {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }

  const std::string& src = tok[2];
  std::vector< std::pair< std::string, std::vector< unsigned > > > out;

  for (const auto& ep : g.edges) {
    if (ep.first.first == src) {
      std::vector< unsigned > ws;
      for (unsigned w : ep.second) {
        ws.push_back(w);
      }
      std::sort(ws.begin(), ws.end());
      out.push_back({ep.first.second, std::move(ws)});
    }
  }
  std::sort(out.begin(), out.end(),
      [](const auto& a, const auto& b) {
        return a.first < b.first;
      });

  for (const auto& row : out) {
    std::cout << row.first;
    for (unsigned w : row.second) {
      std::cout << " " << w;
    }
    std::cout << "\n";
  }
}

void alberto::cmdInbound(const GraphTable& graphs,
                          const std::vector< std::string >& tok)
{
  if (tok.size() < 3 || !graphs.has(tok[1])) {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }
  const Graph& g = graphs.get(tok[1]);
  if (!g.hasVertex(tok[2])) {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }

  const std::string& dst = tok[2];
  std::vector< std::pair< std::string, std::vector< unsigned > > > in;

  for (const auto& ep : g.edges) {
    if (ep.first.second == dst) {
      std::vector< unsigned > ws;
      for (unsigned w : ep.second) {
        ws.push_back(w);
      }
      std::sort(ws.begin(), ws.end());
      in.push_back({ep.first.first, std::move(ws)});
    }
  }
  std::sort(in.begin(), in.end(),
      [](const auto& a, const auto& b) {
        return a.first < b.first;
      });

  for (const auto& row : in) {
    std::cout << row.first;
    for (unsigned w : row.second) {
      std::cout << " " << w;
    }
    std::cout << "\n";
  }
}
