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

    void pushBack(const T & val)
    {
      Node< T > * newNode = new Node< T >{val, nullptr, tail_};
      if (tail_)
      {
        tail_->next = newNode;
      }
      else
      {
        head_ = newNode;
      }
      tail_ = newNode;
    }

    void pushFront(const T & val)
    {
      Node< T > * newNode = new Node< T >{val, head_, nullptr};
      if (head_)
      {
        head_->prev = newNode;
      }
      else
      {
        tail_ = newNode;
      }
      head_ = newNode;
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
