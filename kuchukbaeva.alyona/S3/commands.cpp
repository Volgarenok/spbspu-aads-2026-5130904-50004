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
}
