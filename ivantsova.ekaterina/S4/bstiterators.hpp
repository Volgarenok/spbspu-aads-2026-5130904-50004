#ifndef BSTITERATORS_HPP
#define BSTITERATORS_HPP

#include "treenode.hpp"

namespace ivantsova {
  template < class Key, class Value, class Compare >
  class BSTree;

  template < class Key, class Value >
  class BSTIterator {
  public:
    using Node = TreeNode< Key, Value >;

    explicit BSTIterator(Node *node = nullptr);
    std::pair< const Key, Value > &operator*() const;
    std::pair< const Key, Value > *operator->() const;
    BSTIterator &operator++();
    BSTIterator operator++(int);
    bool operator==(const BSTIterator &other) const;
    bool operator!=(const BSTIterator &other) const;

    template < class K, class V, class C >
    friend class BSTree;

  private:
    Node *node_;
  };
}

#endif
