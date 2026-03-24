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
template<class T>
class LCIter {
    friend class BiList<T>;
public:
    LCIter() noexcept;
    const T& operator*() const;
    LCIter& operator++();
    LCIter operator++(int);
    LCIter& operator--();
    LCIter operator--(int);
    bool operator==(const LCIter& other) const noexcept;
    bool operator!=(const LCIter& other) const noexcept;
private:
    const Node<T>* node_ = nullptr;
    explicit LCIter(const Node<T>* n) noexcept;
};


#endif 
