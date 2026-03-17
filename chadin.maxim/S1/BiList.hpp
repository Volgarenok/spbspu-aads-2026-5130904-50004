#ifndef CHADIN_BILIST_HPP
#define CHADIN_BILIST_HPP

#include <stdexcept>
#include <utility>

namespace chadin
{
  template< class T >
  struct Node
  {
    T val;
    Node* prev;
    Node* next;

    Node(const T& value) :
      val(value),
      prev(nullptr),
      next(nullptr)
    {}

    Node(T&& value) :
      val(std::move(value)),
      prev(nullptr),
      next(nullptr)
    {}
  };

  template< class T >
  class BiList;
}

#endif
