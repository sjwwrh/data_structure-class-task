#ifndef LINK_LIST_H
#define LINK_LIST_H

#include "exception.h"

template <typename T>
class link_list;

template <typename T>
class node {
    friend class link_list<T>;
private:
    T value;
    node* next;
public:
    node(const T& _value = T(), node* _next = nullptr) 
        : value(_value), next(_next) {}
};


//头节点置空,index从1开始
template <typename T>
class link_list {
private:
    node<T>* head;
public:
    using iterator = node<T>*;

    link_list();
    ~link_list();

    void push_back(const T& val);
    bool is_empty() const noexcept;
    int length() const noexcept;
    T get(int i) const;
    int find(const T& val) const noexcept;
    void insert(int i, const T& val);
    void insert(const T arr[], int n);
    void remove(int i);
    void reverse();
    void clear();
    T kth_from_last(int k) const;
};

template <typename T>
link_list<T>::link_list() {
    head = new node<T>();
}

template <typename T>
link_list<T>::~link_list() {
    iterator cur = head;
    iterator next = cur->next;

    while (cur != nullptr) {
        delete cur;
        cur = next;
        next = cur->next;
    }
}

template <typename T>
bool link_list<T>::is_empty() const noexcept {
    return (head->next == nullptr);
}

template <typename T>
int link_list<T>::length() const noexcept {
    int cnt = 0;
    iterator cur = head->next;

    while (cur != nullptr) {
        cur = cur->next;
        cnt++;
    }
    return cnt;
}

template <typename T>
T link_list<T>::get(int i) const {
    if (i < 1) {
        return out_of_range();
    }

    int cnt = i;
    iterator cur = head;

    while (cnt != 0 && cur != nullptr) {
        cur = cur->next;
        cnt--;
    }
    if (cur != nullptr) {
        return cur->value;
    }
    throw out_of_range();
}

template <typename T>
int link_list<T>::find(const T& val) const noexcept {
    int cnt = 1;
    iterator cur = head->next;

    while (cur != nullptr) {
        if (cur->value == val) {
            return cnt;
        }
        cur = cur->next;
        cnt++;
    }
    return 0;
}

template <typename T>
void link_list<T>::insert(int i, const T& val) {
    if (i < 1) {
        return;
    }

    iterator prev = head;
    while (prev != nullptr && i != 1) {
        i--;
        prev = prev->next;
    }
    if (prev == nullptr) {
        return;
    }
    prev->next = new node<T>(val, prev->next);
}

template <typename T>
void link_list<T>::remove(int i) {
    if (i < 1) {
        return;
    }

    iterator prev = head;
    while (prev != nullptr && i != 1) {
        i--;
        prev = prev->next;
    }
    if (prev == nullptr) {
        return;
    }

    iterator node_remove = prev->next;
    if (node_remove == nullptr) {
        return;
    }
    prev->next = node_remove->next;
    delete node_remove;
}

//兄弟协同法
template <typename T>
void link_list<T>::clear() {
    iterator prev = head->next;
    iterator next = nullptr;
    head->next = nullptr;

    while (prev != nullptr) {
        next = prev->next;
        delete prev;
        prev = next;
    }
}

//首席插入法
template <typename T>
void link_list<T>::insert(const T arr[], int n) {
    iterator tmp = nullptr;
    for (int i = 0; i < n; i++) {
        tmp = new node(arr[i], head->next);
        head->next = tmp;
    }
}

template <typename T>
void link_list<T>::reverse() {
    iterator prev = head->next;
    iterator next = nullptr;
    head->next = nullptr;

    while (prev != nullptr) {
        next = prev->next;
        prev->next = head->next;
        head->next = prev;
        prev = next;
    }
}

template <typename T>
T link_list<T>::kth_from_last(int k) const {
    if (k < 1) {
        throw out_of_range();
    }

    iterator prev = head->next;
    iterator next = prev;
    while (k != 0) {
        k--;
        next = next->next;
    }
    if (next == nullptr) {
        throw out_of_range();
    }

    while (next != nullptr) {
        next = next->next;
        prev = prev->next;
    }

    return prev->value;
}

template <typename T>
void link_list<T>::push_back(const T& val) {
    iterator prev = head;
    while (prev->next != nullptr) {
        prev = prev->next;
    }
    iterator new_node = new node(val);
    if (!new_node) {
        throw bad_alloc();
    }
    prev->next = new_node;
}

#endif //LINK_LIST_H