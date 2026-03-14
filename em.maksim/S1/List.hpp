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

  void push_front(const T& value) {
    Elem* nw = new Elem(value, head->next);
    head->next = nw;
    if (tail == head) {
      tail = nw;
    }
    sz++;
  }

  void push_back(const T& value) {
    Elem* nw = new Elem(value);
    tail->next = nw;
    tail = nw;
    sz++;
  }

  void pop_front() {
    if (sz == 0) {
      return;
    }
    Elem* tmp = head->next;
    head->next = tmp->next;
    if (tmp == tail) {
      tail = head;
    }
    delete tmp;
    sz--;
  }

  void pop_back() {
    if (sz == 0) {
      return;
    }
    if (head->next == tail) {
      delete tail;
      tail = head;
      head->next = nullptr;
    } else {
      Elem* tmp = head;
      while (tmp->next != tail) {
        tmp = tmp->next;
      }
      delete tail;
      tail = tmp;
      tail->next = nullptr;
    }
    sz--;
  }
};

}

#endif
