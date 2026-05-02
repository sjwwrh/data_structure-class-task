#ifndef BI_LINK_LIST_H
#define BI_LINK_LIST_H

#include <cstddef>
#include <iostream>

template <typename T>
struct node {
    T val;
    node* prev;
    node* next;

    node() : next(nullptr), prev(nullptr), val() {}
    node(const T& _val) : next(nullptr), prev(nullptr), val(_val) {}
};

template <typename T>
class bi_link_list {
public:
    using iterator = node<T>*;
    using const_iterator = const node<T>*;

public:
    bi_link_list()
        : head(nullptr), tail(nullptr) {}  

    ~bi_link_list() {
        iterator temp1 = head;
        iterator temp2 = head;
        while (temp1 != nullptr) {
            delete temp2;
            temp1 = temp1->next;
            temp2 = temp1;
        }
    }

    void push_back(const T& val);
    void print() const noexcept;
    void insert(const T& val, int index);
    void remove(int index) noexcept;
    void clear() noexcept;
    void reverse() noexcept;

private:
    iterator head;
    iterator tail;
};

template <typename T>
void bi_link_list<T>::push_back(const T& val) {
    iterator new_pnode = new node(val);

    if (!new_pnode) {
        throw std::bad_alloc();
    } else {
        if (head != nullptr) {
            tail->next = new_pnode;
            new_pnode->prev = tail;
            tail = new_pnode;
        } else {
            head = new_pnode;
            tail = new_pnode;
        }
    }
}

template <typename T>
void bi_link_list<T>::insert(const T& val, int index) {
    if (index < 0) {
        return;
    }
    if (index == 0) {
        iterator new_pnode = new node(val);
        new_pnode->next = head;
        head->prev = new_pnode;
        head = new_pnode;
        return;
    }
    
    iterator tmp1 = head;
    iterator tmp2 = head;
    while (tmp1 != nullptr && index > 1) {
        tmp1 = tmp1->next;
        index--;
    }
    if (tmp1 == nullptr) {
        return;
    }
    tmp2 = tmp1->next;
    tmp1->next = new node(val);
    tmp1->next->next = tmp2;
    tmp1->next->prev = tmp1;
    tmp2->prev = tmp1->next;
}

template <typename T>
void bi_link_list<T>::print() const noexcept {
    const_iterator cur = head;
    while (cur != nullptr) {
        std::cout << cur->val << ' ';
    }
}

template <typename T>
void bi_link_list<T>::clear() noexcept {
    iterator tmp1 = head;
    iterator tmp2 = head;
    while (tmp1 != nullptr) {
        tmp1 = tmp1->next;
        tmp2->next = nullptr;
        delete tmp2;
        tmp2 = tmp1;
    }

    head = nullptr;
    tail = nullptr;
}

template <typename T>
void bi_link_list<T>::reverse() noexcept {
    if (head == nullptr) {
        return;
    }

    iterator prev = nullptr;
    iterator curr = head;
    iterator next = curr->next;
    while (curr != nullptr) {
        next = curr->next;
        curr->next = prev;
        curr->prev = next;
        prev = curr;
        curr = next;
    }
    tail = head;
    head = prev;
}

#endif //BI_LINK_LIST_H