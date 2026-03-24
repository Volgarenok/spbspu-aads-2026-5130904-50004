#ifndef NODE_HPP
#define NODE_HPP

#include <cstddef>

template<class T>
struct Node {
    T data;
    Node* prev = nullptr;
    Node* next = nullptr;
    Node(const T& v) : data(v) {}
};

#endif 
