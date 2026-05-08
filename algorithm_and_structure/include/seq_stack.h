#ifndef SEQ_STACK_H
#define SEQ_STACK_H

#include "exception.h"
#include <cstddef>

template <typename T>
class seq_stack {
private:
    T* p;
    int _top;
    int max_size;

private:
    void double_space();

public:
    seq_stack(int size = 100);
    ~seq_stack() {
        delete[] p;
    }

    bool is_empty() const noexcept {
        return _top == -1;
    }
    bool is_full() const noexcept {
        return _top == max_size - 1;
    }
    T top() const noexcept;
    void push(const T& val);
    void pop() noexcept;
};

template <typename T>
seq_stack<T>::seq_stack(int size) 
    : p(nullptr), _top(-1), max_size(size) {
    p = new T[size];
    if (!p) {
        throw illegal_size();
    }
}

template <typename T>
T seq_stack<T>::top() const noexcept {
    if (is_empty()) {
        throw out_of_range();
    }
    return p[_top];
}

template <typename T>
void seq_stack<T>::push(const T& val) {
    if (is_full()) {
        double_space();
    }

    _top++;
    p[_top] = val;
}

template <typename T>
void seq_stack<T>::pop() noexcept {
    if (is_empty()) {
        throw out_of_range();
    }
    _top--;
}

template <typename T>
void seq_stack<T>::double_space() {
    int limit = static_cast<size_t>(-1) / sizeof(T);
    int new_size = limit > 2 * max_size ? 2 * max_size : limit;

    T* new_p = new int[new_size];
    if (!new_p) {
        throw bad_alloc();
    }
    for (int i = 0; i <= _top; i++) {
        new_p[i] = p[i];
    }
    delete[] p;
    p = new_p;
    max_size = new_size;
}

int factorial(int n) {
    seq_stack<int> stack;
    int res = 1;
    while (n != 0) {
        stack.push(n);
        n--;
    }
    while (!stack.is_empty()) {
        int tmp = stack.top();
        res *= tmp;
        stack.pop();
    }
    return res;
}


#endif //SEQ_STACK_H