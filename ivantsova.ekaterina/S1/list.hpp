#ifndef LIST_HPP
#define LIST_HPP

namespace ivantsova
{
  template< class T > class List;

  template< class T > class LIter
  {
    friend class List< T >;

  public:
    LIter() noexcept : ptr(nullptr) {}
    LIter(const LIter&) noexcept = default;
    LIter(LIter&&) noexcept = default;
    ~LIter() = default;
    LIter& operator=(const LIter&) noexcept = default;
    LIter& operator=(LIter&&) noexcept = default;

    T& operator*() const noexcept {}

    T* operator->() const noexcept {}

    LIter& operator++() noexcept {}

    LIter& operator--() noexcept {}

    bool operator==(const LIter& other) const noexcept {}

    bool operator!=(const LIter& other) const noexcept {}

  private:
    typename List<T>::Node* ptr;
    explicit LIter(typename List<T>::Node* p) noexcept : ptr(p) {}
  };

  template< class T > class LCIter
  {
    friend class ivantsova::List< T >;

  public:
    LCIter() noexcept : ptr(nullptr) {}
    LCIter(const LCIter&) noexcept = default;
    LCIter(LCIter&&) noexcept = default;
    ~LCIter() = default;
    LCIter& operator=(const LCIter&) noexcept = default;
    LCIter& operator=(LCIter&&) noexcept = default;

    const T& operator*() const noexcept {}

    const T* operator->() const noexcept {}

    LCIter& operator++() noexcept {}

    LCIter& operator--() noexcept {}

    bool operator==(const LCIter& other) const noexcept {}

    bool operator!=(const LCIter& other) const noexcept {}

  private:
    const typename List<T>::Node* ptr;
    explicit LCIter(const typename List<T>::Node* p) noexcept : ptr(p) {}
  };

  template< class T > class List
  {
    friend class LIter< T >;
    friend class LCIter< T >;

  private:
    struct Node 
    {
      T data;
      Node* prev;
      Node* next;

      explicit Node(const T& val, Node* p = nullptr, Node* n = nullptr) :
        data(val), prev(p), next(n) {}

      explicit Node(T&& val, Node* p = nullptr, Node* n = nullptr) :
        data(std::move(val)), prev(p), next(n) {}
    };

    Node* head;
    size_t size_;

  public:
    List() noexcept : head(nullptr), size_(0) {}
    ~List() {}
    List(const List& other) : head(nullptr), size_(0) {}

    List(List&& other) noexcept : head(other.head), size_(other.size_) {}

    List& operator=(const List& other) {}

    List& operator=(List&& other) noexcept {}

    void swap(List& other) noexcept {}

    bool empty() const noexcept {}

    size_t size() const noexcept {}

    T& front() {}

    const T& front() const {}

    T& back() {}

    const T& back() const {}

    void push_front(const T& value) {}

    void push_front(T&& value) {}

    void push_back(const T& value) {}

    void push_back(T&& value) {}

    void pop_front() {}

    void pop_back() {}

    void clear(){}

    LIter<T> begin() const noexcept {}

    LIter<T> end() const noexcept {}

    LCIter<T> cbegin() const noexcept {}

    LCIter<T> cend() const noexcept {}

    LIter<T> insert(LIter<T> pos, const T& value) {}

    LIter<T> insert(LIter<T> pos, T&& value) {}

    LIter<T> erase(LIter<T> pos) {}
  };
}

#endif
