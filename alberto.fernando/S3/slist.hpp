#ifndef SLIST_HPP
#define SLIST_HPP
#include <cstddef>
#include <utility>

namespace alberto {

template< class T >
class SList {
  struct Node {
    T     data;
    Node* next = nullptr;

    template< class... Args >
    explicit Node(Args&&... args):
      data(std::forward< Args >(args)...)
    {}
  };

  Node*  head_ = nullptr;
  size_t size_ = 0;

public:

  SList() = default;

  SList(const SList& o)
  {
    Node** cur = &head_;
    for (const Node* n = o.head_; n; n = n->next) {
      *cur = new Node(n->data);
      cur  = &(*cur)->next;
      ++size_;
    }
  }

  SList(SList&& o) noexcept:
    head_(o.head_),
    size_(o.size_)
  {
    o.head_ = nullptr;
    o.size_ = 0;
  }

  SList& operator=(SList o) noexcept
  {
    swap(o);
    return *this;
  }

  ~SList()
  {
    clear();
  }

  void swap(SList& o) noexcept
  {
    std::swap(head_, o.head_);
    std::swap(size_, o.size_);
  }
