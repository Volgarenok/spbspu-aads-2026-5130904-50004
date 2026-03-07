#ifndef LCITER_H
#define LCITER_H

#include "LIter.h"

template< class T >
struct LCIter: ListIteratorBase< T > {
  using ListIteratorBase< T >::ListIteratorBase;

  LCIter(const LIter< T > & rhs);

  const T & operator*() const;
  const T & operator->() const;
};

template< class T >
LCIter< T >::LCIter(const LIter< T > & rhs):
  ListIteratorBase< T >(rhs)
{
}

template< class T >
const T & LCIter< T >::operator*() const
{
  return this->node->data;
}

template< class T >
const T & LCIter< T >::operator->() const
{
  return &(this->node->data);
}

#endif 