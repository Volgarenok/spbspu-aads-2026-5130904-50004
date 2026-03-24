#ifndef QUEUE_H
#define QUEUE_H

#include "../common/List.h"
#include <cstddef>

namespace alekseev {
  template< class T >
  struct Queue {
    List< T > * fake_node_, * tail_;
    size_t size_;

    Queue();
    ~Queue();
    Queue(const Queue & rhs);
    Queue & operator=(const Queue & rhs);
    Queue(Queue && rhs) noexcept;
    Queue & operator=(Queue && rhs) noexcept;

    template< class U >
    void push(U && value);

    void pop();
    T & front();
    T & back();
    bool empty() const;
    size_t size() const;
  };

  template< class T >
  Queue< T >::Queue():
    fake_node_(fake< T >()),
    size_(0)
  {
    tail_ = fake_node_;
  }

  template< class T >
  Queue< T >::~Queue()
  {
    clear(fake_node_->next, fake_node_);
    rmfake(fake_node_);
  }

  template< class T >
  Queue< T >::Queue(const Queue & rhs):
    fake_node_(fake< T >()),
    size_(0)
  {
    tail_ = fake_node_;
    List< T > * rhs_current = rhs.fake_node_;
    for (size_t i = 0; i < rhs.size_; ++i) {
      rhs_current = rhs_current->next;
      tail_ = insert_after(tail_, rhs_current->data);
      ++size_;
    }
  }

  template< class T >
  Queue< T > & Queue< T >::operator=(const Queue & rhs)
  {
    if (this == &rhs) {
      return *this;
    }
    List< T > * lhs_fake_node = fake< T >();
    List< T > * lhs_tail = lhs_fake_node;
    List< T > * rhs_current = rhs.fake_node_;
    for (size_t i = 0; i < rhs.size_; ++i) {
      try {
        rhs_current = rhs_current->next;
        lhs_tail = insert_after(lhs_tail, rhs_current->data);
      } catch (...) {
        clear(lhs_fake_node->next, lhs_fake_node);
        rmfake(lhs_fake_node);
        throw;
      }
    }
    clear(fake_node_->next, fake_node_);
    rmfake(fake_node_);
    fake_node_ = lhs_fake_node;
    tail_ = lhs_tail;
    size_ = rhs.size_;
    return *this;
  }

  template< class T >
  Queue< T >::Queue(Queue && rhs) noexcept:
    fake_node_(rhs.fake_node_),
    tail_(rhs.tail_),
    size_(rhs.size_)
  {
    rhs.fake_node_ = nullptr;
    rhs.tail_ = nullptr;
    rhs.size_ = 0;
  }

  template< class T >
  Queue< T > & Queue< T >::operator=(Queue && rhs) noexcept
  {
    clear(fake_node_->next, fake_node_);
    rmfake(fake_node_);
    fake_node_ = rhs.fake_node_;
    rhs.fake_node_ = nullptr;
    tail_ = rhs.tail_;
    rhs.tail_ = nullptr;
    rhs.size_ = 0;
    return *this;
  }
}

#endif
