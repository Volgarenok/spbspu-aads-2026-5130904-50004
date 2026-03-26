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

template< class T >
class LIter {
  friend class List< T >;

private:
  Node< T >* node_;
  List< T >* list_;
};

template< class T >
class LCIter {
  friend class List< T >;

private:
  const Node< T >* node_;
  const List< T >* list_;
};

template< class T >
class List {
  friend class LIter< T >;
  friend class LCIter< T >;

private:
  using NodeT = Node< T >;
  NodeT* head_;
  NodeT* tail_;
  size_t size_;
};

}

#endif
