#ifndef BSTREE_HPP
#define BSTREE_HPP

#include "TreeNode.hpp"
#include <utility>
#include <stdexcept>

namespace haliullin
{
  template< class Key, class Value, class Compare >
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

    Node* copyNodes(Node* node, Node* parent);
    void clearNodes(Node* node);
    Node* fallLeft(Node* node) const;
    Node* fallRight(Node* node) const;
    size_t heightNode(const Node* node) const;
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
void haliullin::BSTree< Key, Value, Compare >::clear()
{
  clearNodes(root_);
  root_ = &Node::fakeLeaf_;
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
void haliullin::BSTree< Key, Value, Compare >::clearNodes(Node* node)
{
  if (node->isFake()) return;
  clearNodes(node->left_);
  clearNodes(node->right_);
  delete node;
}

#endif
