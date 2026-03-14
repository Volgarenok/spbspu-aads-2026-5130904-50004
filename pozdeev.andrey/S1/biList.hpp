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

template<class T>
class LIter {
  friend class BiList<T>;

public:
  LIter() noexcept :
    cur_(nullptr),
    tail_(nullptr)
  {
  }

  LIter(const LIter& other) noexcept = default;
  LIter(LIter&& other) noexcept = default;
  ~LIter() = default;

  LIter& operator=(const LIter& other) noexcept = default;
  LIter& operator=(LIter&& other) noexcept = default;

  bool operator==(const LIter& other) const noexcept
  {
    return cur_ == other.cur_;
  }

  bool operator!=(const LIter& other) const noexcept
  {
    return cur_ != other.cur_;
  }

  T& operator*() const
  {
    return cur_->val_;
  }

  T* operator->() const
  {
    return &(cur_->val_);
  }

  LIter& operator++() noexcept
  {
    if (cur_ != nullptr) {
      cur_ = cur_->next_;
    }
    return *this;
  }

  LIter operator++(int) noexcept
  {
    LIter tmp(*this);
    if (cur_ != nullptr) {
      cur_ = cur_->next_;
    }
    return tmp;
  }

  LIter& operator--() noexcept
  {
    if (cur_ == nullptr) {
      cur_ = tail_;
    } else {
      cur_ = cur_->prev_;
    }
    return *this;
  }

  LIter operator--(int) noexcept
  {
    LIter tmp(*this);
    if (cur_ == nullptr) {
      cur_ = tail_;
    } else {
      cur_ = cur_->prev_;
    }
    return tmp;
  }

private:
  Node<T>* cur_;
  Node<T>* tail_;

  LIter(Node<T>* node, Node<T>* listTail) noexcept :
    cur_(node),
    tail_(listTail)
  {
  }
};

}

#endif
