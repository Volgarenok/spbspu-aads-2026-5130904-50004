#include <iostream>
#include <fstream>
#include <string>
#include "graph.hpp"
#include "hash-table.hpp"
#include "siphash.hpp"
#include "list.hpp"

namespace ali
{
  struct StringEqual
  {
    bool operator()(const std::string & a, const std::string & b) const
    {
      return a == b;
    }
  };

  void sort_strings(List< std::string > & list)
  {
    for (auto it1 = list.begin(); it1 != list.end(); ++it1)
    {
      for (auto it2 = list.begin(); it2 != list.end(); ++it2)
      {
        if (*it2 > *it1)
        {
          std::string temp = *it1;
          *it1 = *it2;
          *it2 = temp;
        }
      }
    }
  }
}

int main(int argc, char ** argv)
{
  if (argc != 2)
  {
    std::cerr << "error\n";
    return 1;
  }

  std::ifstream input(argv[1]);

  if (!input)
  {
    std::cerr << "error\n";
    return 1;
  }

  ali::HashTable< std::string, ali::Graph, ali::SipHash, ali::StringEqual > graphs(101);

  std::string graphName;

  while (input >> graphName)
  {
    unsigned int edgesCount = 0;
    input >> edgesCount;

    ali::Graph graph;

    for (unsigned int i = 0; i < edgesCount; ++i)
    {
      std::string from;
      std::string to;
      unsigned int weight = 0;

      input >> from >> to >> weight;

      graph.bind(from, to, weight);
    }

    graphs.add(graphName, graph);
  }

  std::string command;

  while (std::cin >> command)
  {
    if (command == "graphs")
    {
      ali::List< std::string > names;

      for (auto it = graphs.begin(); it != graphs.end(); ++it)
      {
        names.push_back(it.key());
      }

      ali::sort_strings(names);

      for (auto it = names.begin(); it != names.end(); ++it)
      {
        std::cout << *it << '\n';
      }
    }
    else if (command == "vertexes")
    {
      std::string name;
      std::cin >> name;

      if (!graphs.has(name))
      {
        std::cout << "<INVALID COMMAND>\n";
      }
      else
      {
        graphs.get(name).print_vertexes();
      }
    }
    else if (command == "bind")
    {
      std::string graph;
      std::string from;
      std::string to;
      unsigned int weight = 0;

      std::cin >> graph >> from >> to >> weight;

      if (!graphs.has(graph))
      {
        std::cout << "<INVALID COMMAND>\n";
      }
      else
      {
        graphs.get(graph).bind(from, to, weight);
      }
    }
    else if (command == "cut")
    {
      std::string graph;
      std::string from;
      std::string to;
      unsigned int weight = 0;

      std::cin >> graph >> from >> to >> weight;

      if (!graphs.has(graph))
      {
        std::cout << "<INVALID COMMAND>\n";
      }
      else
      {
        bool result = graphs.get(graph).cut(from, to, weight);

        if (!result)
        {
          std::cout << "<INVALID COMMAND>\n";
        }
      }
    }
    else if (command == "merge")
    {
      std::string newGraph;
      std::string left;
      std::string right;

      std::cin >> newGraph >> left >> right;

      if (!graphs.has(left) || !graphs.has(right))
      {
        std::cout << "<INVALID COMMAND>\n";
      }
      else
      {
        ali::Graph merged = graphs.get(left);
        merged.merge(graphs.get(right));

        graphs.add(newGraph, merged);
      }
    }
    else if (command == "extract")
    {
      std::string newGraph;
      std::string source;
      std::string vertex;

      std::cin >> newGraph >> source >> vertex;

      if (!graphs.has(source))
      {
        std::cout << "<INVALID COMMAND>\n";
      }
      else
      {
        ali::Graph extracted = graphs.get(source).extract(vertex);

        graphs.add(newGraph, extracted);
      }
    }
    else
    {
      std::cout << "<INVALID COMMAND>\n";
    }
  }

  return 0;
}
