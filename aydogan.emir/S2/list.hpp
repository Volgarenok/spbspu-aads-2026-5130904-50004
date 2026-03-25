#ifndef LIST_HPP
#define LIST_HPP

#include <stdexcept>
#include <utility>

namespace aydogan
{
  template< class T >
  class List;

  template< class T >
  class Iterator
  {
    friend class List< T >;

  public:
    Iterator():
      node_(nullptr)
    {}

    T& operator*() const
    {
      return node_->data;
    }

    Iterator& operator++()
    {
      node_ = node_->next;
      return *this;
    }

    bool operator==(const Iterator& other) const
    {
      return node_ == other.node_;
    }

    bool operator!=(const Iterator& other) const
    {
      return node_ != other.node_;
    }

  private:
    struct Node
    {
      T data;
      Node* next;

      Node(const T& value, Node* nextNode):
        data(value),
        next(nextNode)
      {}
    };

    explicit Iterator(Node* node):
      node_(node)
    {}

    Node* node_;
  };

  template< class T >
  class List
  {
    using Node = typename Iterator< T >::Node;

  public:
    List():
      fake_(new Node(T{}, nullptr))
    {}

    ~List()
    {
      clear();
      delete fake_;
    }

    bool empty() const noexcept
    {
      return fake_->next == nullptr;
    }

    Iterator< T > beforeBegin() noexcept
    {
      return Iterator< T >(fake_);
    }

    Iterator< T > begin() noexcept
    {
      return Iterator< T >(fake_->next);
    }

    Iterator< T > end() noexcept
    {
      return Iterator< T >(nullptr);
    }

    T& front()
    {
      if (empty())
      {
        throw std::out_of_range("List is empty");
      }
      return fake_->next->data;
    }

    void push_front(const T& value)
    {
      insertAfter(beforeBegin(), value);
    }

    void pop_front()
    {
      if (empty())
      {
        throw std::out_of_range("List is empty");
      }
      eraseAfter(beforeBegin());
    }

    Iterator< T > insertAfter(Iterator< T > pos, const T& value)
    {
      if (pos.node_ == nullptr)
      {
        throw std::out_of_range("Invalid iterator");
      }

      Node* newNode = new Node(value, pos.node_->next);
      pos.node_->next = newNode;

      return Iterator< T >(newNode);
    }

    Iterator< T > eraseAfter(Iterator< T > pos)
    {
      if (pos.node_ == nullptr || pos.node_->next == nullptr)
      {
        throw std::out_of_range("Nothing to erase");
      }

      Node* toDelete = pos.node_->next;
      pos.node_->next = toDelete->next;
      delete toDelete;

      return Iterator< T >(pos.node_->next);
    }

    void clear() noexcept
    {
      while (!empty())
      {
        Node* tmp = fake_->next;
        fake_->next = tmp->next;
        delete tmp;
      }
    }

  private:
    Node* fake_;
  };
}

#endif
