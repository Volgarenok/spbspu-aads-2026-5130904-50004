#ifndef BSTREE_ITERATORS_HPP
#define BSTREE_ITERATORS_HPP

#include "TreeNode.hpp"
#include "tree-traverse.hpp"

namespace haliullin
{
  template< class Key, class Value, class Compare >
  class BSTree;

  template< class Key, class Value >
  class BSTIterator
  {
  public:
    using Node = TreeNode< Key, Value >;

    ~BSTIterator() = default;
    BSTIterator(Node* node = nullptr) noexcept;

    std::pair< const Key, Value >& operator*() const noexcept;
    std::pair< const Key, Value >* operator->() const noexcept;

    BSTIterator& operator++() noexcept;
    BSTIterator operator++(int) noexcept;
    BSTIterator& operator--() noexcept;
    BSTIterator operator--(int) noexcept;

    bool operator==(const BSTIterator& other) const noexcept;
    bool operator!=(const BSTIterator& other) const noexcept;

  private:
    Node* node_;
  };
}

template< class Key, class Value >
haliullin::BSTIterator< Key, Value >::BSTIterator(Node* node) noexcept:
  node_(node ? node : &Node::fakeLeaf_)
{}

template< class Key, class Value >
std::pair< const Key, Value >& haliullin::BSTIterator< Key, Value >::operator*() const noexcept
{
  return node_->data_;
}

template< class Key, class Value >
std::pair< const Key, Value >* haliullin::BSTIterator< Key, Value >::operator->() const noexcept
{
  return &(node_->data_);
}

template< class Key, class Value >
haliullin::BSTIterator< Key, Value >& haliullin::BSTIterator< Key, Value >::operator++() noexcept
{
  Node* n = next(node_);
  node_ = (n ? n : &Node::fakeLeaf_);
  return *this;
}

template< class Key, class Value >
haliullin::BSTIterator< Key, Value > haliullin::BSTIterator< Key, Value >::operator++(int) noexcept
{
  BSTIterator tmp(*this);
  ++(*this);
  return tmp;
}

template< class Key, class Value >
haliullin::BSTIterator< Key, Value >& haliullin::BSTIterator< Key, Value >::operator--() noexcept
{
  Node* n = previous(node_);
  node_ = (n ? n : &Node::fakeLeaf_);
  return *this;
}

template< class Key, class Value >
haliullin::BSTIterator< Key, Value > haliullin::BSTIterator< Key, Value >::operator--(int) noexcept
{
  BSTIterator tmp(*this);
  --(*this);
  return tmp;
}

template< class Key, class Value >
bool haliullin::BSTIterator< Key, Value >::operator==(const BSTIterator& other) const noexcept
{
  return node_ == other.node_;
}

template< class Key, class Value >
bool haliullin::BSTIterator< Key, Value >::operator!=(const BSTIterator& other) const noexcept
{
  return !(*this == other);
}

#endif
