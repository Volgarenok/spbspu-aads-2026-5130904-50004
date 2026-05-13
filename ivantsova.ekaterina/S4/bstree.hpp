#ifndef BSTREE_HPP
#define BSTREE_HPP

#include <functional>
#include <cstddef>
#include "bstiterators.hpp"
#include "treenode.hpp"

namespace ivantsova {
  template < class Key, class Value, class Compare = std::less< Key > >
  class BSTree {
  public:
    using Node = TreeNode< Key, Value >;
    using iterator = BSTIterator< Key, Value >;
    using const_iterator = BSTConstIterator< Key, Value >;

    BSTree();
    BSTree(const BSTree &other);
    ~BSTree();

    BSTree &operator=(const BSTree &other);

    bool empty() const;
    size_t size() const;
    Value get(const Key &k) const;
    void push(const Key &k, const Value &v);
    Value drop(const Key &k);

    const_iterator find(const Key &k) const;
    iterator find(const Key &k);

    void clear() noexcept;
    void swap(BSTree &other) noexcept;

    iterator begin();
    iterator end() noexcept;
    const_iterator begin() const;
    const_iterator end() const noexcept;
    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;

    const_iterator rotateLeft(const_iterator it);
    const_iterator rotateRight(const_iterator it);
    const_iterator rotateLargeLeft(const_iterator it);
    const_iterator rotateLargeRight(const_iterator it);

    size_t height() const;
    size_t height(const_iterator it) const;

  private:
    Node *fake_root_;
    size_t size_;
    Compare comp_;

    Node *getRealRoot() const;
    Node *clone(Node *src, Node *parent);
    Node *findNode(const Key &k) const;
    Node *findNode(const Key &k);
    Node *fallLeft(Node *node) const;
    void clearImpl(Node *node) noexcept;
    size_t calcHeight(const Node *node) const;
    void removeNode(Node *node);
  };
}

template < class Key, class Value, class Compare >
ivantsova::BSTree< Key, Value, Compare >::BSTree() :
  fake_root_(new Node(Key(), Value())),
  size_(0),
  comp_()
{
  fake_root_->left_ = nullptr;
  fake_root_->right_ = nullptr;
  fake_root_->parent_ = nullptr;
}

template < class Key, class Value, class Compare >
ivantsova::BSTree< Key, Value, Compare >::~BSTree() {
  clear();
  delete fake_root_;
}

template < class Key, class Value, class Compare >
bool ivantsova::BSTree< Key, Value, Compare >::empty() const {
  return size_ == 0;
}

template < class Key, class Value, class Compare >
size_t ivantsova::BSTree< Key, Value, Compare >::size() const {
  return size_;
}

#endif
