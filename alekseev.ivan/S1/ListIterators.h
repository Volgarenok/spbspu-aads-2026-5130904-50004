#ifndef LISTITERATORS_H
#define LISTITERATORS_H

#include "List.h"
#include <memory>

namespace alekseev {
  template< class T, class Derived >
  struct ListIteratorBase {
    friend class List< T >;

    ListIteratorBase();

    explicit ListIteratorBase(List< T > * node);

    Derived & operator++();
    Derived operator++(int);

    bool operator==(const ListIteratorBase< T, Derived > & other) const;
    bool operator!=(const ListIteratorBase< T, Derived > & other) const;

    protected:
      List< T > * node_;
  };

  template< class T, class Derived >
  ListIteratorBase< T, Derived >::ListIteratorBase():
    node_(nullptr)
  {
  }

  template< class T, class Derived >
  ListIteratorBase< T, Derived >::ListIteratorBase(List< T > * node):
    node_(node)
  {
  }

  template< class T, class Derived >
  Derived & ListIteratorBase< T, Derived >::operator++()
  {
    node_ = node_->next;
    return static_cast<Derived &>(*this);
  }

  template< class T, class Derived >
  Derived ListIteratorBase< T, Derived >::operator++(int)
  {
    ListIteratorBase< T, Derived > tmp = *this;
    ++(*this);
    return static_cast<Derived &>(tmp);
  }

  template< class T, class Derived >
  bool ListIteratorBase< T, Derived >::operator==(const ListIteratorBase< T, Derived > & other) const
  {
    return node_ == other.node_;
  }

  template< class T, class Derived >
  bool ListIteratorBase< T, Derived >::operator!=(const ListIteratorBase< T, Derived > & other) const
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
  struct LIter: ListIteratorBase< T, LIter< T > > {
    using ListIteratorBase< T, LIter< T > >::ListIteratorBase;

    LIter(const ListIteratorBase< T, LIter< T > > & base);

    T & operator*() const;
    T * operator->() const;

    friend LIter< T > insert_after< T >(LIter< T > & element, T & value);
    friend LIter< T > erase_after< T >(LIter< T > & element);
    friend LIter< T > clear< T >(LIter< T > & start, LIter & end);
  };

  template< class T >
  LIter< T >::LIter(const ListIteratorBase< T, LIter< T > > & base):
    ListIteratorBase< T, LIter< T > >(base)
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
  struct LCIter: ListIteratorBase< T, LCIter< T > > {
    using ListIteratorBase< T, LCIter< T > >::ListIteratorBase;

    explicit LCIter(const LIter< T > & rhs);
    LCIter(const ListIteratorBase< T, LCIter< T > > & base);

    const T & operator*() const;
    const T * operator->() const;
  };

  template< class T >
  LCIter< T >::LCIter(const LIter< T > & rhs):
    ListIteratorBase< T, LCIter< T > >(rhs)
  {
  }

  template< class T >
  LCIter< T >::LCIter(const ListIteratorBase< T, LCIter< T > > & base):
    ListIteratorBase< T, LCIter< T > >(base)
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
    return LIter< T >(fake_node);
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
    return LCIter< T >(fake_node);
  }

  template< class Iter >
  Iter next(Iter it)
  {
    return ++it;
  }
}

#endif
