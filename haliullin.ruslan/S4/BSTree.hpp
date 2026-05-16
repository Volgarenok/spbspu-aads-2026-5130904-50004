#ifndef BSTREE_HPP
#define BSTREE_HPP

#include "TreeNode.hpp"
#include <cstddef>
#include <utility>
#include <stdexcept>
#include <functional>

namespace haliullin
{
  template< class Key, class Value, class Compare = std::less< Key > >
  class BSTree
  {
  public:
    using Node = TreeNode< Key, Value >;
    ~BSTree();
    BSTree();

    BSTree(const BSTree& other);
    BSTree(BSTree&& other) noexcept;

    BSTree& operator=(const BSTree& other);
    BSTree& operator=(BSTree&& other) noexcept;

    void swap(BSTree& other) noexcept;

    void push(const Key& k, const Value& v);
    Value& get(const Key& k);
    const Value& get(const Key& k) const;
    Value drop(const Key& k);

    size_t height() const;

    bool isEmpty() const noexcept;
    void clear();

  private:
    Node* root_;
    Compare cmp_;

    Node* findNode(const Key& k) const;
    Node* copyNodes(Node* node, Node* parent);
    size_t heightNode(const Node* node) const;
    void clearNodes(Node* node);

    Node* fallLeft(Node* node) const;
    Node* fallRight(Node* node) const;
  };
}

template< class Key, class Value, class Compare >
haliullin::BSTree< Key, Value, Compare >::~BSTree()
{
  clear();
}

template< class Key, class Value, class Compare >
haliullin::BSTree< Key, Value, Compare >::BSTree():
  root_(&Node::fakeLeaf_)
{}

template< class Key, class Value, class Compare >
haliullin::BSTree< Key, Value, Compare >::BSTree(const BSTree& other):
  root_(copyNodes(other.root_, nullptr)),
  cmp_(other.cmp_)
{}

template< class Key, class Value, class Compare >
haliullin::BSTree< Key, Value, Compare >::BSTree(BSTree&& other) noexcept:
  BSTree()
{
  swap(other);
}

template< class Key, class Value, class Compare >
haliullin::BSTree< Key, Value, Compare >&
haliullin::BSTree< Key, Value, Compare >::operator=(const BSTree& other)
{
  if (this != std::addressof(other))
  {
    BSTree tmp(other);
    swap(tmp);
  }
  return *this;
}

template< class Key, class Value, class Compare >
haliullin::BSTree< Key, Value, Compare >&
haliullin::BSTree< Key, Value, Compare >::operator=(BSTree&& other) noexcept
{
  if (this != std::addressof(other))
  {
    BSTree tmp(std::move(other));
    swap(tmp);
  }
  return *this;
}

template< class Key, class Value, class Compare >
void haliullin::BSTree< Key, Value, Compare >::swap(BSTree& other) noexcept
{
  std::swap(root_, other.root_);
  std::swap(cmp_, other.cmp_);
}

template< class Key, class Value, class Compare >
void haliullin::BSTree< Key, Value, Compare >::push(const Key& k, const Value& v)
{
  if (root_->isFake())
  {
    root_ = new Node(k, v);
    return;
  }

  Node* cur = root_;
  Node* parent = nullptr;

  while(!cur->isFake())
  {
    parent = cur;
    if (cmp_(k, cur->data_.first))
    {
      cur = cur->left_;
    }
    else if (cmp_(cur->data_.first, k))
    {
      cur = cur->right_;
    }
    else
    {
      cur->data_.second = v;
      return;
    }
  }

  Node* newNode = new Node(k, v, parent);
  if (cmp_(k, parent->data_.first))
  {
    parent->left_ = newNode;
  }
  else
  {
    parent->right_ = newNode;
  }
}

template< class Key, class Value, class Compare >
size_t haliullin::BSTree< Key, Value, Compare >::height() const
{
  return heightNode(root_);
}

template< class Key, class Value, class Compare >
bool haliullin::BSTree< Key, Value, Compare >::isEmpty() const noexcept
{
  return root_->isFake();
}

template< class Key, class Value, class Compare >
void haliullin::BSTree< Key, Value, Compare >::clear()
{
  clearNodes(root_);
  root_ = &Node::fakeLeaf_;
}

template< class Key, class Value, class Compare >
haliullin::BSTree< Key, Value, Compare>::Node*
haliullin::BSTree< Key, Value, Compare >::findNode(const Key& k) const
{
  Node* cur = root_;
  while (!cur->isFake())
  {
    if (cmp_(k, cur->data_.first))
    {
      cur = cur->left_;
    }
    else if (cmp_(cur->data_.first, k))
    {
      cur = cur->right_;
    }
    else
    {
      return cur;
    }
  }
  return const_cast< Node* >(&Node::fakeLeaf_);
}

template< class Key, class Value, class Compare >
haliullin::BSTree< Key, Value, Compare >::Node*
haliullin::BSTree< Key, Value, Compare >::copyNodes(Node* node, Node* parent)
{
  if (node->isFake()) return &Node::fakeLeaf_;
  Node* newNode = new Node(node->data_.first, node->data_.second, parent);
  newNode->left_ = copyNodes(node->left_, newNode);
  newNode->right_ = copyNodes(node->right_, newNode);
  return newNode;
}

template< class Key, class Value, class Compare >
size_t haliullin::BSTree< Key, Value, Compare >::heightNode(const Node* node) const
{
  if (node->isFake()) return 0;
  size_t leftH = heightNode(node->left_);
  size_t rightH = heightNode(node->right_);
  return std::max(leftH, rightH) + 1;
}

template< class Key, class Value, class Compare >
void haliullin::BSTree< Key, Value, Compare >::clearNodes(Node* node)
{
  if (node->isFake()) return;
  clearNodes(node->left_);
  clearNodes(node->right_);
  delete node;
}

#endif
