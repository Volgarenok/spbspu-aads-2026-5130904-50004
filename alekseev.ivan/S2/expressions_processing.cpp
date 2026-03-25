#include "expressions_processing.h"

#include "stack.h"

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
    Queue< List< char > * > & infix)
{
  Stack< List< char > * > symbols_stack;
  Queue< List< char > * > postfix;
  while (!infix.empty()) {
    List< char > * current = infix.front();
    infix.pop();
    char first_char = current->next->data;
    if (first_char == '(') {
      symbols_stack.push(current);
    } else if (first_char == ')') {
      if (!symbols_stack.empty()) {
        while (symbols_stack.top()->next->data != '(') {
          postfix.push(symbols_stack.top());
          symbols_stack.pop();
          // if symbols_stack.empty() -> error
        }
        symbols_stack.pop();
      }
      // else error
    } else if (first_char == '#' || first_char == '*' || first_char == '/' || first_char == '%' ||
      first_char == '+' || first_char == '-') {
      if (!symbols_stack.empty()) {
        while (priority_of(first_char) >= priority_of(symbols_stack.top()->next->data)) {
          postfix.push(symbols_stack.top());
          symbols_stack.pop();
        }
      }
      symbols_stack.push(current);
    } else {
      postfix.push(current);
    }
  }
  while (!symbols_stack.empty()) {
    // if symbols_stack.top()->next->data == '(' -> error
    postfix.push(symbols_stack.top());
    symbols_stack.pop();
  }
  return postfix;
}

short alekseev::priority_of(char op)
{
  if (op == '#') {
    return 0;
  } else if (op == '*' || op == '/' || op == '%') {
    return 1;
  } else if (op == '+' || op == '-') {
    return 2;
  }
  return -1;
}
