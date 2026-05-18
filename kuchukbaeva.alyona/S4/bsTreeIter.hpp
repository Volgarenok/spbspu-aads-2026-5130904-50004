#ifndef BSTREEITER_HPP
#define BSTREEITER_HPP

#include "treeNode.hpp"

namespace kuchukbaeva {

  template< class Key, class Value >
  class BSTConstIterator;

  template< class Key, class Value >
  class BSTIterator {
  public:
    using Node = TreeNode< Key, Value >;

    BSTIterator() noexcept;
    explicit BSTIterator(Node* node) noexcept;

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
    template< class K, class V, class C > friend class BSTree;
    friend class BSTConstIterator< Key, Value >;
  };

  template< class Key, class Value >
  class BSTConstIterator {
  public:
    using Node = TreeNode< Key, Value >;

    BSTConstIterator() noexcept;
    explicit BSTConstIterator(Node* node) noexcept;
    BSTConstIterator(const BSTIterator< Key, Value >& it) noexcept;

    const std::pair< const Key, Value >& operator*() const noexcept;
    const std::pair< const Key, Value >* operator->() const noexcept;

    BSTConstIterator& operator++() noexcept;
    BSTConstIterator operator++(int) noexcept;
    BSTConstIterator& operator--() noexcept;
    BSTConstIterator operator--(int) noexcept;

    bool operator==(const BSTConstIterator& other) const noexcept;
    bool operator!=(const BSTConstIterator& other) const noexcept;

  private:
    Node* node_;

    template< class K, class V, class C > friend class BSTree;
  };
}
