#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
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

  std::string cmd_line;
  while (std::getline(std::cin, cmd_line))
  {
    if (cmd_line.empty())
      continue;

    zinoviev::Vector<std::string> tokens = zinoviev::split(cmd_line);

    if (tokens.is_empty())
      continue;

    const std::string& command = tokens[0];

    if (command == "graphs")
    {
      if (tokens.getSize() != 1)
      {
        std::cout << "<INVALID COMMAND>\n";
        continue;
      }

      auto cbegin = graphs.cbegin();
      auto cend = graphs.cend();
      zinoviev::print_name_graphs(std::cout, cbegin, cend);
    }
    else if (command == "vertexes")
    {
      if (tokens.getSize() != 2)
      {
        std::cout << "<INVALID COMMAND>\n";
        continue;
      }

      zinoviev::Graph* g = graphs.find(tokens[1]);
      if (!g)
      {
        std::cout << "<INVALID COMMAND>\n";
        continue;
      }

      zinoviev::Vector<std::string> vertices = g->get_vertices();

      for (size_t i = 0; i < vertices.getSize(); ++i)
        std::cout << vertices[i] << '\n';
    }
    else if (command == "outbound" || command == "inbound")
    {
      if (tokens.getSize() != 3)
      {
        std::cout << "<INVALID COMMAND>\n";
        continue;
      }

      zinoviev::Graph* g = graphs.find(tokens[1]);
      if (!g || !g->has_vertex(tokens[2]))
      {
        std::cout << "<INVALID COMMAND>\n";
        continue;
      }

      zinoviev::Vector < std::pair<std::string, zinoviev::Vector<unsigned long long>>> v;

      if (command == "outbound")
        v = g->get_outbound(tokens[2]);
      else
        v = g->get_inbound(tokens[2]);

      for (size_t i = 0; i < v.getSize(); ++i)
      {
        std::cout << v[i].first;
        for (size_t j = 0; j < v[i].second.getSize(); ++j)
        {
          std::cout << " " << v[i].second[j];
        }
        std::cout << "\n";
      }
    }
    else if (command == "bind")
    {
      if (tokens.getSize() != 5)
      {
        std::cout << "<INVALID COMMAND>\n";
        continue;
      }

      zinoviev::Graph* g = graphs.find(tokens[1]);
      if (!g)
      {
        std::cout << "<INVALID COMMAND>\n";
        continue;
      }

      try
      {
        unsigned long long weight = std::stoull(tokens[4]);
        g->add_edge(tokens[2], tokens[3], weight);
      }
      catch (...)
      {
        std::cout << "<INVALID COMMAND>\n";
        continue;
      }
    }
    else if (command == "cut")
    {
      if (tokens.getSize() != 5)
      {
        std::cout << "<INVALID COMMAND>\n";
        continue;
      }

      zinoviev::Graph* g = graphs.find(tokens[1]);
      if (!g)
      {
        std::cout << "<INVALID COMMAND>\n";
        continue;
      }

      try
      {
        unsigned long long weight = std::stoull(tokens[4]);
        g->remove_edge({ tokens[2], tokens[3] }, weight);
      }
      catch (...)
      {
        std::cout << "<INVALID COMMAND>\n";
        continue;
      }
    }
    else if (command == "create")
    {
      if (tokens.getSize() < 3)
      {
        std::cout << "<INVALID COMMAND>\n";
        continue;
      }

      unsigned long long count = 0;
      try
      {
        count = std::stoull(tokens[2]);
        if (count != tokens.getSize() - 3)
        {
          std::cout << "<INVALID COMMAND>\n";
          continue;
        }
      }
      catch (...)
      {
        std::cout << "<INVALID COMMAND>\n";
        continue;
      }

      if (graphs.find(tokens[1]))
      {
        std::cout << "<INVALID COMMAND>\n";
        continue;
      }

      try
      {
        zinoviev::Graph new_graph(tokens[1]);
        for (size_t i = 3; i < tokens.getSize(); ++i)
          new_graph.add_vertex(tokens[i]);
        graphs.add(tokens[1], new_graph);
      }
      catch (...)
      {
        std::cout << "<INVALID COMMAND>\n";
        continue;
      }
    }
    else if (command == "merge")
    {
      if (tokens.getSize() != 4)
      {
        std::cout << "<INVALID COMMAND>\n";
        continue;
      }

      zinoviev::Graph* new_graph_name = graphs.find(tokens[1]);
      zinoviev::Graph* old_g1 = graphs.find(tokens[2]);
      zinoviev::Graph* old_g2 = graphs.find(tokens[3]);
      if (new_graph_name || !old_g1 || !old_g2)
      {
        std::cout << "<INVALID COMMAND>\n";
        continue;
      }

      try
      {
        zinoviev::Graph new_graph(tokens[1]);
        new_graph.add_graph(*old_g1);
        new_graph.add_graph(*old_g2);
        graphs.add(tokens[1], new_graph);
      }
      catch (...)
      {
        std::cout << "<INVALID COMMAND>\n";
        continue;
      }
    }
    else if (command == "extract")
    {
    }
    else
      std::cout << "<INVALID COMMAND>\n";
  }
}
