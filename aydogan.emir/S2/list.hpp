#ifndef LIST_HPP
#define LIST_HPP
#include <stdexcept>
namespace aydogan
{
  template< class T >
  class List
  {
  public:
    List();
  head_(nullptr)
{}
bool empty() const noexcept
{
  return head_ == nullptr;
}
void push_front(const T& value)
{
  head_ = new Node(value, head_);
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
    struct Node;
    Node* head_;
  };
}

#endif
