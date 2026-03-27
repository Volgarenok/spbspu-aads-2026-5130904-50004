#ifndef LIST_HPP
#define LIST_HPP

#include <stdexcept>
#include <cstddef>

namespace pozdeev {

template< class T >
class List {
public:
    List();
    ~List();

    void pushBack(T value);
    T get(std::size_t index) const;
    std::size_t size() const;
    bool isEmpty() const;

    List(const List &) = delete;
    List &operator=(const List &) = delete;
    List(List &&) = delete;
    List &operator=(List &&) = delete;

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
