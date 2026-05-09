#ifndef NODE_HPP
#define NODE_HPP
#include <utility>

namespace kuchukbaeva {
  namespace detail {
    template < class T >
    class Node {
    public:
      Node():
        data_(),
        next_(this)
      {
      }

      Node(const T& d, Node* n):
        data_(d),
        next_(n)
      {
      }

      Node(T&& d, Node* n):
        data_(std::move(d)),
        next_(n)
      {
      }

      T data_;
      Node* next_;
    };
  }
}


#endif
