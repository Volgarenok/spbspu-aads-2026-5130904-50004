#ifndef LIST_HPP
#define LIST_HPP

#include <stdexcept>
#include <utility>
#include <limits>
#include <cstddef>

namespace em {

template <class T>
class List;

template <class T>
class LIter {
  friend class List<T>;

public:
  LIter() noexcept : current_(nullptr) {}
  LIter(const LIter&) noexcept = default;
  LIter(LIter&&) noexcept = default;
  ~LIter() = default;

  LIter& operator=(const LIter&) noexcept = default;
  LIter& operator=(LIter&&) noexcept = default;

  T& operator*() const {
    if (current_ == nullptr) {
      throw std::out_of_range("Dereference null iterator");
    }
    return current_->data;
  }

  T* operator->() const {
    if (current_ == nullptr) {
      throw std::out_of_range("Access null iterator");
    }
    return &(current_->data);
  }

  LIter& operator++() noexcept {
    if (current_ != nullptr) {
      current_ = current_->next;
    }
    return *this;
  }

  bool operator==(const LIter& other) const noexcept {
    return current_ == other.current_;
  }

  bool operator!=(const LIter& other) const noexcept {
    return current_ != other.current_;
  }

private:
  typename List<T>::Node* current_;

  explicit LIter(typename List<T>::Node* p) noexcept : current_(p) {}
};

template <class T>
class LCIter {
  friend class List<T>;

public:
  LCIter() noexcept : current_(nullptr) {}
  LCIter(const LCIter&) noexcept = default;
  LCIter(LCIter&&) noexcept = default;
  ~LCIter() = default;

  LCIter& operator=(const LCIter&) noexcept = default;
  LCIter& operator=(LCIter&&) noexcept = default;

  const T& operator*() const {
    if (current_ == nullptr) {
      throw std::out_of_range("Dereference null const iterator");
    }
    return current_->data;
  }

  const T* operator->() const {
    if (current_ == nullptr) {
      throw std::out_of_range("Access null const iterator");
    }
    return &(current_->data);
  }

  LCIter& operator++() noexcept {
    if (current_ != nullptr) {
      current_ = current_->next;
    }
    return *this;
  }

  bool operator==(const LCIter& other) const noexcept {
    return current_ == other.current_;
  }

  bool operator!=(const LCIter& other) const noexcept {
    return current_ != other.current_;
  }

private:
  const typename List<T>::Node* current_;

  explicit LCIter(const typename List<T>::Node* p) noexcept : current_(p) {}
};

template <class T>
class List {
  friend class LIter<T>;
  friend class LCIter<T>;

protected:
  struct Node {
    T data;
    Node* next;

    explicit Node(const T& val, Node* nxt = nullptr)
      : data(val), next(nxt) {}

    explicit Node(T&& val, Node* nxt = nullptr)
      : data(std::move(val)), next(nxt) {}
  };

  Node* first_;
  Node* last_;
  size_t size_;

public:
  List() : size_(0) {
    first_ = new Node(T());
    last_ = first_;
  }

  ~List() {
    clear();
    delete first_;
  }

  List(const List& other) : size_(0) {
    first_ = new Node(T());
    last_ = first_;
    for (Node* curr = other.first_->next; curr != nullptr; curr = curr->next) {
      push_back(curr->data);
    }
  }

  List(List&& other) noexcept
    : first_(other.first_), last_(other.last_), size_(other.size_) {
    other.first_ = new Node(T());
    other.last_ = other.first_;
    other.size_ = 0;
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
      delete first_;
      first_ = other.first_;
      last_ = other.last_;
      size_ = other.size_;
      other.first_ = new Node(T());
      other.last_ = other.first_;
      other.size_ = 0;
    }
    return *this;
  }

  void swap(List& other) noexcept {
    Node* temp_first = first_;
    Node* temp_last = last_;
    size_t temp_size = size_;

    first_ = other.first_;
    last_ = other.last_;
    size_ = other.size_;

    other.first_ = temp_first;
    other.last_ = temp_last;
    other.size_ = temp_size;
  }

  LIter<T> begin() noexcept {
    return LIter<T>(first_->next);
  }

  LIter<T> end() noexcept {
    return LIter<T>(nullptr);
  }

  LCIter<T> cbegin() const noexcept {
    return LCIter<T>(first_->next);
  }

  LCIter<T> cend() const noexcept {
    return LCIter<T>(nullptr);
  }

  bool empty() const noexcept {
    return size_ == 0;
  }

  size_t size() const noexcept {
    return size_;
  }

  T& front() {
    if (empty()) {
      throw std::out_of_range("List is empty");
    }
    return first_->next->data;
  }

  const T& front() const {
    if (empty()) {
      throw std::out_of_range("List is empty");
    }
    return first_->next->data;
  }

  T& back() {
    if (empty()) {
      throw std::out_of_range("List is empty");
    }
    return last_->data;
  }

  const T& back() const {
    if (empty()) {
      throw std::out_of_range("List is empty");
    }
    return last_->data;
  }

  void push_front(const T& value) {
    Node* new_node = new Node(value, first_->next);
    first_->next = new_node;
    if (last_ == first_) {
      last_ = new_node;
    }
    size_++;
  }

  void push_front(T&& value) {
    Node* new_node = new Node(std::move(value), first_->next);
    first_->next = new_node;
    if (last_ == first_) {
      last_ = new_node;
    }
    size_++;
  }

  void pop_front() {
    if (empty()) {
      return;
    }
    Node* temp = first_->next;
    first_->next = temp->next;
    if (temp == last_) {
      last_ = first_;
    }
    delete temp;
    size_--;
  }

  void push_back(const T& value) {
    Node* new_node = new Node(value);
    last_->next = new_node;
    last_ = new_node;
    size_++;
  }

  void push_back(T&& value) {
    Node* new_node = new Node(std::move(value));
    last_->next = new_node;
    last_ = new_node;
    size_++;
  }

  void pop_back() {
    if (empty()) {
      return;
    }
    if (first_->next == last_) {
      delete last_;
      last_ = first_;
      first_->next = nullptr;
    } else {
      Node* temp = first_;
      while (temp->next != last_) {
        temp = temp->next;
      }
      delete last_;
      last_ = temp;
      last_->next = nullptr;
    }
    size_--;
  }

  LIter<T> insert_after(LIter<T> pos, const T& value) {
    Node* curr = pos.current_;
    if (curr == nullptr) {
      throw std::out_of_range("Cannot insert after nullptr");
    }
    Node* new_node = new Node(value, curr->next);
    curr->next = new_node;
    if (curr == last_) {
      last_ = new_node;
    }
    size_++;
    return LIter<T>(new_node);
  }

  LIter<T> insert_after(LIter<T> pos, T&& value) {
    Node* curr = pos.current_;
    if (curr == nullptr) {
      throw std::out_of_range("Cannot insert after nullptr");
    }
    Node* new_node = new Node(std::move(value), curr->next);
    curr->next = new_node;
    if (curr == last_) {
      last_ = new_node;
    }
    size_++;
    return LIter<T>(new_node);
  }

  LIter<T> erase_after(LIter<T> pos) {
    Node* curr = pos.current_;
    if (curr == nullptr || curr->next == nullptr) {
      throw std::out_of_range("Cannot erase after nullptr");
    }
    Node* temp = curr->next;
    curr->next = temp->next;
    if (temp == last_) {
      last_ = curr;
    }
    delete temp;
    size_--;
    return LIter<T>(curr->next);
  }

  void clear() {
    while (first_->next != nullptr) {
      Node* temp = first_->next;
      first_->next = temp->next;
      delete temp;
    }
    last_ = first_;
    size_ = 0;
  }
};

template <class T>
inline void sum(T& a, const T& b) {
  if (std::numeric_limits<T>::max() - b < a) {
    throw std::overflow_error("Overflow");
  }
  a += b;
}

}

#endif
