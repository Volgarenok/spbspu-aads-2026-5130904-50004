#include "expressions_processing.h"

#include "stack.h"
#include "safety_math.h"
#include <stdexcept>
#include <cctype>

int alekseev::count_from_string(const std::string & str_expr)
{
  Queue< List<char> *> infix = str_to_infix(str_expr);
  Queue< List<char> *> postfix;
  try {
    postfix = infix_to_postfix(infix);
  } catch (...) {
    while (!infix.empty()) {
      List< char > * tmp = infix.front();
      infix.pop();
      clear(tmp->next, tmp);
      rmfake(tmp);
    }
  }
  while (!infix.empty()) {
    List< char > * tmp = infix.front();
    infix.pop();
    clear(tmp->next, tmp);
    rmfake(tmp);
  }
  int res;
  try {
    res = count_postfix(postfix);
  }catch (...) {
    while (!postfix.empty()) {
      List< char > * tmp = postfix.front();
      postfix.pop();
      clear(tmp->next, tmp);
      rmfake(tmp);
    }
  }
  while (!postfix.empty()) {
    List< char > * tmp = postfix.front();
    postfix.pop();
    clear(tmp->next, tmp);
    rmfake(tmp);
  }
  return res;
}

alekseev::Queue< alekseev::List< char > * > alekseev::str_to_infix(const std::string & str_expr)
{
  Queue< List< char > * > res;
  size_t i = 0;
  while (i < str_expr.size()) {
    char current_char = str_expr[i++];
    List< char > * cur_fake = nullptr;
    try {
      cur_fake = fake< char >();
      List< char > * cur_tail = cur_fake;
      while (current_char != ' ' && i < str_expr.size()) {
        cur_tail = insert_after(cur_tail, current_char);
        current_char = str_expr[i++];
      }
      char cfnd = cur_fake->next->data;
      if (!is_operator(cfnd) && cfnd != '(' && cfnd != ')' && !is_number(cur_fake)) {
        throw std::invalid_argument("Bad input: not a number or operator");
      }
      res.push(cur_fake);
    } catch (...) {
      clear(cur_fake->next, cur_fake);
      rmfake(cur_fake);
      while (!res.empty()) {
        List< char > * tmp = res.front();
        res.pop();
        clear(tmp->next, tmp);
        rmfake(tmp);
      }
      throw;
    }
  }
  return res;
}

alekseev::Queue< alekseev::List< char > * > alekseev::infix_to_postfix(
    Queue< List< char > * > infix)
{
  Stack< List< char > * > stack;
  Queue< List< char > * > postfix;
  List< char > * current = nullptr;
  try {
    while (!infix.empty()) {
      current = deep_copy(infix.front());
      infix.pop();
      char first_char = current->next->data;
      if (first_char == '(') {
        stack.push(current);
        current = nullptr;
      } else if (first_char == ')') {
        if (!stack.empty()) {
          while (stack.top()->next->data != '(') {
            postfix.push(stack.top());
            stack.pop();
            if (stack.empty()) {
              throw std::invalid_argument("Invalid expression");
            }
          }
          List< char > * tmp = stack.top();
          stack.pop();
          clear(tmp->next, tmp);
          rmfake(tmp);
        } else {
          throw std::invalid_argument("Invalid expression");
        }
        clear(current->next, current);
        rmfake(current);
        current = nullptr;
      } else if (is_operator(first_char)) {
        if (!stack.empty()) {
          while (priority_of(stack.top()->next->data) >= priority_of(first_char)) {
            postfix.push(stack.top());
            stack.pop();
            if (stack.empty()) {
              break;
            }
          }
        }
        stack.push(current);
        current = nullptr;
      } else {
        postfix.push(current);
        current = nullptr;
      }
    }
    while (!stack.empty()) {
      if (stack.top()->next->data == '(') {
        throw std::invalid_argument("Invalid expression");
      }
      postfix.push(stack.top());
      stack.pop();
    }
  } catch (...) {
    while (!stack.empty()) {
      List< char > * tmp = stack.top();
      stack.pop();
      clear(tmp->next, tmp);
      rmfake(tmp);
    }
    while (!postfix.empty()) {
      List< char > * tmp = postfix.front();
      postfix.pop();
      clear(tmp->next, tmp);
      rmfake(tmp);
    }
    if (current) {
      clear(current->next, current);
      rmfake(current);
    }
    throw;
  }
  return postfix;
}

int alekseev::count_postfix(Queue< List< char > * > postfix)
{
  Stack< int > stack;
  while (!postfix.empty()) {
    List< char > * current = postfix.front();
    postfix.pop();
    if (is_operator(current->next->data)) {
      char op = current->next->data;
      if (op == '#') {
        if (stack.empty()) {
          throw std::invalid_argument("Invalid expression");
        }
        int n = stack.top();
        stack.pop();
        stack.push(flip(n));
      } else {
        if (stack.size() < 2) {
          throw std::invalid_argument("Invalid expression");
        }
        int b = stack.top();
        stack.pop();
        int a = stack.top();
        stack.pop();
        stack.push(count(a, b, op));
      }
    } else {
      stack.push(ltoi(current));
    }
  }
  if (stack.size() > 1) {
    throw std::invalid_argument("Invalid expression");
  }
  return stack.top();
}

short alekseev::priority_of(char op)
{
  if (op == '#') {
    return 3;
  } else if (op == '*' || op == '/' || op == '%') {
    return 2;
  } else if (op == '+' || op == '-') {
    return 1;
  }
  return 0;
}

bool alekseev::is_operator(char op)
{
  return op == '#' || op == '*' || op == '/' || op == '%' || op == '+' || op == '-';
}

bool alekseev::is_number(List< char > * li)
{
  List< char > * current = li->next;
  while (current != li) {
    if (!isdigit(current->data)) {
      return false;
    }
    current = current->next;
  }
  return true;
}

int alekseev::ltoi(List< char > * li)
{
  List< char > * current = li->next;
  std::string res;
  while (current != li) {
    res += current->data;
    current = current->next;
  }
  return stoi(res);
}

int alekseev::count(int a, int b, char op)
{
  if (op == '*') {
    return mul(a, b);
  } else if (op == '/') {
    return div(a, b);
  } else if (op == '%') {
    return mod(a, b);
  } else if (op == '+') {
    return sum(a, b);
  } else if (op == '-') {
    return sub(a, b);
  }
  throw std::invalid_argument("Invalid operation");
}
