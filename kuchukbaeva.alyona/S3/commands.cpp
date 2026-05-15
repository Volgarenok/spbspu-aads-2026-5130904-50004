#include "commands.hpp"
#include <iostream>
#include <fstream>

template< typename T >
void kuchukbaeva::sortVector(Vector< T >& vec)
{
  size_t n = vec.getSize();
  if (n <= 1)
  {
    return;
  }
  for (size_t i = 0; i < n - 1; ++i)
  {
    for (size_t j = i + 1; j < n; ++j)
    {
      if (vec[j] < vec[i])
      {
        T temp = vec[i];
        vec[i] = vec[j];
        vec[j] = temp;
      }
    }
  }
}

kuchukbaeva::Vector< std::string > kuchukbaeva::splitString(const std::string& str)
{
  Vector< std::string > res;
  std::string current = "";
  for (size_t i = 0; i < str.length(); ++i)
  {
    if (str[i] == ' ' || str[i] == '\r' || str[i] == '\n' || str[i] == '\t')
    {
      if (!current.empty())
      {
        res.pushBack(current);
        current = "";
      }
    }
    else
    {
      current += str[i];
    }
  }
  if (!current.empty())
  {
    res.pushBack(current);
  }
  return res;
}

bool kuchukbaeva::tryParseUInt(const std::string& str, unsigned int& out)
{
  if (str.empty())
  {
    return false;
  }
  unsigned long long res = 0;
  for (size_t i = 0; i < str.length(); ++i)
  {
    if (str[i] < '0' || str[i] > '9')
    {
      return false;
    }
    res = res * 10 + (str[i] - '0');
    if (res > 4294967295ULL)
    {
      return false;
    }
  }
  out = static_cast<unsigned int>(res);
  return true;
}

kuchukbaeva::Application::Application():
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

void kuchukbaeva::Application::loadFromFile(const std::string& filename)
{
  std::ifstream file(filename);
  if (!file.is_open())
  {
    throw std::runtime_error("Cannot open file");
  }

  std::string line;
  while (std::getline(file, line))
  {
    Vector< std::string > tokens = splitString(line);
    if (tokens.getSize() == 0)
    {
      continue;
    }
    if (tokens.getSize() == 2)
    {
      std::string graphName = tokens[0];
      unsigned int edgeCount;
      if (!tryParseUInt(tokens[1], edgeCount))
      {
        continue;
      }
      Graph g;
      for (unsigned int i = 0; i < edgeCount; ++i)
      {
        std::string edgeLine;
        if (std::getline(file, edgeLine))
        {
          Vector< std::string > edgeTokens = splitString(edgeLine);
          if (edgeTokens.getSize() >= 3)
          {
            std::string src = edgeTokens[0];
            std::string dest = edgeTokens[1];
            unsigned int weight;
            if (!tryParseUInt(edgeTokens[2], weight))
            {
              continue;
            }
            bool srcFound = false;
            bool destFound = false;
            for (size_t v = 0; v < g.vertexes.getSize(); ++v)
            {
              if (g.vertexes[v] == src)
              {
                srcFound = true;
              }
              if (g.vertexes[v] == dest)
              {
                destFound = true;
              }
            }
            if (!srcFound)
            {
              g.vertexes.pushBack(src);
            }
            if (!destFound)
            {
              g.vertexes.pushBack(dest);
            }

            std::pair< std::string, std::string > key(src, dest);
            Vector< unsigned int >* weights = g.edges.find(key);
            if (weights)
            {
              weights->pushBack(weight);
            }
            else
            {
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

void kuchukbaeva::Application::run(const std::string& filename)
{
  loadFromFile(filename);
  std::string line;
  while (std::getline(std::cin, line))
  {
    processLine(line);
  }
}

void kuchukbaeva::Application::processLine(const std::string& line)
{
  Vector< std::string > tokens = splitString(line);
  if (tokens.getSize() == 0)
  {
    return;
  }
  CommandFunc* funcPtr = commands_.find(tokens[0]);
  if (funcPtr)
  {
    (*funcPtr)(this, tokens);
  }
  else
  {
    std::cout << "<INVALID COMMAND>\n";
  }
}

void kuchukbaeva::Application::cmdGraphs(Application* app, const Vector< std::string >& args)
{
  if (args.getSize() != 1)
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }
  Vector< std::string > names;
  for (auto it = app->graphs_.cbegin(); it != app->graphs_.cend(); ++it)
  {
    names.pushBack(it->first);
  }
  if (names.getSize() == 0)
  {
    std::cout << "\n";
    return;
  }
  sortVector(names);
  for (size_t i = 0; i < names.getSize(); ++i)
  {
    std::cout << names[i] << "\n";
  }
}

void kuchukbaeva::Application::cmdVertexes(Application* app, const Vector< std::string >& args)
{
  if (args.getSize() != 2)
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }
  Graph* g = app->graphs_.find(args[1]);
  if (!g)
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }
  Vector< std::string > verts = g->getVertexes();
  if (verts.getSize() == 0)
  {
    std::cout << "\n";
    return;
  }
  sortVector(verts);
  for (size_t i = 0; i < verts.getSize(); ++i)
  {
    std::cout << verts[i] << "\n";
  }
}

void kuchukbaeva::Application::cmdOutbound(Application* app, const Vector< std::string >& args)
{
  if (args.getSize() != 3) {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }
  Graph* g = app->graphs_.find(args[1]);
  if (!g || !g->hasVertexes(args[2]))
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }
  Vector< std::pair< std::string, unsigned int > > res;
  g->getOutbound(args[2], res);
  for (size_t i = 0; i < res.getSize(); ++i)
  {
    std::cout << res[i].first << " " << res[i].second << "\n";
  }
}

void kuchukbaeva::Application::cmdInbound(Application* app, const Vector< std::string >& args)
{
  if (args.getSize() != 3)
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }
  Graph* g = app->graphs_.find(args[1]);
  if (!g || !g->hasVertex(args[2]))
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }
  Vector< std::pair< std::string, unsigned int > > res;
  g->getInbound(args[2], res);
  for (size_t i = 0; i < res.getSize(); ++i)
  {
    std::cout << res[i].first << " " << res[i].second << "\n";
  }
}

void kuchukbaeva::Application::cmdBind(Application* app, const Vector< std::string >& args)
{
  unsigned int weight = 0;
  if (args.getSize() != 5 || !tryParseUInt(args[4], weight))
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }
  Graph* g = app->graphs_.find(args[1]);
  if (!g || !g->hasVertex(args[2]) || !g->hasVertex(args[3]))
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }
  g->addEdge(args[2], args[3], weight);
}

void kuchukbaeva::Application::cmdCut(Application* app, const Vector< std::string >& args)
{
  unsigned int weight = 0;
  if (args.getSize() != 5 || !tryParseUInt(args[4], weight))
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }
  Graph* g = app->graphs_.find(args[1]);
  if (!g || !g->cutEdge(args[2], args[3], weight))
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }
}

void kuchukbaeva::Application::cmdCreate(Application* app, const Vector< std::string >& args)
{
  if (args.getSize() < 2 || app->graphs_.has(args[1]))
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }
  Graph newG;
  for (size_t i = 2; i < args.getSize(); ++i)
  {
    newG.addVertex(args[i]);
  }
  app->graphs_.add(args[1], newG);
}

void Application::cmdMerge(Application* app, const Vector< std::string >& args)
{
  if (args.getSize() != 4 || app->graphs_.has(args[1]))
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }
  Graph* g1 = app->graphs_.find(args[2]);
  Graph* g2 = app->graphs_.find(args[3]);
  if (!g1 || !g2)
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }
  app->graphs_.add(args[1], g1->merge(*g2));
}

void kuchukbaeva::Application::cmdExtract(Application* app, const Vector< std::string >& args)
{
  if (args.getSize() < 4 || app->graphs_.has(args[1]))
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }
  Graph* oldG = app->graphs_.find(args[2]);
  unsigned int count = 0;
  if (!oldG || !tryParseUInt(args[3], count) || args.getSize() != 4 + count)
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }
  Vector< std::string > vToExtract;
  for (unsigned int i = 0; i < count; ++i)
  {
    std::string v = args[4 + i];
    for (unsigned int j = i + 1; j < count; ++j)
    {
      if (v == args[4 + j])
      {
        std::cout << "<INVALID COMMAND>\n";
        return;
      }
    }
    if (!oldG->hasVertex(v))
    {
      std::cout << "<INVALID COMMAND>\n";
      return;
    }
    vToExtract.pushBack(v);
  }
  app->graphs_.add(args[1], oldG->extract(vToExtract));
}

