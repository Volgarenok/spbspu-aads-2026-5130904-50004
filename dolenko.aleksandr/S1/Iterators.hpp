#ifndef LITER_HPP
#define LITER_HPP

#include <cstddef>

template<class T> class BiList;
template<class T> struct Node;

template<class T>
class LIter {
    friend class BiList<T>;
public:
    LIter() noexcept;
    T& operator*() const;
    LIter& operator++();
    LIter operator++(int);
    LIter& operator--();
    LIter operator--(int);
    bool operator==(const LIter& other) const noexcept;
    bool operator!=(const LIter& other) const noexcept;
private:
    Node<T>* node_ = nullptr;
    explicit LIter(Node<T>* n) noexcept;
};



#endif 
