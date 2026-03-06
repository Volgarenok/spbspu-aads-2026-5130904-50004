#ifndef LIST_H
#define LIST_H

#include <stdexcept>

template <class T>
class Iter {
  friend class List;
};

template <class T>
class List {
  struct Elem {
    T data_;
    Elem* next_;
  };

};

#endif
