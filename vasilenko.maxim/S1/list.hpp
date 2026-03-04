#ifndef VASILENKO_MAXIM_LIST_HPP
#define VASILENKO_MAXIM_LIST_HPP

namespace vasilenko_maxim {

template< class T > class LIter;
template< class T > class LCIter;

template< class T >
class List {
public:
  List();
  ~List();

  void pushBack(const T& value);
  void clear();
  bool isEmpty() const;

  T& front();
  T& back();

  LIter< T > begin();
  LIter< T > end();
  LCIter< T > begin() const;
  LCIter< T > end() const;

private:
  struct Node {
    T data_;
    Node *prev_, *next_;
    Node(const T& data, Node* p, Node* n);
  };

  Node *head_, *tail_;

  friend class LIter< T >;
  friend class LCIter< T >;
};

template< class T >
class LIter {
public:
  LIter(typename List< T >::Node* node);

  T& operator*();
  LIter& operator++();
  bool operator==(const LIter& other) const;
  bool operator!=(const LIter& other) const;

private:
  typename List< T >::Node* node_;
};

template< class T >
List< T >::Node::Node(const T& data, Node* p, Node* n) :
  data_(data), prev_(p), next_(n)
{}

template< class T >
List< T >::List() : head_(nullptr), tail_(nullptr)
{}

template< class T >
T& List< T >::front() { return head_->data_; }

template< class T >
T& List< T >::back() { return tail_->data_; }

template< class T >
LIter< T > List< T >::begin() { return LIter< T >(head_); }

template< class T >
LIter< T > List< T >::end() { return LIter< T >(nullptr); }

template< class T >
LIter< T >::LIter(typename List< T >::Node* node) : node_(node)
{}

template< class T >
T& LIter< T >::operator*() { return node_->data_; }

template< class T >
LIter< T >& LIter< T >::operator++() {
  node_ = node_->next_;
  return *this;
}

template< class T >
bool LIter< T >::operator!=(const LIter& other) const {
  return node_ != other.node_;
}

}

#endif
