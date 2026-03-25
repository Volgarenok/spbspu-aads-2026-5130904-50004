#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "list.hpp"

namespace aydogan
{
  template< class T >
  class Queue
  {
  public:
    Queue();

  private:
    List< T > data_;
    Iterator< T > tail_;
  };
}

#endif