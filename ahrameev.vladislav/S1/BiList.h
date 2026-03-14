#ifndef BILIST_H
#define BILIST_H

namespace akhrameev
{

template<class T>
class BiList
{

public:

  struct Node
  {
    T val;
    Node* next;
    Node* prev;

    Node(const T& value)
    {
      val = value;
      next = nullptr;
      prev = nullptr;
    }
  };

  Node* head;
  Node* tail;

  BiList()
  {
    head = nullptr;
    tail = nullptr;
  }

  bool empty() const
  {
    return head == nullptr;
  }

  void push_back(const T& value)
  {
    Node* node = new Node(value);

    if (empty())
    {
      head = node;
      tail = node;
    }
    else
    {
      tail->next = node;
      node->prev = tail;
      tail = node;
    }
  }

  void pop_front()
  {
    if (empty())
      return;

    Node* tmp = head;

    head = head->next;

    if (head != nullptr)
      head->prev = nullptr;
    else
      tail = nullptr;

    delete tmp;
  }

  T& front()
  {
    return head->val;
  }

};

}

#endif
