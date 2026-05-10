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
void alberto::cmdBind(GraphTable& graphs,
                       const std::vector< std::string >& tok)
{
  if (tok.size() < 5 || !graphs.has(tok[1])) {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }
  const unsigned w = static_cast< unsigned >(std::stoul(tok[4]));
  Graph& g = graphs.get(tok[1]);
  try {
    g.addEdge(tok[2], tok[3], w);
  } catch (std::overflow_error&) {
    g.edges.rehash(g.edges.bucketCount() * 2);
    g.vertices.rehash(g.vertices.bucketCount() * 2);
    g.addEdge(tok[2], tok[3], w);
  }
}

void alberto::cmdCut(GraphTable& graphs,
                      const std::vector< std::string >& tok)
{
  if (tok.size() < 5 || !graphs.has(tok[1])) {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }
  Graph& g = graphs.get(tok[1]);
  if (!g.hasVertex(tok[2]) || !g.hasVertex(tok[3])) {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }

  const EdgeKey  k{tok[2], tok[3]};
  const unsigned w = static_cast< unsigned >(std::stoul(tok[4]));

  if (!g.edges.has(k)) {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }
  WeightList& wl      = g.edges.get(k);
  const bool  removed = wl.remove_if([w](unsigned x) {
    return x == w;
  });
  if (!removed) {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }
  if (wl.empty()) {
    g.edges.drop(k);
  }
}

void alberto::cmdCreate(GraphTable& graphs,
                         const std::vector< std::string >& tok)
{
  if (tok.size() < 2 || graphs.has(tok[1])) {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }
  Graph  ng;
  size_t cnt = 0;
  if (tok.size() >= 3) {
    cnt = static_cast< size_t >(std::stoul(tok[2]));
    for (size_t i = 0; i < cnt && (3 + i) < tok.size(); ++i) {
      ng.ensureVertex(tok[3 + i]);
    }
  }
  safeAddGraph(graphs, tok[1], std::move(ng));
}
