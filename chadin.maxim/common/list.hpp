#ifndef LIST_HPP
#define LIST_HPP

#include <stdexcept>
#include "node.hpp"

namespace chadin
{
  template< class T >
  class List
  {
  public:
    List():
      head_(nullptr),
      tail_(nullptr)
    {}

    ~List()
    {
      clear();
    }

    T & getBack() { return tail_->data; }
    T & getFront() { return head_->data; }
    bool isEmpty() const { return head_ == nullptr; }

    void clear()
    {
      while (!isEmpty())
      {
        popFront();
      }
    }

  private:
    Node< T > * head_;
    Node< T > * tail_;
  };
}

#endif
