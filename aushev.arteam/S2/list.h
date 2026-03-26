#ifndef LIST_H
#define LIST_H

#include <cstddef>

namespace aushev {

template< class T >
struct Node {
  T data;
  Node* next;
  Node* prev;
};

template< class T >
class List;

}

#endif
