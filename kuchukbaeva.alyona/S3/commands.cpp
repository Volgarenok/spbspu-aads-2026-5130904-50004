#include "application.hpp"
#include <iostream>
#include <fstream>

namespace kuchukbaeva {

  template< typename T >
  void sortVector(Vector< T >& vec)
  {
    size_t n = vec.getSize();
    if (n == 0) {
      return;
    }
    for (size_t i = 0; i < n - 1; ++i) {
      for (size_t j = 0; j < n - i - 1; ++j) {
        if (vec[j + 1] < vec[j]) {
          T temp = vec[j];
          vec[j] = vec[j + 1];
          vec[j + 1] = temp;
        }
      }
    }
  }

  Vector< std::string > splitString(const std::string& str)
  {
    Vector< std::string > res;
    std::string current = "";
    for (size_t i = 0; i < str.length(); ++i) {
      if (str[i] == ' ') {
        if (!current.empty()) {
          res.pushBack(current);
          current = "";
        }
      } else {
        current += str[i];
      }
    }
    if (!current.empty()) {
      res.pushBack(current);
    }
    return res;
  }

  unsigned int stringToUInt(const std::string& str)
  {
    unsigned int res = 0;
    for (size_t i = 0; i < str.length(); ++i) {
      res = res * 10 + (str[i] - '0');
    }
    return res;
  }

  Application::Application() :
    commands_(16),
    graphs_(16)
  {
    commands_.add("graphs", &Application::cmdGraphs);
    commands_.add("vertexes", &Application::cmdVertexes);
    commands_.add("outbound", &Application::cmdOutbound);
    commands_.add("inbound", &Application::cmdInbound);
    commands_.add("bind", &Application::cmdBind);
    commands_.add("cut", &Application::cmdCut);
    commands_.add("create", &Application::cmdCreate);
    commands_.add("merge", &Application::cmdMerge);
    commands_.add("extract", &Application::cmdExtract);
  }
  void Application::loadFromFile(const std::string& filename)
  {
    std::ifstream file(filename);
    if (!file.is_open()) {
      throw std::runtime_error("Cannot open file");
    }

    std::string line;
    while (std::getline(file, line)) {
      Vector< std::string > tokens = splitString(line);
      if (tokens.getSize() == 0) {
        continue;
      }
      if (tokens.getSize() == 2) {
        std::string graphName = tokens[0];
        unsigned int edgeCount = stringToUInt(tokens[1]);
        Graph g;
        for (unsigned int i = 0; i < edgeCount; ++i) {
          std::string edgeLine;
          if (std::getline(file, edgeLine)) {
            Vector< std::string > edgeTokens = splitString(edgeLine);
            if (edgeTokens.getSize() >= 3) {
              std::string src = edgeTokens[0];
              std::string dest = edgeTokens[1];
              unsigned int weight = stringToUInt(edgeTokens[2]);
              bool srcFound = false;
              bool destFound = false;
              for (size_t v = 0; v < g.vertexes.getSize(); ++v) {
                if (g.vertexes[v] == src) srcFound = true;
                if (g.vertexes[v] == dest) destFound = true;
              }
              if (!srcFound) g.vertexes.pushBack(src);
              if (!destFound) g.vertexes.pushBack(dest);

              std::pair< std::string, std::string > key(src, dest);
              Vector< unsigned int >* weights = g.edges.find(key);
              if (weights) {
                weights->pushBack(weight);
              } else {
                Vector< unsigned int > newWeights;
                newWeights.pushBack(weight);
                g.edges.add(key, newWeights);
              }
            }
          }
        }
        graphs_.add(graphName, g);
      }
    }
  }

  void Application::run(const std::string& filename)
  {
    loadFromFile(filename);
    std::string line;
    while (std::getline(std::cin, line)) {
      processLine(line);
    }
  }

  void Application::processLine(const std::string& line)
  {
    Vector< std::string > tokens = splitString(line);
    if (tokens.getSize() == 0) {
      return;
    }
    CommandFunc* funcPtr = commands_.find(tokens[0]);
    if (funcPtr) {
      (*funcPtr)(this, tokens);
    } else {
      std::cout << "<INVALID COMMAND>\n";
    }
  }
}
