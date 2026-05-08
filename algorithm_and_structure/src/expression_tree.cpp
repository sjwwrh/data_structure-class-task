#include <iostream>
#include "link_stack.h"
#include "link_tree.h"
#include "sstring.h"
#include "seq_list.h"

bool is_num(const char ch) {
    return (ch >= '0') && (ch <= '9');
}

int priority(const sstring& op) {
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/") return 2;
    return 0;
}

tree_node<sstring>* build_expression_tree(const seq_list<sstring>& midfix) {
    if (midfix.length() == 0) {
        return nullptr;
    }

    link_stack<tree_node<sstring>*> node_stack;
    link_stack<sstring> op_stack;
    for (int i = 1; i <= midfix.length(); i++) {
        if ( is_num(midfix[i][0]) ) {
            tree_node<sstring>* new_node = new tree_node<sstring>(midfix[i]);
            node_stack.push(new_node);
        } 
        else if ( midfix[i] == "(" ) {
            op_stack.push(midfix[i]);
        } 
        else if ( midfix[i] == ")" ) {
            while ( !op_stack.isEmpty() && op_stack.top() != "(" ) {
                tree_node<sstring>* new_node = new tree_node<sstring>(op_stack.top());
                tree_node<sstring>* node_right = node_stack.top();
                node_stack.pop();
                tree_node<sstring>* node_left = node_stack.top();
                node_stack.pop();
                new_node->left = node_left;
                new_node->right = node_right;
                node_stack.push(new_node);
                op_stack.pop();
            }
            if ( !op_stack.isEmpty() && op_stack.top() == "(" ) {
                op_stack.pop();
            }
        } 
        else {
            while ( !op_stack.isEmpty() 
                && priority(op_stack.top()) >= priority(midfix[i]) ) {
                tree_node<sstring>* new_node = new tree_node<sstring>(op_stack.top());
                tree_node<sstring>* node_right = node_stack.top();
                node_stack.pop();
                tree_node<sstring>* node_left = node_stack.top();
                node_stack.pop();
                new_node->left = node_left;
                new_node->right = node_right;
                node_stack.push(new_node);
                op_stack.pop();
            }
            op_stack.push(midfix[i]);
        }
    }

    while ( !op_stack.isEmpty() ) {
        tree_node<sstring>* new_node = new tree_node<sstring>(op_stack.top());
        tree_node<sstring>* node_right = node_stack.top();
        node_stack.pop();
        tree_node<sstring>* node_left = node_stack.top();
        node_stack.pop();
        new_node->left = node_left;
        new_node->right = node_right;
        node_stack.push(new_node);
        op_stack.pop();
    }

    return node_stack.top(); 
}

int calc_expression_tree(tree_node<sstring>* expr_root) {
    if (expr_root == nullptr) {
        return 0;
    }
    if (is_num( (expr_root->val)[0] )) {
        return (expr_root->val).to_number();
    }

    if (expr_root->val == "+") {
        return calc_expression_tree(expr_root->left) + calc_expression_tree(expr_root->right);
    }
    if (expr_root->val == "-") {
        return calc_expression_tree(expr_root->left) - calc_expression_tree(expr_root->right);
    }
    if (expr_root->val == "*") {
        return calc_expression_tree(expr_root->left) * calc_expression_tree(expr_root->right);
    }
    if (expr_root->val == "/") {
        return calc_expression_tree(expr_root->left) / calc_expression_tree(expr_root->right);
    }
    throw;
}


int main() {




    return 0;
}