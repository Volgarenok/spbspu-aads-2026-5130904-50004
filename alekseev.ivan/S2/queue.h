#ifndef QUEUE_H
#define QUEUE_H

#include "../common/List.h"
#include <cstddef>

template< class T >
struct Queue {
  alekseev::List< T > * fake_node, * tail;
  size_t size_;

  Queue();
  ~Queue();
  Queue(const Queue & rhs);
  Queue & operator=(const Queue & rhs);
  Queue(const Queue && rhs);
  Queue & operator=(Queue && rhs);

  template< class U >
  void push(U && value);

  void pop();
  T & front();
  T & back();
  bool empty() const;
  size_t size() const;
};

#endif
