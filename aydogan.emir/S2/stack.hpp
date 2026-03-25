#ifndef STACK_HPP
#define STACK_HPP

#include "list.hpp"

namespace aydogan
{
  template< class T >
  class Stack
  {
  public:
    Stack() = default;
    bool empty() const noexcept
{
  return data_.empty();
}

void push(const T& rhs)
{
    data_.push_front(rhs);
}
void push(T&& rhs)
{
    data_.push_front(std::move(rhs));
}
  private:
    List< T > data_;
  };
}

#endif
