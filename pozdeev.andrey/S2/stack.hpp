#ifndef STACK_HPP
#define STACK_HPP

#include <stdexcept>
#include <cstddef>

namespace pozdeev {

template< class T >
class Stack {
public:
    Stack();
    ~Stack();

    void push(T value);
    T drop();
    T top() const;
    bool isEmpty() const;
    std::size_t size() const;

    Stack(const Stack &) = delete;
    Stack &operator=(const Stack &) = delete;
    Stack(Stack &&) = delete;
    Stack &operator=(Stack &&) = delete;

private:
    struct Node {
        T data_;
        Node *next_;

        Node(T data, Node *next);
    };

    Node *head_;
    std::size_t size_;
};

}
#endif
