#ifndef EXPRESSIONS_PROCESSING_H
#define EXPRESSIONS_PROCESSING_H

#include "queue.h"
#include <string>

namespace alekseev {
  int count_from_string(const std::string & str_expr);
  Queue< List< char > * > str_to_infix(const std::string & str_expr);
  Queue< List< char > * > infix_to_postfix(Queue< List< char > * > infix);
  int count_postfix(Queue< List< char > * > postfix);
  short priority_of(char op);
  bool is_operator(char op);
  bool is_number(List< char > * li);
  int ltoi(List< char > * li);
  int count(int a, int b, char op);
}

#endif
