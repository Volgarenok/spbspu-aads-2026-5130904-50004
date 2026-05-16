#ifndef BSTREE_HPP
#define BSTREE_HPP

#include "TreeNode.hpp"
#include <utility>
#include <functional>

namespace haliullin
{
  template< class Key, class Value, class Compare >
  class BSTree
  {
  public:
    ~BSTree();
    BSTree();

    BSTree(const BSTree& other);
    BSTree(BSTree&& other) noexcept;

    operator=(const BStree& other);
    operator=(BSTree&& other) noexcept;

    void swap(BSTree& other) noexcept;

    void push(const Key& k, const Value& v);
    Value& get(const Key& k);
    const Value& get(const Key& k) const;
    Value drop(const Key& k);

    size_t height() const;

    bool isEmpty() const noexcept;
    void clear() noexcept;

  private:
    Node* root_;
    Compare cmp_;

    Node* fallLeft(Node* node) const;
    Node* fallRight(Node* node) const;
    size_t heightNode(const Node* node) const;
  };
}

#endif
