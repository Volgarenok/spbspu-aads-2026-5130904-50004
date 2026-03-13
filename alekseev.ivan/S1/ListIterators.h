#ifndef LISTITERATORS_H
#define LISTITERATORS_H

#include "List.h"
#include <memory>

namespace alekseev {
  template< class T >
  struct ListIteratorBase {
    friend class List< T >;

    ListIteratorBase();

    explicit ListIteratorBase(List< T > * node);

    ListIteratorBase< T > & operator++();
    ListIteratorBase< T > operator++(int);

    bool operator==(const ListIteratorBase< T > & other) const;
    bool operator!=(const ListIteratorBase< T > & other) const;

    protected:
      List< T > * node_;
  };

  template< class T >
  ListIteratorBase< T >::ListIteratorBase():
    node_(nullptr)
  {
  }

  template< class T >
  ListIteratorBase< T >::ListIteratorBase(List< T > * node):
    node_(node)
  {
  }

  template< class T >
  ListIteratorBase< T > & ListIteratorBase< T >::operator++()
  {
    node_ = node_->next;
    return *this;
  }

  template< class T >
  ListIteratorBase< T > ListIteratorBase< T >::operator++(int)
  {
    ListIteratorBase< T > tmp = *this;
    ++(*this);
    return tmp;
  }

  template< class T >
  bool ListIteratorBase< T >::operator==(const ListIteratorBase< T > & other) const
  {
    return node_ == other.node_;
  }

  template< class T >
  bool ListIteratorBase< T >::operator!=(const ListIteratorBase< T > & other) const
  {
    return !(*this == other);
  }

  template< class T >
  struct LIter;
  template< class T >
  LIter< T > insert_after(LIter< T > & element, T & value);
  template< class T >
  LIter< T > erase_after(LIter< T > & element);
  template< class T >
  LIter< T > clear(LIter< T > & start, LIter< T > & end);

  template< class T >
  struct LIter: ListIteratorBase< T > {
    using ListIteratorBase< T >::ListIteratorBase;

    LIter(const ListIteratorBase< T > & base);

    T & operator*() const;
    T * operator->() const;

    friend LIter< T > insert_after< T >(LIter< T > & element, T & value);
    friend LIter< T > erase_after< T >(LIter< T > & element);
    friend LIter< T > clear< T >(LIter< T > & start, LIter & end);
  };

  template< class T >
  LIter< T >::LIter(const ListIteratorBase< T > & base):
    ListIteratorBase< T >(base)
  {
  }

  template< class T >
  T & LIter< T >::operator*() const
  {
    return this->node_->data;
  }

  template< class T >
  T * LIter< T >::operator->() const
  {
    return std::addressof(this->node_->data);
  }

  template< class T >
  LIter< T > insert_after(LIter< T > & element, T & value)
  {
    element.node_ = insert_after(element.node_, value);
    return element;
  }

  template< class T >
  LIter< T > erase_after(LIter< T > & element)
  {
    element.node_ = erase_after(element.node_);
    return element;
  }

  template< class T >
  LIter< T > clear(LIter< T > & start, LIter< T > & end)
  {
    start.node_ = clear(start.node_, end.node_);
    return start;
  }

  template< class T >
  struct LCIter: ListIteratorBase< T > {
    using ListIteratorBase< T >::ListIteratorBase;

    explicit LCIter(const LIter< T > & rhs);
    LCIter(const ListIteratorBase< T > & base);

    const T & operator*() const;
    const T * operator->() const;
  };

  template< class T >
  LCIter< T >::LCIter(const LIter< T > & rhs):
    ListIteratorBase< T >(rhs)
  {
  }

  template< class T >
  LCIter< T >::LCIter(const ListIteratorBase< T > & base):
    ListIteratorBase< T >(base)
  {
  }

  template< class T >
  const T & LCIter< T >::operator*() const
  {
    return this->node_->data;
  }

  template< class T >
  const T * LCIter< T >::operator->() const
  {
    return std::addressof(this->node_->data);
  }

  template< class T >
  LIter< T > begin(List< T > * fake_node)
  {
    return LIter< T >(fake_node->next);
  }

  template< class T >
  LIter< T > before_begin(List< T > * fake_node)
  {
    return LIter< T >(fake_node);
  }

  template< class T >
  LIter< T > end(List< T > * fake_node)
  {
    List< T > * current = fake_node;
    while (current->next != fake_node) {
      current = current->next;
    }
    return LIter< T >(current);
  }

  template< class T >
  LCIter< T > begin(const List< T > * fake_node)
  {
    return LCIter< T >(fake_node->next);
  }

  template< class T >
  LCIter< T > before_begin(const List< T > * fake_node)
  {
    return LCIter< T >(fake_node);
  }

  template< class T >
  LCIter< T > end(const List< T > * fake_node)
  {
    List< T > * current = fake_node;
    while (current->next != fake_node) {
      current = current->next;
    }
    return LCIter< T >(current);
  }

  template< class Iter >
  Iter next(Iter it)
  {
    return ++it;
  }
}

#endif
