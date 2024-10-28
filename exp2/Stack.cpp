#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <stdexcept>

template <typename T>
class Stack {
private:
    struct Node {
        T data;
        Node* next;

        Node(T value) : data(value), next(nullptr) {}
    };

    Node* topNode; // 指向栈顶元素
    int size; // 记录栈的大小

public:
    // 构造函数
    Stack() : topNode(nullptr), size(0) {}

    // 析构函数
    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }

    // 判断栈是否为空
    bool isEmpty() const {
        return size == 0;
    }

    // 返回栈的大小
    int getSize() const {
        return size;
    }

    // 推入元素
    void push(const T& value) {
        Node* newNode = new Node(value);
        newNode->next = topNode; // 新节点指向当前栈顶
        topNode = newNode; // 更新栈顶
        size++; // 增加大小
    }

    // 弹出元素
    T pop() {
        if (isEmpty()) {
            throw std::runtime_error("Stack is empty, cannot pop.");
        }
        Node* temp = topNode; // 临时保存栈顶
        T value = topNode->data; // 获取栈顶值
        topNode = topNode->next; // 更新栈顶
        delete temp; // 释放原栈顶
        size--; // 减小大小
        return value; // 返回弹出值
    }

    // 获取栈顶元素
    T top() const {
        if (isEmpty()) {
            throw std::runtime_error("Stack is empty, cannot access top.");
        }
        return topNode->data; // 返回栈顶元素
    }
};

#endif // STACK_H
