#ifndef EXPRESSIONS_PROCESSING_H
#define EXPRESSIONS_PROCESSING_H

#include "queue.h"
#include <iostream>
#include <string>

namespace alekseev {
  Queue< List< char > * > stoq(const std::string & str_expr);
  Queue< List< char > * > infix_to_postfix(Queue< List< char > * > infix);
  int count_expr(Queue< char * > & postfix);
  short priority_of(char op);
}

#endif
