#ifndef LINK_TREE_H
#define LINK_TREE_H

#include "link_stack.h"
#include "seq_loop_queue.h"
#include <iostream>

template <typename T>
struct tree_node {
    tree_node* left;
    tree_node* right;
    T val;

    tree_node(const T& _val, tree_node* l = nullptr, tree_node* r = nullptr)
        : val(_val), left(l), right(r) {}
    tree_node(T&& _val = T(), tree_node* l = nullptr, tree_node* r = nullptr)
        : val(_val), left(l), right(r) {}
};

template <typename T>
class link_tree {
public:
    using iterator = tree_node<T>*;

private:    
    iterator root;

public:
    link_tree(const tree_node<T>* _root = nullptr) : root(_root) {}
    link_tree(const link_tree<T>& other) : root(nullptr) {
        deep_copying(other);
    }
    link_tree(link_tree<T>&& other) : root(other.root) {
        other.root = nullptr;
    }
    ~link_tree() {
        delete_all();
    }

    int size() const {
        size_impl_stack(root);
    }
    bool empty() const noexcept {
        return root == nullptr; 
    }
    void create_tree(const T& stop_flag);
    int height() const {
        return height_impl_recursive(root);
    }
    void preorder_print() const {
        preorder_print_impl_recursive(root);
    }
    void inorder_print() const {
        inorder_print_impl_stack(root);
    }
    void postorder_print() const {
        postorder_print_impl_stack(root);
    }
    void build_with_preorder_and_inorder_seq(T pre[], T in[], int len) {
        if (root != nullptr) {
            delete_all();
        }
        root = build_with_preorder_and_inorder_seq_impl(pre, 0, len - 1, in, 0, len - 1);
    }

private:
    void deep_copying(const tree_node<T>* other_root) {
        delete_all();
        deep_copying_impl(root, other_root);
    }
    void delete_all() noexcept {
        delete_all_impl(root);
        root = nullptr;
    }
};

template <typename T>
void link_tree<T>::create_tree(const T& stop_flag) {
    seq_loop_queue<iterator> queue;

    std::cout << "please input the value of the root: ";
    T root_val;
    std::cin >> root_val;
    if (root_val == stop_flag) {
        return;
    }
    root = new tree_node<T>(root_val);
    queue.in_queue(root);

    iterator tmp = nullptr;
    iterator tmpl = nullptr;
    iterator tmpr = nullptr;
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


//---------------------------------------------------------
//非成员函数
//---------------------------------------------------------

template <typename T>
void deep_copying_impl(tree_node<T>*& dst_root, const tree_node<T>* src_root) {
    if (src_root == nullptr) {
        dst_root = nullptr;
        return;
    }

    try {
        dst_root = new tree_node<T>(src_root->val);
        if (src_root->left != nullptr) {
            deep_copying_impl(dst_root->left, src_root->left);
        }
        if (src_root->right != nullptr) {
            deep_copying_impl(dst_root->right, src_root->right);
        }
    } catch (...) {
        delete_all_impl(dst_root);
        throw;
    }
}

template <typename T>
void delete_all_impl(tree_node<T>* root) noexcept {
    if (root == nullptr) {
        return;
    }

    if (root->left != nullptr) {
        delete_all_impl(root->left);
    }
    if (root->right != nullptr) {
        delete_all_impl(root->right);
    }
    delete root;
}

template <typename T>
int size_impl_stack(tree_node<T>* root) {
    if (root == nullptr) {
        return 0;
    }

    link_stack<tree_node<T>*> help_stack;
    int cnt = 0;
    help_stack.push(root);
    while (!help_stack.empty()) {
        root = help_stack.top();
        help_stack.pop();
        cnt++;
        if (root->left != nullptr) {
            help_stack.push(root->left);
        }
        if (root->right != nullptr) {
            help_stack.push(root->right);
        }
    }

    return cnt;
}

template <typename T>
int height_impl_recursive(tree_node<T>* root) {
    if (root == nullptr) {
        return 0;
    }
    int l_height = height_impl_recursive(root->left);
    int r_height = height_impl_recursive(root->right);
    int max_height = l_height > r_height ? l_height : r_height;
    return max_height + 1; 
}

template <typename T>
void inorder_print_impl_stack(tree_node<T>* root) {
    if (root != nullptr) {
        link_stack<tree_node<T>*> help_stack;
        while (!help_stack.empty() || root != nullptr) {
            if (root != nullptr) {
                help_stack.push(root);
                root = root->left;
            } else {
                root = help_stack.top();
                help_stack.pop();
                std::cout << root->value << ' ';
                root = root->right;
            }
        }
    }
}

template <typename T>
void inorder_print_impl_stack2(tree_node<T>* root) {
    if (root != nullptr) {
        link_stack<tree_node<T>*> node_stack;
        link_stack<int> ret_stack;
        node_stack.push(root);
        ret_stack.push(0);
        while (!node_stack.empty()) {
            int ret = ret_stack.top();
            if (ret == 0) {
                ret_stack.pop();
                ret_stack.push(1);
                auto cur = node_stack.top();
                if (cur->left != nullptr) {
                    node_stack.push(cur->left);
                    ret_stack.push(0);
                }
            } else if (ret == 1) {
                auto cur = node_stack.top();
                node_stack.pop();
                ret_stack.pop();
                std::cout << cur->value << ' ';
                if (cur->right != nullptr) {
                    node_stack.push(cur->left);
                    ret_stack.push(0);
                }
            }
        }
    }
}

template <typename T>
void preorder_print_impl_recursive(tree_node<T>* root) {
    if (root == nullptr) {
        return;
    }

    std::cout << root->val << ' ';
    preorder_print_impl_recursive(root->left);
    preorder_print_impl_recursive(root->right);
}

template <typename T>
void postorder_print_impl_stack(tree_node<T>* root) {
    if (root != nullptr) {
        link_stack<tree_node<T>*> help_stack;
        link_stack<tree_node<T>*> print_stack;

        help_stack.push(root);
        while (!help_stack.empty()) {
            auto cur = help_stack.top();
            help_stack.pop();
            print_stack.push(cur);
            if (cur->left != nullptr) {
                help_stack.push(cur->left);
            }
            if (cur->right != nullptr) {
                help_stack.push(cur->right);
            }
        }
        while (!print_stack.empty()) {
            auto cur = print_stack.top();
            std::cout << cur->value << ' ';
            print_stack.pop();
        }
    }
    std::cout << '\n';
}

template <typename T>
tree_node<T>* build_with_preorder_and_inorder_seq_impl(
    T pre[], int pl, int pr,
    T in[], int il, int ir
) {
    if (il > ir || pl > pr) {
        return nullptr;
    }

    tree_node<T>* root = new tree_node<T>(pre[pl]);
    int root_pos = il;
    while (in[root_pos] != pre[pl]) {
        root_pos++;
    }
    int il1 = il;
    int ir1 = root_pos - 1;
    int il2 = root_pos + 1;
    int ir2 = ir;
    int pl1 = pl + 1;
    int pr1 = pl + (root_pos - il);
    int pl2 = pr1 + 1;
    int pr2 = pr;

    tree_node<T>* left = build_with_preorder_and_inorder_seq_impl(
        pre, pl1, pr1,
        in, il1, ir1
    );
    tree_node<T>* right = build_with_preorder_and_inorder_seq_impl(
        pre, pl2, pr2,
        in, il2, ir2
    );
    root->left = left;
    root->right = right;

    return root;
}





#endif //LINK_TREE_H