#include "expressions_processing.h"

#include "stack.h"
#include <exception>
#include <cctype>

alekseev::Queue< alekseev::List< char > * > alekseev::stoq(const std::string & str_expr)
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
  Stack< List< char > * > symbols_stack;
  Queue< List< char > * > postfix;
  List< char > * current = nullptr;
  try {
    while (!infix.empty()) {
      current = deep_copy(infix.front());
      infix.pop();
      char first_char = current->next->data;
      if (first_char == '(') {
        symbols_stack.push(current);
        current = nullptr;
      } else if (first_char == ')') {
        if (!symbols_stack.empty()) {
          while (symbols_stack.top()->next->data != '(') {
            postfix.push(symbols_stack.top());
            symbols_stack.pop();
            if (symbols_stack.empty()) {
              throw std::invalid_argument("Invalid expression");
            }
          }
          List< char > * tmp = symbols_stack.top();
          symbols_stack.pop();
          clear(tmp->next, tmp);
          rmfake(tmp);
        } else {
          throw std::invalid_argument("Invalid expression");
        }
        clear(current->next, current);
        rmfake(current);
        current = nullptr;
      } else if (is_operator(first_char)) {
        if (!symbols_stack.empty()) {
          while (priority_of(symbols_stack.top()->next->data) >= priority_of(first_char)) {
            postfix.push(symbols_stack.top());
            symbols_stack.pop();
            if (symbols_stack.empty()) {
              break;
            }
          }
        }
        symbols_stack.push(current);
        current = nullptr;
      } else {
        postfix.push(current);
        current = nullptr;
      }
    }
    while (!symbols_stack.empty()) {
      if (symbols_stack.top()->next->data == '(') {
        throw std::invalid_argument("Invalid expression");
      }
      postfix.push(symbols_stack.top());
      symbols_stack.pop();
    }
  } catch (...) {
    while (!symbols_stack.empty()) {
      List< char > * tmp = symbols_stack.top();
      symbols_stack.pop();
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

int alekseev::ltoi(List<char> * li)
{
  List< char > * current = li->next;
  std::string res;
  while (current != li) {
    res += current->data;
    current = current->next;
  }
  return stoi(res);
}
