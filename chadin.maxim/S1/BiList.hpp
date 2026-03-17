#ifndef CHADIN_BILIST_HPP
#define CHADIN_BILIST_HPP

#include <stdexcept>
#include <utility>

namespace chadin
{
  template< class T >
  struct Node
  {
    T val;
    Node* prev;
    Node* next;

    Node(const T& value) :
      val(value),
      prev(nullptr),
      next(nullptr)
    {}

    Node(T&& value) :
      val(std::move(value)),
      prev(nullptr),
      next(nullptr)
    {}
  };

  template< class T >
  class BiList;

  template< class T >
  class LIter
  {
  public:
    friend class BiList< T >;

    LIter() noexcept :
      node_(nullptr),
      head_(nullptr)
    {}

    T& operator*() const
    {
      return node_->val;
    }

    T* operator->() const
    {
      return &(node_->val);
    }

    LIter& operator++() noexcept
    {
      if (node_)
      {
        node_ = node_->next;
        if (node_ == head_)
        {
          node_ = nullptr;
        }
      }
      return *this;
    }

    LIter operator++(int) noexcept
    {
      LIter tmp(*this);
      ++(*this);
      return tmp;
    }

    LIter& operator--() noexcept
    {
      if (node_ == nullptr)
      {
        if (head_)
        {
          node_ = head_->prev;
        }
      }
      else
      {
        if (node_ == head_)
        {
          node_ = nullptr;
        }
        else
        {
          node_ = node_->prev;
        }
      }
      return *this;
    }

    bool operator==(const LIter& other) const noexcept
    {
      return node_ == other.node_;
    }

    bool operator!=(const LIter& other) const noexcept
    {
      return !(*this == other);
    }

  private:
    Node< T >* node_;
    Node< T >* head_;

    LIter(Node< T >* node, Node< T >* head) noexcept :
      node_(node),
      head_(head)
    {}
  };

}

#endif
