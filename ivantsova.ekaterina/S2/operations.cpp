#include "operations.hpp"
#include <sstream>
#include <limits>

int ivantsova::getPriority(const std::string& op) {
  if (op == "+" || op == "-") {
    return 1;
  }
  if (op == "*" || op == "/" || op == "%") {
    return 2;
  }
  if (op == "<<") {
    return 3;
  }
  return 0;
}

bool ivantsova::isOperator(const std::string& token) {
  return token == "+" || token == "-" || token == "*" || token == "/" || token == "%" || token == "<<";
}

bool ivantsova::isNumber(const std::string& token) {
  if (token.empty()) {
    return false;
  }
  size_t start = 0;
  if (token[0] == '-') {
    if (token.size() == 1) {
      return false;
    }
    start = 1;
  }
  for (size_t i = start; i < token.size(); ++i) {
    if (!std::isdigit(token[i])) {
        return false;
    }
  }
  return true;
}

long long ivantsova::useOperation(long long a, long long b, const std::string& op) {
  if (op == "+") {
    if (b > 0 && a > std::numeric_limits< long long >::max() - b) {
      throw std::overflow_error("Addition overflow");
    }
    if (b < a && a < std::numeric_limits< long long >::min() - b) {
      throw std::underflow_error("Addition underflow");
    }
    return a + b;
  }
  if (op == "-") {
    if (b < 0 && a > std::numeric_limits< long long >::max() + b) {
      throw std::overflow_error("Substraction overflow");
    }
    if (b > a && a < std::numeric_limits< long long >::min() + b) {
      throw std::underflow_error("Substraction underflow");
    }
    return a - b;
  }
  if (op == "*") {
    if (a != 0 && b != 0) {
      if ((a > 0 && b > 0 && a > std::numeric_limits< long long >::max() / b) \
       || (a < 0 && b < 0 && a < std::numeric_limits< long long >::max() / b)) {
        throw std::overflow_error("Multiplication overflow");
      }
      if ((a > 0 && b < 0 && b < std::numeric_limits< long long >::min() / a) \
      || (a < 0 && b > 0 && a < std::numeric_limits< long long >::min() / b)) {
        throw std::underflow_error("Multiplication underflow");
      }
    }
    return a * b;
  }
  if (op == "/") {
    if (b == 0) {
      throw std::runtime_error("Division by zero");
    }
    return a / b;
  }
  if (op == "%") {
    if (b == 0) {
      throw std::runtime_error("Division by zero");
    }
    if (a % b < 0) {
      if (b > 0) {
        return a % b + b;
      } else {
        return a % b - b;
      }
    }
    return a % b;
  }
  if (op == "<<") {
    if (b < 0) {
      throw std::runtime_error("Shift by negative number");
    }
    if (b >= static_cast< int >(sizeof(long long) * 8)) {
      throw std::overflow_error("Shift number too large");
    }
    return a << b;
  }
  throw std::runtime_error("Unknown operator");
}

ivantsova::Queue< std::string > ivantsova::convertToPostfix(const std::string& line) {
  std::stringstream ss(line);
  std::string token;
  Queue< std::string > input;
  while (ss >> token) {
    input.push(token);
  }
  if (input.empty()) {
    throw std::runtime_error("Empty expression");
  }
  Queue< std::string > output;
  Stack< std::string > operators;
  while (!input.empty()) {
    std::string tok = input.pop();
    if (isNumber(tok)) {
      output.push(tok);
    }
    else if (tok == "(") {
      operators.push(tok);
    }
    else if (tok == ")") {
      while (!operators.empty() && operators.top() != "(") {
        output.push(operators.pop());
      }
      if (operators.empty()) {
        throw std::runtime_error("Mismatched parentheses");
      }
      operators.pop();
    }
    else if (isOperator(tok)) {
      while (!operators.empty() && operators.top() != "(" && getPriority(operators.top()) >= getPriority(tok)) {
        output.push(operators.pop());
      }
      operators.push(tok);
    }
    else {
      throw std::runtime_error("Invalid token");
    }
  }
  while (!operators.empty()) {
    if (operators.top() == "(" || operators.top() == ")") {
      throw std::runtime_error("Mismatched parentheses");
    }
    output.push(operators.pop());
  }
  return output;
}

long long ivantsova::calculatePostfix(Queue< std::string >& postfix) {
  Stack< long long > evalStack;
  while (!postfix.empty()) {
    std::string tok = postfix.pop();
    if (isNumber(tok)) {
      evalStack.push(std::stoll(tok));
    }
    else if (isOperator(tok)) {
      if (evalStack.size() < 2) {
        throw std::runtime_error("Not enough operands");
      }
      long long b = evalStack.pop();
      long long a = evalStack.pop();
      evalStack.push(useOperation(a, b, tok));
    }
    else {
        throw std::runtime_error("Invalid token in postfix");
    }
  }
  if (evalStack.size() != 1) {
    throw std::runtime_error("Invalid expression");
  }
  return evalStack.pop();
}

long long ivantsova::calculateExpression(const std::string& line) {
  Queue< std::string > postfix = convertToPostfix(line);
  return calculatePostfix(postfix);
}
