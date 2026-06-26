#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <string>
#include "list.hpp"

namespace ali
{
  struct Edge
  {
    std::string from;
    std::string to;
    unsigned int weight;

    Edge():
      from(),
      to(),
      weight(0)
    {}

    Edge(const std::string & f, const std::string & t, unsigned int w):
      from(f),
      to(t),
      weight(w)
    {}
  };

  class Graph
  {
  private:
    List< std::string > vertexes_;
    List< Edge > edges_;

    bool has_vertex(const std::string & name)
    {
      for (auto it = vertexes_.begin(); it != vertexes_.end(); ++it)
      {
        if (*it == name)
        {
          return true;
        }
      }

      return false;
    }

  public:
    void add_vertex(const std::string & name)
    {
      if (!has_vertex(name))
      {
        vertexes_.push_back(name);
      }
    }

    void bind(const std::string & from, const std::string & to, unsigned int weight)
    {
      add_vertex(from);
      add_vertex(to);

      edges_.push_back(Edge(from, to, weight));
    }

    bool cut(const std::string & from, const std::string & to, unsigned int weight)
    {
      List< Edge > newEdges;
      bool removed = false;

      for (auto it = edges_.begin(); it != edges_.end(); ++it)
      {
        if (!removed &&
            (*it).from == from &&
            (*it).to == to &&
            (*it).weight == weight)
        {
          removed = true;
        }
        else
        {
          newEdges.push_back(*it);
        }
      }

      edges_ = newEdges;

      return removed;
    }

    void merge(Graph & other)
    {
      for (auto it = other.vertexes_.begin(); it != other.vertexes_.end(); ++it)
      {
        add_vertex(*it);
      }

      for (auto it = other.edges_.begin(); it != other.edges_.end(); ++it)
      {
        bind((*it).from, (*it).to, (*it).weight);
      }
    }

    Graph extract(const std::string & vertex)
    {
      Graph result;

      for (auto it = edges_.begin(); it != edges_.end(); ++it)
      {
        if ((*it).from == vertex || (*it).to == vertex)
        {
          result.bind((*it).from, (*it).to, (*it).weight);
        }
      }

      return result;
    }

    bool has(const std::string & name)
    {
      return has_vertex(name);
    }

    void print_vertexes()
    {
      for (auto it = vertexes_.begin(); it != vertexes_.end(); ++it)
      {
        std::cout << *it << '\n';
      }
    }
  };
}

#endif
