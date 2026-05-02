#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>

struct type {
    int coef;
    int exp;

    type(int _coef = 0, int _exp = 0) : coef(_coef), exp(_exp) {}
    type(const type& other) : coef(other.coef), exp(other.exp) {}
};

struct node {
    type value;
    node* next;

    node(type _value = type(), node* _next = nullptr)
        : value(_value), next(_next) {}
};

struct polynomial {
private:
    node* head;
    type stop_flag;

public:
    polynomial(const type& stop);
    ~polynomial();
    void get_poly();
    void display() const noexcept;
    void clear();
    void add_poly(const polynomial& lhs, const polynomial& rhs); 
};

type get_stop() {
    int c = 0;
    int e = 0;

    std::cout << "请输入(系数, 指数)作为结束标志: ";
    std::cin >> c >> e;

    return type(c, e);
}

polynomial::polynomial(const type& stop = type(0,0)) {
    head = new node();
    stop_flag.coef = stop.coef;
    stop_flag.exp = stop.exp;
}

polynomial::~polynomial() {
    clear();
    delete head;
}

void polynomial::get_poly() {
    node* p = head;
    node* tmp = nullptr;
    type val;

    std::cout << "请按照指数从小到大的顺序输入, "
        << "最后输入结束标志对代表结束:\n";
    
    std::cin >> val.coef >> val.exp;
    while (true) {
        if (val.coef == stop_flag.coef &&
            val.exp == stop_flag.exp) {
            break;
        }

        tmp = new node(type(val.coef, val.exp));
        p->next = tmp;
        p = tmp;

        std::cin >> val.coef >> val.exp;
    }
}

void polynomial::add_poly(const polynomial& lhs, const polynomial& rhs) {
    node* l = lhs.head->next;
    node* r = rhs.head->next;
    clear();
    node* tmp = head;
    while (l != nullptr && r != nullptr) {
        int lcoef = (l->value).coef;
        int lexp = (l->value).exp;
        int rcoef = (r->value).coef;
        int rexp = (r->value).exp;

        if (lexp == rexp) {
            tmp->next = new node(type(lcoef + rcoef, lexp));
            l = l->next;
            r = r->next;
            tmp = tmp->next;
        } else if (lexp < rexp) {
            tmp->next = new node(l->value);
            l = l->next;
            tmp = tmp->next;
        } else {
            tmp->next = new node(r->value);
            r = r->next;
            tmp = tmp->next;
        }
    }
    while (l != nullptr) {
        tmp->next = new node(l->value);
        l = l->next;
        tmp = tmp->next;
    }
    while (r != nullptr) {
        tmp->next = new node(r->value);
        r = r->next;
        tmp = tmp->next;
    }
}

void polynomial::clear() {
    node* cur = head->next;
    node* next = cur->next;

    while (cur != nullptr) {
        delete cur;
        cur = next;
        next = cur->next;
    }
    head->next = nullptr;
}

// 稀疏矩阵: 类似于多项式的存储, 利用一个三元的struct存x,y,value即可
//     最后存到一个线性表中,故不再具体实现

#endif //POLYNOMIAL_H