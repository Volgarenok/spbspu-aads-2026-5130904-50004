#ifndef STACK_H
#define STACK_H

#include "../common/ListIterators.h"

namespace alekseev {
  template< class T >
  struct Stack {
    List< T > fake_node;

    void push(T & rhs);
    T pop();
  };
}

#endif
