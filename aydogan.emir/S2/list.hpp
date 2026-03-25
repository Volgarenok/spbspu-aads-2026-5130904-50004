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
T& front()
{
  if (empty())
  {
    throw std::out_of_range("List is empty");
  }
  return head_->data;
}
void push_front(const T& value)
{
  head_ = new Node(value, head_);
}
void pop_front()
{
  if (empty())
  {
    throw std::out_of_range("List is empty");
  }

  Node* tmp = head_;
  head_ = head_->next;
  delete tmp;
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
