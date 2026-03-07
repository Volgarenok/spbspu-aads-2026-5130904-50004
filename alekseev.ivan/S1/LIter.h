#ifndef LITER_H
#define LITER_H

#include "ListIterators.h"

template< class T >
struct LIter: ListIteratorBase< T > {
  using ListIteratorBase< T >::ListIteratorBase;

  LIter(const ListIteratorBase< T > & base);

  T & operator*() const;
  T & operator->() const;
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
T & LIter< T >::operator->() const
{
  return &(this->node->data);
}

#endif
