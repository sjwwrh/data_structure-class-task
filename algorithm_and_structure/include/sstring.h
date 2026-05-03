#ifndef SSTRING_H
#define SSTRING_H

#include "exception.h"

class sstring {
    friend int* next_value(const sstring& str, int len); //for kmp_find

private:
    char* str;
    int capacity;

    static constexpr int INITSIZE = 100;
public:
    sstring(int size = INITSIZE);
    sstring(const char* _str);
    sstring(const sstring& other);
    ~sstring() {
        delete[] str;
    }

    int length() const noexcept;
    void display() const noexcept;
    bool equal(const sstring& other) const noexcept;
    void assign(const sstring& other);
    sstring substring(int pos, int len) const;
    int BF_find(const sstring& substr, int start) const;
    int KMP_find(const sstring& substr, int start) const;
    bool insert(int pos, const sstring& insert_str);
    bool remove(int pos, int n);
};

sstring::sstring(int size) : str(nullptr), capacity() {
    if (size <= 0) {
        throw illegal_size();
    }

    str = new char[size];
    if (!str) {
        throw bad_alloc();
    }
    capacity = size;
    str[0] = '\0';
}

sstring::sstring(const char* _str) : str(nullptr), capacity() {
    int len = 0;
    while (_str[len] != '\0') {
        len++;
    }
    capacity = len + 1;
    str = new char[len + 1];

    int i = 0;
    while (_str[i] != '\0') {
        str[i] = _str[i];
        i++;
    }
    str[i] = '\0';
}

sstring::sstring(const sstring& other) : str(nullptr), capacity(other.capacity) {
    str = new char[capacity];

    int i = 0;
    while (other.str[i] != '\0') {
        str[i] = other.str[i];
        i++;
    }
    str[i] = '\0';
}

int sstring::length() const noexcept {
    int i = 0;
    while (str[i] != '\0') {
        i++;
    }
    return i;
}

bool sstring::equal(const sstring& other) const noexcept {
    int i = 0;
    while (str[i] != '\0' && other.str[i] != '\0') {
        if (str[i] != other.str[i]) {
            return false;
        }
        i++;
    }
    if (str[i] != '\0' || other.str[i] != '\0') {
        return false;
    } else {
        return true;
    }
}

void sstring::assign(const sstring& other) {
    int len = other.length();

    if (capacity <= len) {
        delete[] str;
        capacity = len + 1;
        str = new char[capacity];
        if (!str) {
            throw bad_alloc();
        }
    }

    for (int i = 0; i < len; i++) {
        str[i] = other.str[i];
    }
}

sstring sstring::substring(int pos, int len) const {
    int len_of_str = length();
    if (pos < 0 || pos > len_of_str) {
        throw out_of_range();
    }

    sstring tmp(len + 1);
    for (int i = 0; i < len; i++) {
        if (str[pos + i] == '\0') {
            tmp.str[i] = '\0';
            break;
        }
        tmp.str[i] = str[pos + i];
    }
    return tmp;
}

//模式匹配
//从第start位置的字符起查找substr
//返回其首次出现的位置,否则返回-1
int sstring::BF_find(const sstring& substr, int start) const {
    int cur_start = start;
    int sublen = substr.length();
    int len = length();
    int pos = -1;

    while (cur_start <= len - sublen) {
        bool find = true;
        for (int i = 0; i < sublen; i++) {
            if (str[cur_start + i] != substr.str[i]) {
                find = false;
                break;
            }
        }
        if (find) {
            pos = cur_start;
            break;
        }
        cur_start++;
    }
    return pos;
}

//kmp
int sstring::KMP_find(const sstring& pattern, int start) const {
    int len = length();
    int sublen = pattern.length();
    int* next = next_value(pattern, sublen);
    int cur = start;
    int subcur = 0;

    while (cur < len && subcur < sublen) {
        if (str[cur] == pattern.str[subcur]) {
            cur++;
            subcur++;
        } else if (subcur > 0) {
            subcur = next[subcur];
        } else {
            cur++;
        }
    }

    if (next != nullptr) {
        delete[] next;
    }
    if (subcur == sublen) {
        return cur - sublen;
    } else {
        return -1;
    }
}

int* next_value(const sstring& pattern, int len) {
    if (len <= 0) {
        return nullptr;
    }

    int* next = new int[len];
    if (len < 2) {
        next[0] = 0;
        return next;
    }

    next[0] = 0;
    next[1] = 1;
    int comp = 0;
    int cur = 2;
    while (cur < len) {
        if (pattern.str[cur - 1] == pattern.str[comp]) {
            next[cur] = comp + 1;
            cur++;
            comp++;
        } else if (comp > 0) {
            comp = next[comp];
        } else {
            next[cur] = 0;
            cur++;
        }
    }
    return next;
}



#endif //SSTRING_H