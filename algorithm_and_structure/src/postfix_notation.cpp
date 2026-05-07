#include <iostream>
#include "link_stack.h"
#include "seq_list.h"
#include "sstring.h"

bool is_num(const char ch) {
    return ('0' <= ch) && (ch <= '9');
}

int operation(int lhs, int rhs, const sstring& op) {
    if (op == "+") {
        return lhs + rhs;
    }
    if (op == "-") {
        return lhs - rhs;
    }
    if (op == "*") {
        return lhs * rhs;
    }
    if (op == "/") {
        return lhs / rhs;
    }
    return 0;
}

int priority(const char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

seq_list<sstring> transfer_to_postfix(const seq_list<sstring>& midfix) {
    seq_list<sstring> postfix;
    link_stack<char> op_stack;
    for (int i = 1; i <= midfix.length(); i++) {
        if (is_num(midfix[i][0])) {
            postfix.push_back(midfix[i]);
        } else if (midfix[i] == "(") {
            op_stack.push(midfix[i][0]);
        } else if (midfix[i] == ")") {
            while (!op_stack.isEmpty() && op_stack.top() != '(') {
                char op[2];
                op[0] = op_stack.top();
                op[1] = '\0';
                postfix.push_back(op);
                op_stack.pop();
            }
            if (!op_stack.isEmpty() && op_stack.top() == '(') {
                op_stack.pop();
            }
        } else {
            while (!op_stack.isEmpty() && (priority(midfix[i][0]) <= priority(op_stack.top()))) {
                char op[2];
                op[0] = op_stack.top();
                op[1] = '\0';
                postfix.push_back(op);
                op_stack.pop();
            }
            op_stack.push(midfix[i][0]);
        }
    }

    while (!op_stack.isEmpty()) {
        char op[2];
        op[0] = op_stack.top();
        op[1] = '\0';
        postfix.push_back(op);
        op_stack.pop();
    }
    return postfix;
}

int calc_value_postfix(const seq_list<sstring>& postfix) {
    int len = postfix.length();
    if (len == 0) {
        return 0;
    }

    link_stack<int> num_stack;
    for (int i = 1; i <= len; i++) {
        if (postfix[i] == "+" || postfix[i] == "-" || postfix[i] == "*" || postfix[i] == "/") {
            int num_right = num_stack.top();
            num_stack.pop();
            int num_left = num_stack.top();
            num_stack.pop();
            num_stack.push(operation(num_left, num_right, postfix[i]));
        } else {
            num_stack.push(postfix[i].to_number());
        }
    }
    int res = num_stack.top();
    return res;
}

int main() {
    // 测试中缀表达式转换为后缀表达式并计算值
    seq_list<sstring> midfix;
    midfix.push_back("9");
    midfix.push_back("*");
    midfix.push_back("(");
    midfix.push_back("5");
    midfix.push_back("-");
    midfix.push_back("1");
    midfix.push_back(")");
    midfix.push_back("+");
    midfix.push_back("10");
    midfix.push_back("/");
    midfix.push_back("2");

    seq_list<sstring> postfix = transfer_to_postfix(midfix);
    int result = calc_value_postfix(postfix);

    for (int i = 1; i <= midfix.length(); i++) {
        std::cout << midfix[i] << " ";
    }
    std::cout << std::endl;

    for (int i = 1; i <= postfix.length(); i++) {
        std::cout << postfix[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "result = " << result << std::endl;

    return 0;
}