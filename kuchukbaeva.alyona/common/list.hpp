#ifndef LIST_HPP
#define LIST_HPP
#include "list-iterators.hpp"
#include <stdexcept>

namespace kuchukbaeva {

  template < class T >
  class List {
  public:
    List():
      fake_(new detail::Node< T >())
    {
    }

    List(const List& other):
      List()
    {
      LIter< T > it = beforeBegin();
      for (LCIter< T > otherIt = other.cbegin(); otherIt != other.cend(); ++otherIt) {
        it = insertAfter(it, *otherIt);
      }
    }

    List(List&& other) noexcept:
      fake_(other.fake_)
    {
      other.fake_ = new detail::Node< T >();
    }

    ~List()
    {
      clear();
      delete fake_;
    }

    List& operator=(const List& other)
    {
      if (this != &other) {
        List tmp(other);
        std::swap(fake_, tmp.fake_);
      }
      return *this;
    }

    List& operator=(List&& other) noexcept
    {
      if (this != &other) {
        clear();
        delete fake_;
        fake_ = other.fake_;
        other.fake_ = new detail::Node< T >();
      }
      return *this;
    }

    LIter< T > begin()
    {
      return LIter< T >(fake_->next_);
    }

    LIter< T > end()
    {
      return LIter< T >(fake_);
    }

    LCIter< T > cbegin() const
    {
      return LCIter< T >(fake_->next_);
    }

    LCIter< T > cend() const
    {
      return LCIter< T >(fake_);
    }

    LIter< T > beforeBegin()
    {
      return LIter< T >(fake_);
    }

    T& front() {
      return fake_->next_->data_;
    }

    const T& front() const {
      return fake_->next_->data_;
    }

    void push_front(const T& value)
    {
      insertAfter(beforeBegin(), value);
    }

    void pop_front()
    {
      if (isEmpty()) {
        throw std::out_of_range("List is empty");
      }
      eraseAfter(beforeBegin());
    }

    void clear()
    {
      while (!isEmpty()) {
        pop_front();
      }
    }

    bool isEmpty() const
    {
      return fake_->next_ == fake_;
    }

    LIter< T > insertAfter(LIter< T > pos, const T& value)
    {
      detail::Node< T >* newNode = new detail::Node< T >(std::move(value), pos.node_->next_);
      pos.node_->next_ = newNode;
      return LIter< T >(newNode);
    }

    LIter< T > eraseAfter(LIter< T > pos)
    {
      detail::Node< T >* toDelete = pos.node_->next_;
      pos.node_->next_ = toDelete->next_;
      delete toDelete;
      return LIter< T >(pos.node_->next_);
    }

  private:
    detail::Node< T >* fake_;

  };
}

#endif
