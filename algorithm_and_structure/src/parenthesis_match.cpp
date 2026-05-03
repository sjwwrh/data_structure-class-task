#include "link_stack.h"
#include <iostream>

bool match(const char* str) {
    link_stack<char> parenthesis;
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == '{' || str[i] == '[' || str[i] == '(') {
            parenthesis.push(str[i]);
        } else if (str[i] == '}') {
            if (parenthesis.isEmpty()) {
                return false;
            }

            char ch = parenthesis.top();
            if (ch != '{') {
                return false;
            }
            parenthesis.pop();
        } else if (str[i] == ']') {
            if (parenthesis.isEmpty()) {
                return false;
            }

            char ch = parenthesis.top();
            if (ch != '[') {
                return false;
            }
            parenthesis.pop();
        } else if (str[i] == ')') {
            if (parenthesis.isEmpty()) {
                return false;
            }

            char ch = parenthesis.top();
            if (ch != '(') {
                return false;
            }
            parenthesis.pop();
        }
        i++;
    }
    if (parenthesis.isEmpty()) {
        return true;
    } else {
        return false;
    }
}

void print(bool ret) {
    if (ret) {
        std::cout << "matching\n";
    } else {
        std::cout << "no matching\n";
    }
}

int main() {
    print(match("fdjlsf({[]})"));
    print(match("))((fjdl))"));
    print(match("(]{})"));

    return 0;
}