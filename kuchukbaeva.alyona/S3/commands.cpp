#include "commands.hpp"
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
  void Application::cmdGraphs(Application* app, const Vector< std::string >& args)
  {
    if (args.getSize() != 1) {
      std::cout << "<INVALID COMMAND>\n";
      return;
    }
    Vector< std::string > names;
    for (auto it = app->graphs_.begin(); it != app->graphs_.end(); ++it) {
      names.pushBack(it->first);
    }
    sortVector(names);
    for (size_t i = 0; i < names.getSize(); ++i) {
      std::cout << names[i] << "\n";
    }
  }

  void Application::cmdVertexes(Application* app, const Vector< std::string >& args)
  {
    if (args.getSize() != 2) {
      std::cout << "<INVALID COMMAND>\n";
      return;
    }
    Graph* g = app->graphs_.find(args[1]);
    if (!g) {
      std::cout << "<INVALID COMMAND>\n";
      return;
    }
    Vector< std::string > verts = g->vertexes;
    sortVector(verts);
    for (size_t i = 0; i < verts.getSize(); ++i) {
      std::cout << verts[i] << "\n";
    }
  }

  void Application::cmdOutbound(Application* app, const Vector< std::string >& args)
  {
    if (args.getSize() != 3) {
      std::cout << "<INVALID COMMAND>\n";
      return;
    }
    Graph* g = app->graphs_.find(args[1]);
    if (!g) {
      std::cout << "<INVALID COMMAND>\n";
      return;
    }
    bool vFound = false;
    for (size_t i = 0; i < g->vertexes.getSize(); ++i) {
      if (g->vertexes[i] == args[2]) {
        vFound = true;
        break;
      }
    }
    if (!vFound) {
      std::cout << "<INVALID COMMAND>\n";
      return;
    }

    Vector< std::string > dests;
    for (auto it = g->edges.begin(); it != g->edges.end(); ++it) {
      if (it->first.first == args[2]) {
        dests.pushBack(it->first.second);
      }
    }
    sortVector(dests);

    for (size_t i = 0; i < dests.getSize(); ++i) {
      std::pair< std::string, std::string > key(args[2], dests[i]);
      Vector< unsigned int >* weights = g->edges.find(key);
      if (weights) {
        Vector< unsigned int > wCopy = *weights;
        sortVector(wCopy);
        for (size_t w = 0; w < wCopy.getSize(); ++w) {
          std::cout << dests[i] << " " << wCopy[w] << "\n";
        }
      }
    }
  }

  void Application::cmdInbound(Application* app, const Vector< std::string >& args)
  {
    if (args.getSize() != 3) {
      std::cout << "<INVALID COMMAND>\n";
      return;
    }
    Graph* g = app->graphs_.find(args[1]);
    if (!g) {
      std::cout << "<INVALID COMMAND>\n";
      return;
    }
    bool vFound = false;
    for (size_t i = 0; i < g->vertexes.getSize(); ++i) {
      if (g->vertexes[i] == args[2]) {
        vFound = true;
        break;
      }
    }
    if (!vFound) {
      std::cout << "<INVALID COMMAND>\n";
      return;
    }

    Vector< std::string > srcs;
    for (auto it = g->edges.begin(); it != g->edges.end(); ++it) {
      if (it->first.second == args[2]) {
        srcs.pushBack(it->first.first);
      }
    }
    sortVector(srcs);

    for (size_t i = 0; i < srcs.getSize(); ++i) {
      std::pair< std::string, std::string > key(srcs[i], args[2]);
      Vector< unsigned int >* weights = g->edges.find(key);
      if (weights) {
        Vector< unsigned int > wCopy = *weights;
        sortVector(wCopy);
        for (size_t w = 0; w < wCopy.getSize(); ++w) {
          std::cout << srcs[i] << " " << wCopy[w] << "\n";
        }
      }
    }
  }

  void Application::cmdBind(Application* app, const Vector< std::string >& args)
  {
    if (args.getSize() != 5) {
      std::cout << "<INVALID COMMAND>\n";
      return;
    }
    Graph* g = app->graphs_.find(args[1]);
    if (!g) {
      std::cout << "<INVALID COMMAND>\n";
      return;
    }
    std::string src = args[2];
    std::string dest = args[3];
    unsigned int weight = stringToUInt(args[4]);

    bool srcFound = false;
    bool destFound = false;
    for (size_t i = 0; i < g->vertexes.getSize(); ++i) {
      if (g->vertexes[i] == src) srcFound = true;
      if (g->vertexes[i] == dest) destFound = true;
    }
    if (!srcFound) g->vertexes.pushBack(src);
    if (!destFound) g->vertexes.pushBack(dest);

    std::pair< std::string, std::string > key(src, dest);
    Vector< unsigned int >* weights = g->edges.find(key);
    if (weights) {
      weights->pushBack(weight);
    } else {
      Vector< unsigned int > newWeights;
      newWeights.pushBack(weight);
      g->edges.add(key, newWeights);
    }
  }

  void Application::cmdCut(Application* app, const Vector< std::string >& args)
  {
    if (args.getSize() != 5) {
      std::cout << "<INVALID COMMAND>\n";
      return;
    }
    Graph* g = app->graphs_.find(args[1]);
    if (!g) {
      std::cout << "<INVALID COMMAND>\n";
      return;
    }
    std::pair< std::string, std::string > key(args[2], args[3]);
    unsigned int weight = stringToUInt(args[4]);
    Vector< unsigned int >* weights = g->edges.find(key);
    if (!weights) {
      std::cout << "<INVALID COMMAND>\n";
      return;
    }
    bool found = false;
    for (size_t i = 0; i < weights->getSize(); ++i) {
      if ((*weights)[i] == weight) {
        weights->erase(i);
        found = true;
        break;
      }
    }
    if (!found) {
      std::cout << "<INVALID COMMAND>\n";
      return;
    }
    if (weights->isEmpty()) {
      g->edges.drop(key);
    }
  }

  void Application::cmdCreate(Application* app, const Vector< std::string >& args)
  {
    if (args.getSize() < 3) {
      std::cout << "<INVALID COMMAND>\n";
      return;
    }
    if (app->graphs_.has(args[1])) {
      std::cout << "<INVALID COMMAND>\n";
      return;
    }
    unsigned int count = stringToUInt(args[2]);
    if (args.getSize() != 3 + count) {
      std::cout << "<INVALID COMMAND>\n";
      return;
    }
    Graph g;
    for (unsigned int i = 0; i < count; ++i) {
      g.vertexes.pushBack(args[3 + i]);
    }
    app->graphs_.add(args[1], g);
  }

  void Application::cmdMerge(Application* app, const Vector< std::string >& args)
  {
    if (args.getSize() != 4) {
      std::cout << "<INVALID COMMAND>\n";
      return;
    }
    if (app->graphs_.has(args[1])) {
      std::cout << "<INVALID COMMAND>\n";
      return;
    }
    Graph* g1 = app->graphs_.find(args[2]);
    Graph* g2 = app->graphs_.find(args[3]);
    if (!g1 || !g2) {
      std::cout << "<INVALID COMMAND>\n";
      return;
    }
    Graph newG = *g1;
    for (size_t i = 0; i < g2->vertexes.getSize(); ++i) {
      bool exists = false;
      for (size_t j = 0; j < newG.vertexes.getSize(); ++j) {
        if (newG.vertexes[j] == g2->vertexes[i]) {
          exists = true;
          break;
        }
      }
      if (!exists) {
        newG.vertexes.pushBack(g2->vertexes[i]);
      }
    }
    for (auto it = g2->edges.begin(); it != g2->edges.end(); ++it) {
      Vector< unsigned int >* existingWeights = newG.edges.find(it->first);
      if (existingWeights) {
        for (size_t w = 0; w < it->second.getSize(); ++w) {
          existingWeights->pushBack(it->second[w]);
        }
      } else {
        newG.edges.add(it->first, it->second);
      }
    }
    app->graphs_.add(args[1], newG);
  }

  void Application::cmdExtract(Application* app, const Vector< std::string >& args)
  {
    if (args.getSize() < 4) {
      std::cout << "<INVALID COMMAND>\n";
      return;
    }
    if (app->graphs_.has(args[1])) {
      std::cout << "<INVALID COMMAND>\n";
      return;
    }
    Graph* oldG = app->graphs_.find(args[2]);
    if (!oldG) {
      std::cout << "<INVALID COMMAND>\n";
      return;
    }

    unsigned int count = stringToUInt(args[3]);
    if (args.getSize() != 4 + count) {
      std::cout << "<INVALID COMMAND>\n";
      return;
    }
    Vector< std::string > vToExtract;
    for (unsigned int i = 0; i < count; ++i) {
      std::string v = args[4 + i];
      bool existsInOld = false;
      for (size_t j = 0; j < oldG->vertexes.getSize(); ++j) {
        if (oldG->vertexes[j] == v) {
          existsInOld = true;
          break;
        }
      }
      if (!existsInOld) {
        std::cout << "<INVALID COMMAND>\n";
        return;
      }
      vToExtract.pushBack(v);
    }
    Graph newG;
    newG.vertexes = vToExtract;
    for (auto it = oldG->edges.begin(); it != oldG->edges.end(); ++it) {
      bool srcIn = false;
      bool destIn = false;
      for (size_t i = 0; i < vToExtract.getSize(); ++i) {
        if (vToExtract[i] == it->first.first) srcIn = true;
        if (vToExtract[i] == it->first.second) destIn = true;
      }
      if (srcIn && destIn) {
        newG.edges.add(it->first, it->second);
      }
    }
    app->graphs_.add(args[1], newG);
  }

}
