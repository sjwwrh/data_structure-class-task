#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "exception.h"

//第0位置空, 以第1位为队首
template <typename T>
class priority_queue {
private:
    T* array;
    int len;
    int capacity;

public:
    priority_queue(int size = 10);
    priority_queue(T arr[], int n);
    ~priority_queue() {
        delete[] array;
    }

    bool is_empty() const noexcept {
        return len == 0;
    }
    bool is_full() const noexcept {
        return len == capacity;
    }
    T front() const;
    void in_queue(const T& val);
    void de_queue();


private:
    void double_space();
    void adjust(int hole);
    void build(int r);
};

template <typename T>
priority_queue<T>::priority_queue(int size)
    : array(nullptr), capacity(size), len(0) {
    array = new T[size + 1];
    if (!array) {
        throw illegal_size();
    }
    capacity = size;
}

template <typename T>
priority_queue<T>::priority_queue(T arr[], int n)
    : array(nullptr), capacity(n + 10), len(n) {
    if (n < 1) {
        throw illegal_size();
    }

    array = new T[n + 11];
    if (!array) {
        throw bad_alloc();
    }
    for (int i = 1; i <= n; i++) {
        array[i] = arr[i - 1];
    }
    for (int i = n / 2; i >= 1; i--) { //完全二叉树n/2总能得到最后一个有叶子的节点
        adjust[i];
    }
    //build(1) 递归方式建立小顶堆
}

template <typename T>
void priority_queue<T>::adjust(int hole) {
    int min_child = 0;
    T cur_val = array[hole];
    while (true) {
        min_child = 2 * hole;
        if (min_child > len) {
            break;
        }
        if (min_child + 1 <= len) {
            if (array[min_child + 1] < array[min_child]) {
                min_child++;
            }
        }
        if (cur_val <= array[min_child]) {
            break;
        }
        array[hole] = array[min_child];
        hole = min_child;
    }
    array[hole] = cur_val;
}

template <typename T>
void priority_queue<T>::build(int root) {
    if (root > len / 2) {
        return;
    }
    build(2 * root);
    build(2 * root + 1);
    adjust(root);
}

template <typename T>
T priority_queue<T>::front() const {
    if (is_empty()) {
        throw out_of_range();
    }
    return array[1];
}

template <typename T>
void priority_queue<T>::in_queue(const T& val) {
    if (is_full()) {
        double_space();
    }

    len++;
    int hole = len;
    for (; hole > 1 && val < array[hole / 2]; hole /= 2) {
        array[hole] = array[hole / 2];
    }
    array[hole] = val;
}

template <typename T>
void priority_queue<T>::de_queue() {
    if (is_empty()) {
        throw out_of_range();
    }
    array[1] = array[len];
    len--;
    adjust(1);
}

template <typename T>
void priority_queue<T>::double_space() {
    int max_size = static_cast<size_t>(-1) / sizeof(T);
    int new_size = max_size > 2 * capacity + 1 ? 2 * capacity : max_size;

    T* new_array = new T[new_size + 1];
    if (!new_array) {
        throw bad_alloc();
    }
    for (int i = 1; i <= capacity(); i++) {
        new_array[i] = array[i];
    }
    delete[] array;
    array = new_array;
    capacity = new_size;
}

#endif //PRIORITY_QUEUE_H