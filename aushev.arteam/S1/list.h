#ifndef LIST_H
#define LIST_H

#include <cstddef>

namespace aushev {

template< class T >
class List;

template< class T >
class LIter {
  friend class List< T >;

private:
  struct Node {
    T data;
    Node* next;
  };
  Node* node_;
};

template< class T >
class LCIter {
  friend class List< T >;

private:
  struct Node {
    T data;
    Node* next;
  };
  const Node* node_;
};

template< class T >
class List {
public:
  List();
  ~List();
  List(const List& other);
  List& operator=(const List& other);
  List(List&& other) noexcept;
  List& operator=(List&& other) noexcept;

private:
  struct Node {
    T data;
    Node* next;
  };
  Node* head_;
  Node* tail_;
  size_t size_;
};

template< class T >
List< T >::List()
  : head_(nullptr)
  , tail_(nullptr)
  , size_(0)
{
}

template< class T >
List< T >::~List()
{
  clear();
}

template< class T >
List< T >::List(const List& other)
  : head_(nullptr)
  , tail_(nullptr)
  , size_(0)
{
  for (const auto& item : other) {
    push_back(item);
  }
}

template< class T >
List< T >& List< T >::operator=(const List& other)
{
  if (this != &other) {
    clear();
    for (const auto& item : other) {
      push_back(item);
    }
  }
  return *this;
}

template< class T >
List< T >::List(List&& other) noexcept
  : head_(other.head_)
  , tail_(other.tail_)
  , size_(other.size_)
{
  other.head_ = nullptr;
  other.tail_ = nullptr;
  other.size_ = 0;
}

template< class T >
List< T >& List< T >::operator=(List&& other) noexcept
{
  if (this != &other) {
    clear();
    head_ = other.head_;
    tail_ = other.tail_;
    size_ = other.size_;
    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.size_ = 0;
  }
  return *this;
}

}

#endif
