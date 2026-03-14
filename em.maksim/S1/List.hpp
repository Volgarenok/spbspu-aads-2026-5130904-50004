#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>
#include <stdexcept>

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
