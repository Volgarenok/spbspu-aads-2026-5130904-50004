#ifndef STACK_HPP
#define STACK_HPP

#include "../S1/list.hpp"
namespace ali
{
  template< typename T >
  class Stack
  {
  private:
    List< T > data_;

  public:
    void push(const T & value)
    {
      data_.push_front(value);
    }

    void drop()
    {
      data_.pop_front();
    }

    T & top()
    {
      return data_.front();
    }

    bool empty() const
    {
      return data_.empty();
    }
  };
}

#endif
