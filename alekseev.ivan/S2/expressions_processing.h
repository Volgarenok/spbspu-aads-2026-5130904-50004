#ifndef EXPRESSIONS_PROCESSING_H
#define EXPRESSIONS_PROCESSING_H

#include "queue.h"
#include <string>

namespace alekseev {
  using QLCh = Queue< List< char > * >;
  int count_from_string(const std::string & str_expr);
  QLCh str_to_infix(const std::string & str_expr);
  QLCh infix_to_postfix(QLCh infix);
  int count_postfix(QLCh postfix);
  short priority_of(char op);
  bool is_operator(char op);
  bool is_number(List< char > * li);
  int ltoi(List< char > * li);
  int count(int a, int b, char op);
}

#endif
