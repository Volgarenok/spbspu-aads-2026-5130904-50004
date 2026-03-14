#ifndef POZDEEV_BILIST_HPP
#define POZDEEV_BILIST_HPP

#include <cstddef>
#include <stdexcept>
#include <utility>

namespace pozdeev {

template<class T>
class BiList;

template<class T>
class Node {
public:
  T val_;
  Node<T>* prev_;
  Node<T>* next_;

  Node(const T& value) :
    val_(value),
    prev_(nullptr),
    next_(nullptr)
  {
  }

  Node(T&& value) :
    val_(std::move(value)),
    prev_(nullptr),
    next_(nullptr)
  {
  }

  Node(const T& value, Node* p, Node* n) :
    val_(value),
    prev_(p),
    next_(n)
  {
  }

  Node(T&& value, Node* p, Node* n) :
    val_(std::move(value)),
    prev_(p),
    next_(n)
  {
  }
};

}

#endif
