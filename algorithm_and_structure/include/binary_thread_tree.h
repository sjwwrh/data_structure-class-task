#ifndef BINARY_THREAD_TREE
#define BINARY_THREAD_TREE

#include "seq_loop_queue.h"
#include "seq_stack.h"
#include <iostream>

template <typename T>
struct tree_node {
    tree_node* left;
    tree_node* right;
    T val;
    bool left_flag;
    bool right_flag;

    tree_node(const T& _val, tree_node* l = nullptr, tree_node* r = nullptr)
        : val(_val), left(l), right(r), left_flag(false), right_flag(false) {}
    tree_node(T&& _val = T(), tree_node* l = nullptr, tree_node* r = nullptr)
        : val(_val), left(l), right(r), left_flag(false), right_flag(false) {}
};

template <typename T>
class binary_thread_tree {
private:
    tree_node<T>* root;
    tree_node<T>* first;  //线索首节点

public:
    binary_thread_tree() : root(nullptr), first(nullptr) {}
    ~binary_thread_tree() {
        delete_all(root);
    }
    void create(const T& stop_flag);
    bool is_empty() const noexcept {
        return root == nullptr;
    }
    void thread_mid();
    void thread_mid_visit();
    void thread_mid_pre_visit();

private:
    void delete_all(tree_node<T>* _root) noexcept;
};

template <typename T>
void binary_thread_tree<T>::delete_all(tree_node<T>* _root) noexcept {
    if (_root == nullptr) {
        return;
    }

    delete_all(_root->left);
    delete_all(_root->right);
    delete _root;
}

template <typename T>
void binary_thread_tree<T>::create(const T& stop_flag) {
    seq_loop_queue<tree_node<T>*> queue;

    std::cout << "please input the value of the root: ";
    T root_val;
    std::cin >> root_val;
    if (root_val == stop_flag) {
        return;
    }
    root = new tree_node<T>(root_val);
    queue.in_queue(root);

    tree_node<T>* tmp = nullptr;
    tree_node<T>* tmpl = nullptr;
    tree_node<T>* tmpr = nullptr;
    T left_val;
    T right_val;
    while (!queue.is_empty()) {
        tmp = queue.front();
        queue.de_queue();
        std::cout << "please input the value of the left and right child of"
            << tmp->val << " ,using " << stop_flag << " as no child: ";
        std::cin >> left_val >> right_val;
        if (left_val != stop_flag) {
            tmpl = new tree_node<T>(left_val);
            tmp->left = tmpl;
            queue.in_queue(tmpl);
        }
        if (right_val != stop_flag) {
            tmpr = new tree_node<T>(right_val);
            tmp->right = tmpr;
            queue.in_queue(tmpr);
        }
    }
}

template <typename T>
void binary_thread_tree<T>::thread_mid() {
    if (root == nullptr) {
        first = nullptr;
        return;
    }

    tree_node<T>* pre = nullptr;
    tree_node<T>* cur_node = nullptr;
    seq_stack<tree_node<T>*> node_stack;
    seq_stack<int> ret_stack;
    node_stack.push(root);
    ret_stack.push(0);


    while (!node_stack.is_empty()) {
        int flag = ret_stack.top();
        ret_stack.pop();
        cur_node = node_stack.top();

        if (flag == 0) {
            ret_stack.push(1);
            if (cur_node->left != nullptr) {
                node_stack.push(cur_node->left);
            }
        } else {
            node_stack.pop();
            if (first == nullptr) {
                first = cur_node;
            }
            if (cur_node->right != nullptr) {
                node_stack.push(cur_node->right);
                ret_stack.push(0);
            }
            if (cur_node->left == nullptr) {
                cur_node->left_flag = true;
                cur_node->left = pre;
            }
            if (pre != nullptr && pre->right == nullptr) {
                pre->right = cur_node;
                pre->right_flag = true;
            }
            pre = cur_node;
        }
    }
    cur_node->right_flag = true;
}

template <typename T>
void binary_thread_tree<T>::thread_mid_visit() {
    if (first == nullptr) {
        return;
    }

    tree_node<T>* cur_node = first;
    while (cur_node != nullptr) {
        std::cout << cur_node->val << ' ';
        if (!cur_node->right_flag) {
            cur_node = cur_node->right;
            while (!cur_node->left_flag) {
                cur_node = cur_node->left;
            }
        } else {
            cur_node = cur_node->right;
        }
    }
    std::cout << '\n';
}

#endif //BINARY_THREAD_TREE