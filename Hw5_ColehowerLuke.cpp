// Hw5_ColehowerLuke.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;
// Stack Class
class DynIntStack {
private:
    struct StackNode {
        int value;
        StackNode* next;
    };
    StackNode* top;

public:
    DynIntStack() : top(nullptr) {}

    void push(int val) {
        StackNode* newNode = new StackNode{ val, top };
        top = newNode;
    }

    bool pop(int& val) {
        if (isEmpty()) {
            return false;
        }
        StackNode* temp = top;
        val = top->value;
        top = top->next;
        delete temp;
        return true;
    }

    bool isEmpty() {
        return top == nullptr;
    }

    void print() {
        if (isEmpty()) {
            cout << "Stack: empty" << endl;
        }
        else {
            cout << "Stack: ";
            StackNode* current = top;
            while (current) {
                cout << current->value << " ";
                current = current->next;
            }
            cout << endl;
        }
    }

    ~DynIntStack() {
        while (!isEmpty()) {
            int temp;
            pop(temp);
        }
    }
};
// Queue Class
class DynIntQueue {
private:
    struct QueueNode {
        int value;
        QueueNode* next;
    };
    QueueNode* front;
    QueueNode* rear;

public:
    DynIntQueue() : front(nullptr), rear(nullptr) {}

    void enqueue(int val) {
        QueueNode* newNode = new QueueNode{ val, nullptr };
        if (isEmpty()) {
            front = rear = newNode;
        }
        else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    bool dequeue(int& val) {
        if (isEmpty()) {
            return false;
        }
        QueueNode* temp = front;
        val = front->value;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }
        delete temp;
        return true;
    }

    bool isEmpty() {
        return front == nullptr;
    }

    void print() {
        if (isEmpty()) {
            cout << "Queue: empty" << endl;
        }
        else {
            cout << "Queue: ";
            QueueNode* current = front;
            while (current) {
                cout << current->value << " ";
                current = current->next;
            }
            cout << endl;
        }
    }

    ~DynIntQueue() {
        while (!isEmpty()) {
            int temp;
            dequeue(temp);
        }
    }
};

int main() {
    DynIntStack stack;
    DynIntQueue queue;
    int option, value;

    do {
        cout << "\n1) Print stack and queue\n"
            << "2) Add a value to stack\n"
            << "3) Add a value to queue\n"
            << "4) Remove a value from stack\n"
            << "5) Remove a value from queue\n"
            << "Enter an option, 0 to quit: ";
        cin >> option;

        switch (option) {
        case 1:
            stack.print();
            queue.print();
            break;
        case 2:
            cout << "Enter Value: ";
            cin >> value;
            stack.push(value);
            cout << value << " entered in stack." << endl;
            break;
        case 3:
            cout << "Enter Value: ";
            cin >> value;
            queue.enqueue(value);
            cout << value << " entered in queue." << endl;
            break;
        case 4:
            if (stack.pop(value)) {
                cout << "Value removed from stack: " << value << endl;
            }
            else {
                cout << "Stack is empty." << endl;
            }
            break;
        case 5:
            if (queue.dequeue(value)) {
                cout << "Value removed from queue: " << value << endl;
            }
            else {
                cout << "Queue is empty." << endl;
            }
            break;
        case 0:
            cout << "Exiting program." << endl;
            break;
        default:
            cout << "Invalid option. Please try again." << endl;
        }
    } while (option != 0);

    return 0;
}

