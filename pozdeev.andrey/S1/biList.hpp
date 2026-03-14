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

template<class T>
class LCIter {
  friend class BiList<T>;

public:
  LCIter() noexcept :
    cur_(nullptr),
    tail_(nullptr)
  {
  }

  LCIter(const LIter<T>& other) noexcept :
    cur_(other.cur_),
    tail_(other.tail_)
  {
  }

  LCIter(const LCIter& other) noexcept = default;
  LCIter(LCIter&& other) noexcept = default;
  ~LCIter() = default;

  LCIter& operator=(const LCIter& other) noexcept = default;
  LCIter& operator=(LCIter&& other) noexcept = default;

  bool operator==(const LCIter& other) const noexcept
  {
    return cur_ == other.cur_;
  }

  bool operator!=(const LCIter& other) const noexcept
  {
    return cur_ != other.cur_;
  }

  const T& operator*() const
  {
    return cur_->val_;
  }

  const T* operator->() const
  {
    return &(cur_->val_);
  }

  LCIter& operator++() noexcept
  {
    if (cur_ != nullptr) {
      cur_ = cur_->next_;
    }
    return *this;
  }

  LCIter operator++(int) noexcept
  {
    LCIter tmp(*this);
    if (cur_ != nullptr) {
      cur_ = cur_->next_;
    }
    return tmp;
  }

  LCIter& operator--() noexcept
  {
    if (cur_ == nullptr) {
      cur_ = tail_;
    } else {
      cur_ = cur_->prev_;
    }
    return *this;
  }

  LCIter operator--(int) noexcept
  {
    LCIter tmp(*this);
    if (cur_ == nullptr) {
      cur_ = tail_;
    } else {
      cur_ = cur_->prev_;
    }
    return tmp;
  }

private:
  const Node<T>* cur_;
  const Node<T>* tail_;

  LCIter(const Node<T>* node, const Node<T>* listTail) noexcept :
    cur_(node),
    tail_(listTail)
  {
  }
};

template<class T>
class BiList {
public:
  BiList() noexcept :
    head_(nullptr),
    tail_(nullptr),
    size_(0)
  {
  }

  BiList(const BiList& other) :
    head_(nullptr),
    tail_(nullptr),
    size_(0)
  {
    LCIter<T> it = other.cbegin();
    while (it != other.cend()) {
      pushBack(*it);
      ++it;
    }
  }

  BiList(BiList&& other) noexcept :
    head_(other.head_),
    tail_(other.tail_),
    size_(other.size_)
  {
    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.size_ = 0;
  }

  ~BiList()
  {
    clear();
  }

  BiList& operator=(const BiList& other)
  {
    if (this != &other) {
      clear();
      LCIter<T> it = other.cbegin();
      while (it != other.cend()) {
        pushBack(*it);
        ++it;
      }
    }
    return *this;
  }

  BiList& operator=(BiList&& other) noexcept
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

  bool isEmpty() const noexcept
  {
    if (size_ == 0) {
      return true;
    } else {
      return false;
    }
  }
};

}

#endif
