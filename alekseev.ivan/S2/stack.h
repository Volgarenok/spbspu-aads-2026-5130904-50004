#ifndef STACK_H
#define STACK_H

#include "../common/ListIterators.h"

namespace alekseev {
  template< class T >
  struct Stack {
    List< T > * data_;
    size_t size_;

    Stack();
    ~Stack();
    Stack(const Stack & rhs);
    Stack & operator=(const Stack & rhs);
    Stack(Stack && rhs) noexcept;
    Stack & operator=(Stack && rhs) noexcept;

    void push(T & rhs);
    void pop();
    T & top();
    bool empty();
    size_t size();
  };

  template< class T >
  Stack< T >::Stack():
    data_(fake< T >()),
    size_(0)
  {
  }

  template< class T >
  Stack< T >::~Stack()
  {
    clear(data_->next, data_);
    rmfake(data_);
  }

  template< class T >
  Stack< T >::Stack(const Stack & rhs):
    data_(fake< T >()),
    size_(0)
  {
    List< T > * current = rhs->data_->next;
    for (size_t i = 0; i < rhs.size(); ++i) {
      try {
        push(current->data);
      } catch (...) {
        clear(data_->next, data_);
        rmfake(data_);
        throw;
      }
      current = current->next_;
    }
  }

  template< class T >
  Stack< T > & Stack< T >::operator=(const Stack & rhs)
  {
    if (this == &rhs) {
      return *this;
    }
    List< T > * lhs_fake_node = fake< T >();
    List< T > * lhs_current = lhs_fake_node;
    List< T > * rhs_current = rhs->data_->next;
    for (size_t i = 0; i < rhs.size(); ++i) {
      try {
        lhs_current = insert_after(lhs_current, rhs_current->data);
        rhs_current = rhs_current->next_;
      } catch (...) {
        clear(lhs_fake_node->next, lhs_fake_node);
        rmfake(lhs_fake_node);
        throw;
      }
    }
    clear(data_->next, data_);
    rmfake(data_);
    data_ = lhs_fake_node;
    size_ = rhs.size();
    return *this;
  }

  template< class T >
  Stack< T >::Stack(Stack && rhs) noexcept
  {
    data_ = rhs.data_;
    size_ = rhs.size();
    rhs.data_ = nullptr;
  }

  template< class T >
  Stack<T> & Stack<T>::operator=(Stack && rhs) noexcept
  {
    clear(data_->next, data_);
    rmfake(data_);
    data_ = rhs.data_;
    size_ = rhs.size();
    rhs.data_ = nullptr;
    return *this;
  }
}

#endif
