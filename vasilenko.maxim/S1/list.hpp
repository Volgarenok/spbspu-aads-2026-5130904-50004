#ifndef VASILENKO_MAXIM_LIST_HPP
#define VASILENKO_MAXIM_LIST_HPP

namespace vasilenko_maxim {

template<class T>
class List {
private:
  struct Node {
    T data_;
    Node *prev_, *next_;
    Node(const T& data, Node* p, Node* n) : data_(data), prev_(p), next_(n) {}
  };

  Node *head_, *tail_;

public:
  List() : head_(nullptr), tail_(nullptr) {}

  bool isEmpty() const { return head_ == nullptr; }

  void pushBack(const T& value) {
    Node* newNode = new Node(value, tail_, nullptr);
    if (tail_) tail_->next_ = newNode;
    else head_ = newNode;
    tail_ = newNode;
  }

  void clear() {
    while (head_) {
      Node* temp = head_;
      head_ = head_->next_;
      delete temp;
    }
    tail_ = nullptr;
  }

  ~List() { clear(); }
};

}
#endif
