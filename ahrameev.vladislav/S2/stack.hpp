#ifndef STACK_HPP
#define STACK_HPP

namespace akhrameev {
    template <typename T>
    class Stack {
    public:
        Stack() = default;
        Stack(const Stack&) = delete;
        Stack& operator=(const Stack&) = delete;
        ~Stack() {}
        void push(T rhs) {}
        T drop() { return T(); }
        bool empty() const { return true; }
    };
}
#endif