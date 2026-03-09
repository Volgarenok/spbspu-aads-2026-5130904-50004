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

  bool empty() const;
  size_t size() const;
  void clear();

  void push_front(const T& value);
  void push_back(const T& value);

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

template< class T >
bool List< T >::empty() const
{
  return size_ == 0;
}

template< class T >
size_t List< T >::size() const
{
  return size_;
}

template< class T >
void List< T >::clear()
{
  while (head_ != nullptr) {
    Node* tmp = head_;
    head_ = head_->next;
    delete tmp;
  }
  tail_ = nullptr;
  size_ = 0;
}

template< class T >
void List< T >::push_front(const T& value)
{
  Node* newNode = new Node;
  newNode->data = value;
  newNode->next = head_;
  head_ = newNode;
  if (tail_ == nullptr) {
    tail_ = newNode;
  }
  ++size_;
}

template< class T >
void List< T >::push_back(const T& value)
{
  Node* newNode = new Node;
  newNode->data = value;
  newNode->next = nullptr;
  if (tail_ == nullptr) {
    head_ = newNode;
    tail_ = newNode;
  } else {
    tail_->next = newNode;
    tail_ = newNode;
  }
  ++size_;
}

}

#endif
