#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>
#include <stdexcept>
#include <utility>

namespace em {

template <class T>
class List;

template <class T>
class LIter {
  friend class List<T>;

private:
  typename List<T>::Elem* ptr;

  explicit LIter(typename List<T>::Elem* p) noexcept : ptr(p) {}

public:
  LIter() noexcept : ptr(nullptr) {}
  LIter(const LIter&) noexcept = default;
  LIter(LIter&&) noexcept = default;
  ~LIter() = default;

  LIter& operator=(const LIter&) noexcept = default;
  LIter& operator=(LIter&&) noexcept = default;

  T& operator*() const {
    if (ptr == nullptr) {
      throw std::out_of_range("Dereference null iterator");
    }
    return ptr->data;
  }

  T* operator->() const {
    if (ptr == nullptr) {
      throw std::out_of_range("Access null iterator");
    }
    return &(ptr->data);
  }

  LIter& operator++() noexcept {
    if (ptr != nullptr) {
      ptr = ptr->next;
    }
    return *this;
  }

  bool operator==(const LIter& other) const noexcept {
    return ptr == other.ptr;
  }

  bool operator!=(const LIter& other) const noexcept {
    return ptr != other.ptr;
  }
};

template <class T>
class LCIter {
  friend class List<T>;

private:
  const typename List<T>::Elem* ptr;

  explicit LCIter(const typename List<T>::Elem* p) noexcept : ptr(p) {}

public:
  LCIter() noexcept : ptr(nullptr) {}
  LCIter(const LCIter&) noexcept = default;
  LCIter(LCIter&&) noexcept = default;
  ~LCIter() = default;

  LCIter& operator=(const LCIter&) noexcept = default;
  LCIter& operator=(LCIter&&) noexcept = default;

  const T& operator*() const {
    if (ptr == nullptr) {
      throw std::out_of_range("Dereference null const iterator");
    }
    return ptr->data;
  }

  const T* operator->() const {
    if (ptr == nullptr) {
      throw std::out_of_range("Access null const iterator");
    }
    return &(ptr->data);
  }

  LCIter& operator++() noexcept {
    if (ptr != nullptr) {
      ptr = ptr->next;
    }
    return *this;
  }

  bool operator==(const LCIter& other) const noexcept {
    return ptr == other.ptr;
  }

  bool operator!=(const LCIter& other) const noexcept {
    return ptr != other.ptr;
  }
};

template <class T>
class List {
  friend class LIter<T>;
  friend class LCIter<T>;

protected:
  struct Elem {
    T data;
    Elem* next;

    explicit Elem(const T& val, Elem* nxt = nullptr)
      : data(val), next(nxt) {}

    explicit Elem(T&& val, Elem* nxt = nullptr)
      : data(std::move(val)), next(nxt) {}
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

  List(const List& other) : sz(0) {
    head = new Elem(T());
    tail = head;
    for (Elem* curr = other.head->next; curr != nullptr; curr = curr->next) {
      push_back(curr->data);
    }
  }

  List(List&& other) noexcept
    : head(other.head), tail(other.tail), sz(other.sz) {
    other.head = new Elem(T());
    other.tail = other.head;
    other.sz = 0;
  }

  List& operator=(const List& other) {
    if (this != &other) {
      List tmp(other);
      swap(tmp);
    }
    return *this;
  }

  List& operator=(List&& other) noexcept {
    if (this != &other) {
      clear();
      delete head;
      head = other.head;
      tail = other.tail;
      sz = other.sz;
      other.head = new Elem(T());
      other.tail = other.head;
      other.sz = 0;
    }
    return *this;
  }

  void swap(List& other) noexcept {
    Elem* tmp_head = head;
    Elem* tmp_tail = tail;
    size_t tmp_sz = sz;

    head = other.head;
    tail = other.tail;
    sz = other.sz;

    other.head = tmp_head;
    other.tail = tmp_tail;
    other.sz = tmp_sz;
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

  LIter<T> begin() noexcept {
    return LIter<T>(head->next);
  }

  LIter<T> end() noexcept {
    return LIter<T>(nullptr);
  }

  LCIter<T> cbegin() const noexcept {
    return LCIter<T>(head->next);
  }

  LCIter<T> cend() const noexcept {
    return LCIter<T>(nullptr);
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
