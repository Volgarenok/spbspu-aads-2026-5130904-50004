#ifndef LITER_H
#define LITER_H

template< class T >
struct LIter {
  friend class List< T >;
  List< T > * node;

  LIter():
    node(nullptr)
  {
  }

  LIter< T > & operator++();
  LIter< T > operator++(int);

  T & operator*();
  T & operator->();

  bool operator==(const LIter< T > & other) const;
  bool operator!=(const LIter< T > & other) const;
};

#endif
