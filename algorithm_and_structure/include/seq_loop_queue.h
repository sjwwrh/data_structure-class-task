#ifndef SEQ_LOOP_QUEUE_H
#define SEQ_LOOP_QUEUE_H

#include "exception.h"

template <typename T>
class seq_loop_queue {
private:
    T* array;
    int capacity;
    int out;
    int in;

public:
    seq_loop_queue(int size = 100);
    ~seq_loop_queue() {
        delete[] array;
    }

    bool is_full() {
        return out == ( (in + 1) % capacity );
    }
    bool is_empty() {
        return in == out;
    }
    T front() const {
        if (is_empty()) {
            throw out_of_range();
        }
        return array[out];
    }
    void in_queue(const T& val);
    void de_queue() noexcept;
       
private:
    void double_space();
};

template <typename T>
seq_loop_queue<T>::seq_loop_queue(int size)
    : array(nullptr), capacity(size), out(0), in(0) {
    array = new T[size];
    if (!array) {
        throw bad_alloc();
    }
}

template <typename T>
void seq_loop_queue<T>::in_queue(const T& val) {
    if (is_full()) {
        double_space();
    }

    array[in] = val;
    in = ( in + 1 ) % capacity;
}

template <typename T>
void seq_loop_queue<T>::de_queue() noexcept {
    if (is_empty()) {
        return;
    }
    out = (out + 1) % capacity;
}

template <typename T>
void seq_loop_queue<T>::double_space() {
    int max_size = static_cast<unsigned long>(-1) / sizeof(T);
    int new_size = max_size > 2 * capacity ? 2 * capacity : max_size;

    T* new_array = new T[new_size];
    if (!array) {
        throw bad_alloc();
    }

    int i = 0;
    for (i = 0; i < capacity; i++) {
        new_array[i] = array[(out + i) % capacity];
    }
    delete[] array;
    array = new_array;
    capacity = new_size;
    in = (out + i) % capacity;
}


#endif //SEQ_LOOP_QUEUE_H