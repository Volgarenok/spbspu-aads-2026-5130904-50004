#ifndef LCITER_H
#define LCITER_H

#include "LIter.h"

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
