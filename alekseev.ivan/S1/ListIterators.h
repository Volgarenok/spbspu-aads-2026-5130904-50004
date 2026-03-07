#ifndef LISTITERATORS_H
#define LISTITERATORS_H

#include "List.h"

template< class T >
struct ListIteratorBase {
  friend class List< T >;

  ListIteratorBase();

  ListIteratorBase(List< T > * node);

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
struct LIter: ListIteratorBase< T > {
  using ListIteratorBase< T >::ListIteratorBase;

  LIter(const ListIteratorBase< T > & base);

  T & operator*() const;
  T * operator->() const;
};

template< class T >
LIter< T >::LIter(const ListIteratorBase< T > & base):
  ListIteratorBase< T >(base)
{
}

template< class T >
T & LIter< T >::operator*() const
{
  return this->node->data;
}

template< class T >
T * LIter< T >::operator->() const
{
  return &(this->node->data);
}

template< class T >
struct LCIter: ListIteratorBase< T > {
  using ListIteratorBase< T >::ListIteratorBase;

  LCIter(const LIter< T > & rhs);
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
  return this->node->data;
}

template< class T >
const T * LCIter< T >::operator->() const
{
  return &(this->node->data);
}

#endif
