#ifndef LINK_STACK_H
#define LINK_STACK_H

#include "exception.h"

template <typename T>
struct node {
    T val;
    node<T>* next;
    node() : val(), next(nullptr) {}
    node(const T& _val) : val(_val), next(nullptr) {}
};

template <typename T>
class link_stack {
public:
    using iterator = node<T>*;
    using const_iterator = const node<T>*;
private:
    iterator Top;

public:
    link_stack() : Top(nullptr) {}
    ~link_stack() noexcept {
        iterator prev = Top;
        iterator next = Top;

        while (next != nullptr) {
            next = next->next;
            delete prev;
            prev = next;
        }
    }

    bool isEmpty() const noexcept {
        return Top == nullptr;
    }

    bool isFull() const noexcept {
        return false;
    }

    T top() const {
        if (Top == nullptr) {
            throw out_of_range();
        }
        return Top->val;
    }

    void push(const T& val = T()) {
        iterator new_top = new node<T>(val);
        new_top->next = Top;
        Top = new_top;
    }

    void pop() {
        if (Top == nullptr) {
            throw out_of_range();
        }
        auto temp = Top;
        Top = Top->next;
        delete temp;
    }
};



#endif //LINK_STACK_H