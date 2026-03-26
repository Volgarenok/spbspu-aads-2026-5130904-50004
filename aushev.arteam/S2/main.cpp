#include <iostream>
#include <fstream>
#include "stack.h"
#include "queue.h"

namespace aushev {

namespace {

const int MAX_TOKEN_SIZE = 100;

struct Token {
  char data[MAX_TOKEN_SIZE];
  size_t size;

  Token() : size(0) {
    data[0] = '\0';
  }

  void append(char c) {
    if (size < MAX_TOKEN_SIZE - 1) {
      data[size++] = c;
      data[size] = '\0';
    }
  }

  void clear() {
    size = 0;
    data[0] = '\0';
  }

  bool isEmpty() const {
    return size == 0;
  }

  bool isDigit(char c) const {
    return c >= '0' && c <= '9';
  }

  bool isSpace(char c) const {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
  }

  bool isNumber() const {
    if (size == 0) {
      return false;
    }
    for (size_t i = 0; i < size; ++i) {
      if (i == 0 && data[i] == '-') {
        if (size == 1) {
          return false;
        }
        continue;
      }
      if (!isDigit(data[i])) {
        return false;
      }
    }
    return true;
  }

  bool isOperator() const {
    if (size != 1) {
      return false;
    }
    char c = data[0];
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '%';
  }

  bool isOpenParen() const {
    return size == 1 && data[0] == '(';
  }

  bool isCloseParen() const {
    return size == 1 && data[0] == ')';
  }

  long long toNumber() const {
    long long result = 0;
    long long sign = 1;
    size_t start = 0;

    if (size > 0 && data[0] == '-') {
      sign = -1;
      start = 1;
    }

    for (size_t i = start; i < size; ++i) {
      result = result * 10 + (data[i] - '0');
    }

    return result * sign;
  }

  char getOperator() const {
    return data[0];
  }
};

int getPrecedence(const Token& op)
{
  if (op.size != 1) {
    return 0;
  }
  char c = op.data[0];
  if (c == '+' || c == '-') {
    return 1;
  }
  if (c == '*' || c == '/' || c == '%') {
    return 2;
  }
  return 0;
}

List< Token > infixToPostfix(const List< Token >& infix)
{
  List< Token > postfix;
  Stack< Token > opStack;

  for (auto it = infix.begin(); it != infix.end(); ++it) {
    const Token& token = *it;

    if (token.isNumber()) {
      postfix.push_back(token);
    } else if (token.isOpenParen()) {
      opStack.push(token);
    } else if (token.isCloseParen()) {
      while (!opStack.empty() && !opStack.top().isOpenParen()) {
        postfix.push_back(opStack.drop());
      }
      if (opStack.empty()) {
        throw std::logic_error("Mismatched parentheses");
      }
      opStack.drop();
    } else if (token.isOperator()) {
      while (!opStack.empty() && !opStack.top().isOpenParen() &&
             getPrecedence(opStack.top()) >= getPrecedence(token)) {
        postfix.push_back(opStack.drop());
      }
      opStack.push(token);
    } else {
      throw std::logic_error("Invalid token");
    }
  }

  while (!opStack.empty()) {
    Token op = opStack.drop();
    if (op.isOpenParen() || op.isCloseParen()) {
      throw std::logic_error("Mismatched parentheses");
    }
    postfix.push_back(op);
  }

  return postfix;
}

}

}

int main()
{
  return 0;
}