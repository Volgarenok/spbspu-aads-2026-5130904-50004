#ifndef OPERATIONS_HPP
#define OPERATIONS_HPP

#include "stack.hpp"
#include "queue.hpp"
#include <string>

namespace ivantsova {
  int getPriority(const std::string& op);
  bool isOperator(const std::string& token);
  bool isNumber(const std::string& token);
  long long useOperation(long long a, long long b, const std::string& line);
  Queue< std::string > convertToPostfix(const std::string& line);
  long long calculatePostfix(Queue< std::string >& postfix);
  long long calculateExpression(const std::string& line);
};

#endif
