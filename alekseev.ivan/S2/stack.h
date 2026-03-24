#ifndef STACK_H
#define STACK_H

#include "../common/ListIterators.h"

namespace alekseev {
  template< class T >
  struct Stack {
    List< T > fake_node_;
    size_t size_;

    Stack();
    ~Stack();
    Stack( const Stack & );
    Stack & operator=( const Stack & );
    Stack( Stack && );
    Stack & operator=( Stack && );

    void push(T & rhs);
    void pop();
    T & top();
    bool empty();
    size_t size();
  };
}

#endif
