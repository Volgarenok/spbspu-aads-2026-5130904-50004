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

  template< class T >
  class LCIter
  {
  public:
    friend class BiList< T >;

    LCIter() noexcept :
      node_(nullptr),
      head_(nullptr)
    {}

    LCIter(const LIter< T >& other) noexcept :
      node_(other.node_),
      head_(other.head_)
    {}

    const T& operator*() const
    {
      return node_->val;
    }

    const T* operator->() const
    {
      return &(node_->val);
    }

    LCIter& operator++() noexcept
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

    LCIter operator++(int) noexcept
    {
      LCIter tmp(*this);
      ++(*this);
      return tmp;
    }

    LCIter& operator--() noexcept
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

    bool operator==(const LCIter& other) const noexcept
    {
      return node_ == other.node_;
    }

    bool operator!=(const LCIter& other) const noexcept
    {
      return !(*this == other);
    }

  private:
    const Node< T >* node_;
    const Node< T >* head_;

    LCIter(const Node< T >* node, const Node< T >* head) noexcept :
      node_(node),
      head_(head)
    {}
  };

template< class T >
  class BiList
  {
  public:
    BiList() noexcept :
      head_(nullptr),
      size_(0)
    {}

    BiList(const BiList& other) :
      head_(nullptr),
      size_(0)
    {
      if (!other.isEmpty())
      {
        Node< T >* curr = other.head_;
        do
        {
          pushBack(curr->val);
          curr = curr->next;
        }
        while (curr != other.head_);
      }
    }

    BiList(BiList&& other) noexcept :
      head_(other.head_),
      size_(other.size_)
    {
      other.head_ = nullptr;
      other.size_ = 0;
    }

    ~BiList()
    {
      clear();
    }

    BiList& operator=(const BiList& other)
    {
      if (this != &other)
      {
        BiList tmp(other);
        swap(tmp);
      }
      return *this;
    }

    BiList& operator=(BiList&& other) noexcept
    {
      if (this != &other)
      {
        clear();
        head_ = other.head_;
        size_ = other.size_;
        other.head_ = nullptr;
        other.size_ = 0;
      }
      return *this;
    }

    void swap(BiList& other) noexcept
    {
      std::swap(head_, other.head_);
      std::swap(size_, other.size_);
    }

    bool isEmpty() const noexcept
    {
      return size_ == 0;
    }

    size_t getSize() const noexcept
    {
      return size_;
    }

    T& front()
    {
      if (isEmpty())
      {
        throw std::out_of_range("List is empty");
      }
      return head_->val;
    }

    const T& front() const
    {
      if (isEmpty())
      {
        throw std::out_of_range("List is empty");
      }
      return head_->val;
    }

    T& back()
    {
      if (isEmpty())
      {
        throw std::out_of_range("List is empty");
      }
      return head_->prev->val;
    }

    const T& back() const
    {
      if (isEmpty())
      {
        throw std::out_of_range("List is empty");
      }
      return head_->prev->val;
    }

    LIter< T > begin() noexcept
    {
      return LIter< T >(head_, head_);
    }

    LIter< T > end() noexcept
    {
      return LIter< T >(nullptr, head_);
    }

    LCIter< T > cbegin() const noexcept
    {
      return LCIter< T >(head_, head_);
    }

    LCIter< T > cend() const noexcept
    {
      return LCIter< T >(nullptr, head_);
    }

    void pushFront(const T& value)
    {
      Node< T >* newNode = new Node< T >(value);
      if (isEmpty())
      {
        head_ = newNode;
        head_->next = head_;
        head_->prev = head_;
      }
      else
      {
        Node< T >* tail = head_->prev;
        newNode->next = head_;
        newNode->prev = tail;
        tail->next = newNode;
        head_->prev = newNode;
        head_ = newNode;
      }
      ++size_;
    }

    void pushBack(const T& value)
    {
      pushFront(value);
      head_ = head_->next;
    }

    void popFront()
    {
      if (isEmpty())
      {
        return;
      }
      if (size_ == 1)
      {
        delete head_;
        head_ = nullptr;
      }
      else
      {
        Node< T >* oldHead = head_;
        Node< T >* tail = head_->prev;
        head_ = head_->next;
        head_->prev = tail;
        tail->next = head_;
        delete oldHead;
      }
      --size_;
    }

    void popBack()
    {
      if (isEmpty())
      {
        return;
      }
      if (size_ == 1)
      {
        popFront();
      }
      else
      {
        Node< T >* tail = head_->prev;
        tail->prev->next = head_;
        head_->prev = tail->prev;
        delete tail;
        --size_;
      }
    }

    void clear() noexcept
    {
      while (!isEmpty())
      {
        popFront();
      }
    }

    LIter< T > insert(LIter< T > pos, const T& value)
    {
      if (pos == begin())
      {
        pushFront(value);
        return begin();
      }
      if (pos == end())
      {
        pushBack(value);
        LIter< T > res = end();
        return --res;
      }
      Node< T >* curr = pos.node_;
      Node< T >* newNode = new Node< T >(value);
      newNode->prev = curr->prev;
      newNode->next = curr;
      curr->prev->next = newNode;
      curr->prev = newNode;
      ++size_;
      return LIter< T >(newNode, head_);
    }

  private:
    Node< T >* head_;
    size_t size_;
  };
}

#endif
