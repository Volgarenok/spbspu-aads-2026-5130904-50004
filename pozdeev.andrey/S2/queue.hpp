#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <stdexcept>
#include <cstddef>

namespace pozdeev {

template< class T >
class Queue {
public:
    Queue();
    ~Queue();

    void push(T value);
    T drop();
    T front() const;
    bool isEmpty() const;
    std::size_t size() const;

    Queue(const Queue &) = delete;
    Queue &operator=(const Queue &) = delete;
    Queue(Queue &&) = delete;
    Queue &operator=(Queue &&) = delete;

private:
    struct Node {
        T data_;
        Node *next_;

        Node(T data, Node *next);
    };

    Node *head_;
    Node *tail_;
    std::size_t size_;
};

}

#endif
