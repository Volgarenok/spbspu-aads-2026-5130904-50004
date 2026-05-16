#ifndef BSTREE_HPP
#define BSTREE_HPP

#include <functional>

namespace zinoviev
{
  template <class Key, class Value, class Compare = std::less<Key>>
  class BSTree
  {
    struct Node
    {
      std::pair<const Key, Value> data_;

      Node* left_;
      Node* right_;
      Node* parent_;

      Node(const Key& k, const Value& val, Node* p) :
        data_(k, val),
        left_(nullptr),
        right_(nullptr),
        parent_(p)
      {
      }
    };

    Node* root_;
    size_t size_;
    Compare compare_;

    Node* next(Node* cur);

  public:
    class Iterator
    {
      Node* current_;
    public:

      Iterator(Node* cur) :
        current_(cur)
      {
      }

      std::pair<const Key, Value>& operator*()
      {
        return current_->data_;
      }

      std::pair<const Key, Value>* operator->()
      {
        return &(current_->data_);
      }

      Iterator& operator++()
      {
        current_ = next(current_);
        return *this;
      }

      Iterator operator++(int)
      {
        Iterator tmp = Iterator(current_);
        current_ = next(current_);
        return tmp;
      }

      bool operator==(const Iterator& other) const
      {
        return this->current_ == other.current_;
      }

      bool operator!=(const Iterator& other) const
      {
        return !(*this == other);
      }
    };

    class CIterator
    {
    };

    BSTree(const Compare& com = Compare()) :
      root_(nullptr),
      size_(0),
      compare_(com)
    {
    }
  };

  template <class Key, class Value, class Compare>
  typename BSTree<Key, Value, Compare>::Node* BSTree<Key, Value, Compare>::next(Node* cur)
  {
    if (cur->right_)
    {
      cur = cur->right_;

      while (cur->left_)
        cur = cur->left_;
    }
    else
    {
      Node* parent = cur->parent_;

      while (parent && cur != parent->left_)
      {
        cur = parent;
        parent = parent->parent_;
      }

      if (!parent)
        cur = nullptr;
      else
        cur = parent;
    }

    return cur;
  }
}
#endif
