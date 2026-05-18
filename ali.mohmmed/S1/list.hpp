#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>

namespace ali
{
  template< class T >
  class List
  {
  private:
    struct Node
    {
      T data;
      Node * next;

      Node(const T & value):
        data(value),
        next(nullptr)
      {}
    };

    Node * head_;

    void copy_from(const List & other)
    {
      Node * current = other.head_;

      while (current)
      {
        push_back(current->data);
        current = current->next;
      }
    }

  public:
    class Iterator
    {
    private:
      Node * node_;

    public:
      Iterator(Node * node):
        node_(node)
      {}

      T & operator*()
      {
        return node_->data;
      }

      Iterator & operator++()
      {
        node_ = node_->next;
        return *this;
      }

      bool operator!=(const Iterator & other) const
      {
        return node_ != other.node_;
      }
    };

    List():
      head_(nullptr)
    {}

    List(const List & other):
      head_(nullptr)
    {
      copy_from(other);
    }

    List & operator=(const List & other)
    {
      if (this != &other)
      {
        clear();
        copy_from(other);
      }

      return *this;
    }

    ~List()
    {
      clear();
    }

    void push_front(const T & value)
    {
      Node * newNode = new Node(value);
      newNode->next = head_;
      head_ = newNode;
    }

    void push_back(const T & value)
    {
      Node * newNode = new Node(value);

      if (!head_)
      {
        head_ = newNode;
        return;
      }

      Node * current = head_;

      while (current->next)
      {
        current = current->next;
      }

      current->next = newNode;
    }

    T & front()
    {
      return head_->data;
    }

    void pop_front()
    {
      if (!head_)
      {
        return;
      }

      Node * temp = head_;
      head_ = head_->next;
      delete temp;
    }

    Iterator begin()
    {
      return Iterator(head_);
    }

    Iterator end()
    {
      return Iterator(nullptr);
    }

    std::size_t size() const
    {
      std::size_t count = 0;

      Node * current = head_;

      while (current)
      {
        ++count;
        current = current->next;
      }

      return count;
    }

    bool empty() const
    {
      return head_ == nullptr;
    }

    void clear()
    {
      while (head_)
      {
        Node * temp = head_;
        head_ = head_->next;
        delete temp;
      }
    }
  };
}

#endif
