#ifndef AYDOGAN_LIST_HPP
#define AYDOGAN_LIST_HPP

namespace aydogan
{

template <class T>
class List
{
private:
  struct Node
  {
    T data;
    Node* next;
  };

  Node* fake_;

public:
  List();
  ~List();

  List(const List&);
  List(List&&) noexcept;

  List& operator=(const List&);
  List& operator=(List&&) noexcept;

  bool empty() const noexcept;

};

}

#endif