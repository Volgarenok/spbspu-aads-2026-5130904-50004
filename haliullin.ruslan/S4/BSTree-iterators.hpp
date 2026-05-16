#ifndef BSTREE_ITERATORS_HPP
#define BSTREE_ITERATORS_HPP

#include "TreeNode.hpp"

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

    bool operator==() const noexcept;
    bool operator!=() const noexcept;

  private:
    Node* node_;
  };

  template< class Key, class Value >
  class BSTConstIterator
  {

  };
}

#endif
