#ifndef STACK_HPP
#define STACK_HPP

#include "../S1/BiList.hpp"
#include <stdexcept>

namespace zinoviev
{
  template <typename T>
  class Stack
  {
    BiList<T> data_;

  public:
    Stack() = default;

    void push(const T& value)
    {
      data_.push_front(value);
    }

    void push(T&& value)
    {
      data_.push_front(std::move(value));
    }

    void pop()
    {
      data_.pop_front();
    }

    const T& top() const
    {
      if (empty())
        throw std::logic_error("Stack is empty");
      return *data_.cbegin();
    }

    bool empty() const noexcept
    {
      return data_.size() == 0;
    }

    size_t size() const noexcept
    {
      return data_.size();
    }
  };
}

#endif
