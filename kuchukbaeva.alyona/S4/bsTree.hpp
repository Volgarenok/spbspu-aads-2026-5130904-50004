#ifndef BSTREE_HPP
#define BSTREE_HPP

#include "treeNode.hpp"
#include <cstddef>
#include <utility>
#include <stdexcept>
#include <functional>

namespace kuchukbaeva {

  template< class Key, class Value, class Compare = std::less< Key > >
  class BSTree {
  public:
    using Node = TreeNode< Key, Value >;
    using iterator = BSTIterator< Key, Value >;
    using const_iterator = BSTConstIterator< Key, Value >;

    BSTree();
    ~BSTree();

    BSTree(const BSTree& other);
    BSTree(BSTree&& other) noexcept;

    BSTree& operator=(const BSTree& other);
    BSTree& operator=(BSTree&& other) noexcept;

    void push(const Key& k, const Value& v);
    Value& get(const Key& k);
    const Value& get(const Key& k) const;
    Value drop(const Key& k);

    size_t height(const_iterator it) const;
    size_t height() const;

    const_iterator rotateLeft(const_iterator it);
    const_iterator rotateRight(const_iterator it);
    const_iterator rotateLargeLeft(const_iterator it);
    const_iterator rotateLargeRight(const_iterator it);

    iterator find(const Key& k);
    const_iterator find(const Key& k) const;

    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    const_iterator cbegin() const noexcept;
    iterator end() noexcept;
    const_iterator end() const noexcept;
    const_iterator cend() const noexcept;

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;
    void swap(BSTree& other) noexcept;
    void clear();

  private:
    Node* root_;
    size_t size_;
    Compare cmp_;

    Node* findNode(const Key& k) const;
    Node* copyNodes(Node* node, Node* parent);
    size_t heightNode(const Node* node) const;
    void removeNode(Node* node);
    void clearNodes(Node* node);
  };
}
