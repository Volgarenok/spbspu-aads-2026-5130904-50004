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

public:
  List() : sz(0) {
    head = new Elem(T());
    tail = head;
  }

  ~List() {
    clear();
    delete head;
  }

  void clear() {
    while (head->next != nullptr) {
      Elem* tmp = head->next;
      head->next = tmp->next;
      delete tmp;
    }
    tail = head;
    sz = 0;
  }
};

}

#endif
