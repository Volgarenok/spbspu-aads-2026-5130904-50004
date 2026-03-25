#ifndef EXPRESSIONS_PROCESSING_H
#define EXPRESSIONS_PROCESSING_H

#include "queue.h"
#include <iostream>

namespace alekseev {
  Queue< char * > input_expr(std::istream & in);
  Queue< char * > infix_to_postfix(Queue< char * > & infix);
  int count_expr(Queue< char * > & postfix);
}

#endif
