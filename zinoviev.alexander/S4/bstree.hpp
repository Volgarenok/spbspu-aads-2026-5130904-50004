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

    Node* next(Node* cur)
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

    const Node* next(const Node* cur)
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
      const Node* current_;
    public:

      CIterator(const Node* cur) :
        current_(cur)
      {
      }

      const std::pair<const Key, Value>& operator*()
      {
        return current_->data_;
      }

      const std::pair<const Key, Value>* operator->()
      {
        return &(current_->data_);
      }

      CIterator& operator++()
      {
        current_ = next(current_);
        return *this;
      }

      CIterator operator++(int)
      {
        CIterator tmp = CIterator(current_);
        current_ = next(current_);
        return tmp;
      }

      bool operator==(const CIterator& other) const
      {
        return this->current_ == other.current_;
      }

      bool operator!=(const CIterator& other) const
      {
        return !(*this == other);
      }
    };

    BSTree(const Compare& com = Compare()) :
      root_(nullptr),
      size_(0),
      compare_(com)
    {
    }

    Iterator begin();
    Iterator end();
    CIterator cbegin();
    CIterator cend();
  };

  template <class Key, class Value, class Compare>
  typename BSTree<Key, Value, Compare>::Iterator BSTree<Key, Value, Compare>::begin()
  {
    return Iterator{ root_ };
  }

  template <class Key, class Value, class Compare>
  typename BSTree<Key, Value, Compare>::Iterator BSTree<Key, Value, Compare>::end()
  {
    return Iterator{ nullptr };
  }

  template <class Key, class Value, class Compare>
  typename BSTree<Key, Value, Compare>::CIterator BSTree<Key, Value, Compare>::cbegin()
  {
    return CIterator{ root_ };
  }

  template <class Key, class Value, class Compare>
  typename BSTree<Key, Value, Compare>::CIterator BSTree<Key, Value, Compare>::cend()
  {
    return Iterator{ nullptr };
  }
}
#endif
