#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "../S1/list.hpp"

namespace ali
{
  template< typename T >
  class Queue
  {
  private:
    List< T > data_;

  public:
    void push(const T & value)
    {
      data_.push_back(value);
    }

    void drop()
    {
      data_.pop_front();
    }

    T & front()
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
