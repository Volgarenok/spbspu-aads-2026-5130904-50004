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

  private:
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

#endif
