#ifndef LINK_QUEUE_H
#define LINK_QUEUE_H

#include "exception.h"

template <typename T>
struct node {
    T val;
    node<T>* next;
    node() : val(), next(nullptr) {}
    node(const T& _val) : val(_val), next(nullptr) {}
};

template <typename T>
class link_queue {
public:
    using iterator = node<T>*;

private:
    iterator in;
    iterator out;

public:
    link_queue();
    ~link_queue();

    bool is_empty() const noexcept {
        return out == nullptr;
    }
    bool is_full() const noexcept {
        return false;
    }
    T front() const {
        if (is_empty()) {
            throw out_of_range();
        }
        return out->val;
    }
    void in_queue(const T& val);
    void de_queue() noexcept;
};

template <typename T>
link_queue<T>::link_queue()
    : in(nullptr), out(nullptr) {}

template <typename T>
link_queue<T>::~link_queue() {
    iterator prev = out;
    iterator next = nullptr;

    while (prev != nullptr) {
        next = prev->next;
        delete prev;
        prev = next;
    }
}

template <typename T>
void link_queue<T>::in_queue(const T& val) {
    iterator new_node = new node(val);
    if (!new_node) {
        throw bad_alloc();
    }

    if (is_empty()) {
        in = new_node;
        out = new_node;
    } else {
        in->next = new_node;
        in = new_node;
    }
}

template <typename T>
void link_queue<T>::de_queue() noexcept {
    if (is_empty()) {
        return;
    }

    iterator tmp = out->next;
    delete out;
    out = tmp;
}

#endif //LINK_QUEUE_H