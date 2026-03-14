#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>

namespace em {

template <class T>
class List {
protected:
  struct Elem {
    T data;
    Elem* next;

    explicit Elem(const T& val, Elem* nxt = nullptr)
      : data(val), next(nxt) {}
  };

  Elem* head;
  Elem* tail;
  size_t sz;
};

}

#endif
