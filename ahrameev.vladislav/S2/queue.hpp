#ifndef QUEUE_HPP
#define QUEUE_HPP

namespace akhrameev {
    template <typename T>
    class Queue {
    public:
        Queue() = default;
        Queue(const Queue&) = delete;
        Queue& operator=(const Queue&) = delete;
        ~Queue() {}
        void push(T rhs) {}
        T drop() { return T(); }
        bool empty() const { return true; }
    };
}
#endif