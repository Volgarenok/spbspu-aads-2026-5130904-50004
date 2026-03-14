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
  };

  Node* head;
  Node* tail;

  BiList()
  {
    head = nullptr;
    tail = nullptr;
  }

};

}

#endif
