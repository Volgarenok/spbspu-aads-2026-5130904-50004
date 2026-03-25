#ifndef LIST_HPP
#define LIST_HPP

namespace aydogan
{
  template< class T >
  class List
  {
  public:
    List();

  private:
    struct Node;
    Node* head_;
  };
}

#endif
