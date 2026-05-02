#ifndef SEQLIST_H
#define SEQLIST_H

//以第一个元素为哨兵
template <typename T>
class seq_list {
private:
    T* elem;
    int len;
    int capacity;
    static constexpr int INITSIZE = 100;

public:
    seq_list(int size = INITSIZE) {
        elem = new T[size];
        if (!elem) {
            throw std::bad_alloc();
        }
        len = 0;
        capacity = size - 1;
    }

    ~seq_list() {
        delete[] elem;
    }

    T get(int i) const {
        if (i < 1 || i > len) {
            throw std::out_of_range();
        }
        return elem[i];
    }

    int find(const T& val) const {
        elem[0] = val;
        for (int i = len; elem[i] != val; i--) { }
        return i;
    }

    void insert(int i, const T& val) {
        if (i < 1 || i > len + 1) {
            throw std::out_of_range();
        }

       if (len == capacity) {
            doubleSpace();
       }
       elem[len + 1] = elem[len];
       for (int cur = len - 1; cur >= i; cur--) {
            elem[cur + 1] = elem[cur];
       }
       elem[i] = val;
       len++;
    }


    void remove(int i) {
        if (i < 1 || i > len) {
            throw std::out_of_range();
        }
        for (int cur = i; i < len; i++) {
            elem[i] = elem[i + 1];
        }

        len--;
    }

    void clear() noexcept {
        len = 0;
    }
    void func() const {
        elem[1] = 0;
    }
    bool isEmpty() const noexcept {
        return len == 0;
    }
    bool isFull() const noexcept {
        return len == capacity;
    }
    int length() const noexcept {
        return len;
    }

private:
    void doubleSpace() {
        int max_size = static_cast<size_t>(-1) / sizeof(T);
        int new_size = max_size > 2 * capacity ? 2 * capacity : max_size;

        delete[] elem;
        elem = new T[new_size];
        if (!elem) {
            throw std::bad_alloc();
        }

        capacity = new_size;
    }

};

#endif //SEQLIST_H