#include "expr.hpp"
#include "stack.hpp"
#include "queue.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

namespace akhrameev {

bool is_operator(const std::string& s) {
  return s == "+" || s == "-" || s == "*" || s == "/" || s == "%" || s == "!";
}

int get_priority(const std::string& op) {
  if (op == "!") return 4;
  if (op == "*" || op == "/" || op == "%") return 3;
  if (op == "+" || op == "-") return 2;
  return 1;
}

bool is_left_assoc(const std::string& op) {
  return op != "!";
}

void tokenize(const std::string& line, Queue<std::string>& out) {
  size_t i = 0;
  while (i < line.size()) {
    size_t j = line.find(' ', i);
    if (j == std::string::npos) j = line.size();
    if (j > i) out.push(line.substr(i, j - i));
    i = j + 1;
  }
}

void to_postfix(Queue<std::string>& tokens, Queue<std::string>& out) {
  Stack<std::string> ops;
  while (!tokens.empty()) {
    std::string t = tokens.drop();
    if (t == "(") {
      ops.push(t);
    } else if (t == ")") {
      while (!ops.empty() && ops.top() != "(") {
        out.push(ops.drop());
      }
      if (ops.empty()) throw std::runtime_error("Ошибка в скобках");
      ops.drop();
    } else if (is_operator(t)) {
      int p1 = get_priority(t);
      while (!ops.empty() && ops.top() != "(") {
        int p2 = get_priority(ops.top());
        if (p2 > p1 || (p2 == p1 && is_left_assoc(t))) {
          out.push(ops.drop());
        } else {
          break;
        }
      }
      ops.push(t);
    } else {
      out.push(t);
    }
  }
  while (!ops.empty()) {
    if (ops.top() == "(") throw std::runtime_error("Ошибка в скобках");
    out.push(ops.drop());
  }
}

long long calc_postfix(Queue<std::string>& post) {
  Stack<long long> nums;
  while (!post.empty()) {
    std::string t = post.drop();
    if (is_operator(t)) {
      if (t == "!") {
        if (nums.empty()) throw std::runtime_error("Неверное выражение");
        long long a = nums.drop();
        nums.push(~a);
      } else {
        if (nums.empty()) throw std::runtime_error("Неверное выражение");
        long long b = nums.drop();
        if (nums.empty()) throw std::runtime_error("Неверное выражение");
        long long a = nums.drop();

        if (t == "+") nums.push(a + b);
        else if (t == "-") nums.push(a - b);
        else if (t == "*") nums.push(a * b);
        else if (t == "/") {
          if (b == 0) throw std::runtime_error("Деление на ноль");
          nums.push(a / b);
        } else if (t == "%") {
          if (b == 0) throw std::runtime_error("Остаток от деления на ноль");
          nums.push(a % b);
        }
      }
    } else {
      nums.push(std::stoll(t));
    }
  }
  if (nums.empty()) throw std::runtime_error("Пустое выражение");
  return nums.drop();
}

int run(int argc, char* argv[]) {
  std::istream* input = &std::cin;
  std::ifstream file;
  if (argc > 1) {
    file.open(argv[1]);
    if (!file.is_open()) {
      std::cerr << "Ошибка: не удалось открыть файл " << argv[1] << "\n";
      return 1;
    }
    input = &file;
  }

  std::string line;
  while (std::getline(*input, line)) {
    Queue<std::string> tokens;
    tokenize(line, tokens);
    Queue<std::string> postfix;
    to_postfix(tokens, postfix);
    long long res = calc_postfix(postfix);
    std::cout << res << " ";
  }
  std::cout << "\n";
  return 0;
}

} 