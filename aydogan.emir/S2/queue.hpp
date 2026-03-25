#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "list.hpp"

namespace aydogan
{
  template< class T >
  class Queue
  {
  public:
    Queue()
  data_(),
  tail_(data_.beforeBegin())
{}

bool empty() const noexcept
{
  return data_.empty();
}
  private:
    List< T > data_;
    Iterator< T > tail_;
  };
}

#endif