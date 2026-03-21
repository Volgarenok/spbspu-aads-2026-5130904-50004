#ifndef STACK_HPP
#define STACK_HPP

#include "../common/list.hpp"

namespace ivantsova{

  template < class T >
  class Stack {
  private:
    List<T> data_;

  public:
    Stack() = default;
    void push(const T& value) {}
    T pop() {}
    T& top() {}
    const T& top() const {}
    bool empty() const {}
    size_t size() const {}
    void clear() {}
  };
}
#endif
