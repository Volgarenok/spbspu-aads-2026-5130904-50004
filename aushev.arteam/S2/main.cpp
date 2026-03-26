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

}
}

int main()
{
  return 0;
}
