#ifndef BSTREE_HPP
#define BSTREE_HPP

#include <functional>
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

#endif
