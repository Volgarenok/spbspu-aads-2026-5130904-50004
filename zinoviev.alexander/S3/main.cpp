#include <iostream>
#include <fstream>
#include <string>
#include "graph.hpp"
#include "hash_table.hpp"
#include "commands.hpp"

using GraphTable = zinoviev::HashTable<std::string, zinoviev::Graph, zinoviev::StringHasher, std::equal_to<std::string>>;

int main(int argc,const char* argv[])
{
  if (argc != 2)
  {
    std::cout << "Usage: " << argv[0] << " <filename>\n";
    return 1;
  }

  std::ifstream file(argv[1]);
  if (!file.is_open())
  {
    std::cout << "Error: cannot open file " << argv[1] << std::endl;
    return 0;
  }

  GraphTable graphs;

  std::string line;
  while (std::getline(file, line))
  {
    if (line.empty())
      continue;

    size_t pos = line.find(' ');
    std::string graph_name = line.substr(0, pos);
    std::string count_str = line.substr(pos + 1);
    unsigned long long edges_count = std::stoull(count_str);

    zinoviev::Graph new_graph(graph_name);

    size_t read_edges = 0;
    while (!file.eof() && read_edges < edges_count && std::getline(file, line))
    {
      if (line.empty())
        continue;

      size_t first_space = line.find(' ');
      std::string from = line.substr(0, first_space);
      std::string rest = line.substr(first_space + 1);

      size_t second_space = rest.find(' ');
      std::string to = rest.substr(0, second_space);
      std::string weight_str = rest.substr(second_space + 1);

      unsigned long long weight = std::stoull(weight_str);

      new_graph.add_edge(from, to, weight);
      ++read_edges;
    }

    try
    {
      graphs.add(graph_name, new_graph);
    }
    catch (const std::overflow_error&)
    {
      std::cout << "<INVALID COMMAND>\n";
      continue;
    }
  }
}
