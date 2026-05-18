#include <iostream>
#include "graph.hpp"

int main()
{
  ali::Graph graph;

  graph.bind("a", "b", 40);

  if (graph.has_edge("a", "b"))
  {
    std::cout << "ok\n";
  }

  return 0;
}
