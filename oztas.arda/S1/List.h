#ifndef LIST_H
#define LIST_H

#include <cstddef>
#include <iterator>
#include <memory>
#include <utility>

namespace oztas
{
  template< class T >
  class List;

  template< class T >
  class LCIter;

  template< class T >
  class LIter
  {
    friend class List< T >;
    friend class LCIter< T >;

  public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    LIter() :
      node_(nullptr)
    {
    }

    reference operator*() const
    {
      return static_cast<Node*>(node_)->value;
    }

    pointer operator->() const
    {
      return std::addressof(static_cast<Node*>(node_)->value);
    }

    LIter& operator++()
    {
      node_ = node_->next;
      return *this;
    }

    LIter operator++(int)
    {
      LIter result(*this);
      ++(*this);
      return result;
    }

    bool operator==(const LIter& other) const
    {
      return node_ == other.node_;
    }

    bool operator!=(const LIter& other) const
    {
      return !(*this == other);
    }

  private:
    struct NodeBase
    {
      NodeBase* next;

      NodeBase() :
        next(nullptr)
      {
      }
    };

    struct Node :
      NodeBase
    {
      template< class U >
      explicit Node(U&& rhs) :
        NodeBase(),
        value(std::forward< U >(rhs))
      {
      }

      T value;
    };

    explicit LIter(NodeBase* node) :
      node_(node)
    {
    }

    NodeBase* node_;
  };

  template< class T >
  class LCIter
  {
    friend class List< T >;

  public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = const T*;
    using reference = const T&;

    LCIter() :
      node_(nullptr)
    {
    }

    LCIter(const LIter< T >& other) :
      node_(other.node_)
    {
    }

    reference operator*() const
    {
      return static_cast<const Node*>(node_)->value;
    }

    pointer operator->() const
    {
      return std::addressof(static_cast<const Node*>(node_)->value);
    }

    LCIter& operator++()
    {
      node_ = node_->next;
      return *this;
    }

    LCIter operator++(int)
    {
      LCIter result(*this);
      ++(*this);
      return result;
    }

    bool operator==(const LCIter& other) const
    {
      return node_ == other.node_;
    }

    bool operator!=(const LCIter& other) const
    {
      return !(*this == other);
    }

  private:
    using NodeBase = typename LIter< T >::NodeBase;
    using Node = typename LIter< T >::Node;

    explicit LCIter(const NodeBase* node) :
      node_(node)
    {
    }

    const NodeBase* node_;
  };

  template< class T >
  class List
  {
  public:
    using value_type = T;
    using iterator = LIter< T >;
    using const_iterator = LCIter< T >;

    List() :
      fake_(),
      tail_(&fake_),
      size_(0)
    {
    }

    List(const List& other) :
      fake_(),
      tail_(&fake_),
      size_(0)
    {
      try {
        for (const_iterator it = other.begin(); it != other.end(); ++it) {
          pushBack(*it);
        }
      }
      catch (...) {
        clear();
        throw;
      }
    }

    List(List&& other) noexcept :
      fake_(),
      tail_(&fake_),
      size_(0)
    {
      moveFrom(std::move(other));
    }

    ~List()
    {
      clear();
    }

    List& operator=(const List& other)
    {
      if (this != std::addressof(other)) {
        List temp(other);
        swap(temp);
      }
      return *this;
    }

    List& operator=(List&& other) noexcept
    {
      if (this != std::addressof(other)) {
        clear();
        moveFrom(std::move(other));
      }
      return *this;
    }

    iterator beforeBegin() noexcept
    {
      return iterator(&fake_);
    }

    const_iterator beforeBegin() const noexcept
    {
      return const_iterator(&fake_);
    }

    const_iterator cbeforeBegin() const noexcept
    {
      return const_iterator(&fake_);
    }

    iterator begin() noexcept
    {
      return iterator(fake_.next);
    }

    const_iterator begin() const noexcept
    {
      return const_iterator(fake_.next);
    }

    const_iterator cbegin() const noexcept
    {
      return const_iterator(fake_.next);
    }

    iterator end() noexcept
    {
      return iterator(nullptr);
    }

    const_iterator end() const noexcept
    {
      return const_iterator(nullptr);
    }

    const_iterator cend() const noexcept
    {
      return const_iterator(nullptr);
    }

    bool empty() const noexcept
    {
      return size_ == 0;
    }

    std::size_t size() const noexcept
    {
      return size_;
    }

    T& front()
    {
      return static_cast<Node*>(fake_.next)->value;
    }

    const T& front() const
    {
      return static_cast<const Node*>(fake_.next)->value;
    }

    T& back()
    {
      return static_cast<Node*>(tail_)->value;
    }

    const T& back() const
    {
      return static_cast<const Node*>(tail_)->value;
    }

    void pushFront(const T& value)
    {
      insertAfter(beforeBegin(), value);
    }

    void pushFront(T&& value)
    {
      insertAfter(beforeBegin(), std::move(value));
    }

    void pushBack(const T& value)
    {
      insertAfter(iterator(tail_), value);
    }

    void pushBack(T&& value)
    {
      insertAfter(iterator(tail_), std::move(value));
    }

    void popFront() noexcept
    {
      eraseAfter(beforeBegin());
    }

    void popBack() noexcept
    {
      if (empty()) {
        return;
      }

      iterator prev = beforeBegin();
      while (prev.node_->next != tail_) {
        ++prev;
      }

      eraseAfter(prev);
    }

    template< class U >
    iterator insertAfter(iterator pos, U&& value)
    {
      Node* node = new Node(std::forward< U >(value));
      node->next = pos.node_->next;
      pos.node_->next = node;

      if (tail_ == pos.node_) {
        tail_ = node;
      }

      ++size_;
      return iterator(node);
    }

    iterator eraseAfter(iterator pos) noexcept
    {
      NodeBase* victim = pos.node_->next;
      if (victim == nullptr) {
        return end();
      }

      pos.node_->next = victim->next;
      if (tail_ == victim) {
        tail_ = pos.node_;
      }

      iterator result(victim->next);
      delete static_cast<Node*>(victim);
      --size_;
      return result;
    }

    void clear() noexcept
    {
      NodeBase* current = fake_.next;
      while (current != nullptr) {
        NodeBase* next = current->next;
        delete static_cast<Node*>(current);
        current = next;
      }

      fake_.next = nullptr;
      tail_ = &fake_;
      size_ = 0;
    }

    void swap(List& other) noexcept
    {
      List temp(std::move(other));
      other.moveFrom(std::move(*this));
      moveFrom(std::move(temp));
    }

  private:
    using NodeBase = typename LIter< T >::NodeBase;
    using Node = typename LIter< T >::Node;

    void moveFrom(List&& other) noexcept
    {
      fake_.next = other.fake_.next;
      size_ = other.size_;

      if (other.tail_ == &other.fake_) {
        tail_ = &fake_;
      }
      else {
        tail_ = other.tail_;
      }

      other.fake_.next = nullptr;
      other.tail_ = &other.fake_;
      other.size_ = 0;
    }

    NodeBase fake_;
    NodeBase* tail_;
    std::size_t size_;
  };
}

#endif
