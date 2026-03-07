#ifndef LIST_H
#define LIST_H


template< class T >
struct  List {
  T data;
  List< T > * next;
};

template< class T >
struct LIter {
  friend class List< T >;

};

template< class T >
struct LCIter {
  friend class List< T >;

};

#endif