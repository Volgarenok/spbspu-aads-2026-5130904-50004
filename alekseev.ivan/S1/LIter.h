#ifndef LITER_H
#define LITER_H

#include "List.h"

template< class T >
struct LIter {
  friend class List< T >;

  LIter();

  LIter(List< T > * node);

  LIter< T > & operator++();
  LIter< T > operator++(int);

  T & operator*();
  T & operator->();

  bool operator==(const LIter< T > & other) const;
  bool operator!=(const LIter< T > & other) const;

  private:
    List< T > * node_;
};

template< class T >
LIter< T >::LIter():
  node_(nullptr)
{
}
template< class T >
LIter< T >::LIter(List< T > * node):
  node_(node)
{
}



#endif
