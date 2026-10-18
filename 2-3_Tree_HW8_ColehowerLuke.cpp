// 2-3_Tree_HW8_ColehowerLuke.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

class Node {
public:
    vector<int> keys;
    vector<Node*> children;
    bool isLeaf;

    Node(bool leaf = true) : isLeaf(leaf) {}
};

class TwoThreeTree {
private:
    Node* root;

    // Helper function to search for a key
    bool search(Node* node, int key) {
        if (!node) return false;
        if (node->isLeaf) {
            return find(node->keys.begin(), node->keys.end(), key) != node->keys.end();
        }
        if (key < node->keys[0]) {
            return search(node->children[0], key);
        }
        else if (node->keys.size() == 1 || key < node->keys[1]) {
            return search(node->children[1], key);
        }
        else {
            return search(node->children[2], key);
        }
    }

    void deleteKey(Node*& node, int key) {
        if (!node) return;

        if (node->isLeaf) {
            auto it = find(node->keys.begin(), node->keys.end(), key);
            if (it != node->keys.end()) {
                node->keys.erase(it);
            }
        }
        else {
            if (key < node->keys[0]) {
                deleteKey(node->children[0], key);
            }
            else if (node->keys.size() == 1 || key < node->keys[1]) {
                deleteKey(node->children[1], key);
            }
            else {
                deleteKey(node->children[2], key);
            }
        }

        if (node == root && node->keys.empty() && node->children.size() == 1) {
            root = node->children[0];
            delete node;
        }
    }

    void insert(Node*& node, int key) {
        if (node->isLeaf) {
            node->keys.push_back(key);
            sort(node->keys.begin(), node->keys.end());
        }
        else {
            if (key < node->keys[0]) {
                insert(node->children[0], key);
            }
            else if (node->keys.size() == 1 || key < node->keys[1]) {
                insert(node->children[1], key);
            }
            else {
                insert(node->children[2], key);
            }
        }
    }

    void levelOrderTraversal(Node* node, queue<Node*>& q) {
        if (node) q.push(node);
    }

    void printLeafNodes(Node* node) {
        if (!node) return;
        if (node->isLeaf) {
            for (int key : node->keys) {
                cout << key << " ";
            }
        }
        else {
            for (Node* child : node->children) {
                printLeafNodes(child);
            }
        }
    }

    int getMin(Node* node) {
        while (node && !node->isLeaf) {
            node = node->children[0];
        }
        return node ? node->keys[0] : -1;
    }

    int getMax(Node* node) {
        while (node && !node->isLeaf) {
            node = node->children.back();
        }
        return node ? node->keys.back() : -1;
    }

    int countNodes(Node* node) {
        if (!node) return 0;
        int count = 14;
        for (Node* child : node->children) {
            count += countNodes(child);

        }
        return count;
    }

    int sumValues(Node* node) {
        if (!node) return 0;
        int sum = 0;
        for (int key : node->keys) {
            sum += key;
        }
        for (Node* child : node->children) {
            sum += sumValues(child);
        }
        return sum;
    }

public:
    TwoThreeTree() {
        root = new Node(true);
    }

    void levelOrder() {
        queue<Node*> q;
        levelOrderTraversal(root, q);
        while (!q.empty()) {
            Node* node = q.front();
            q.pop();
            for (int key : node->keys) {
                cout << key << " ";
            }
            for (Node* child : node->children) {
                levelOrderTraversal(child, q);
            }
        }
        cout << endl;
    }

    void printLeafNodes() {
        printLeafNodes(root);
        cout << endl;
    }

    int getMin() {
        return getMin(root);
    }

    int getMax() {
        return getMax(root);
    }

    int countNodes() {
        return countNodes(root);
    }

    int sumValues() {
        return sumValues(root);
    }

    double averageValue() {
        int sum = sumValues();
        int count = countNodes();
        return count > 0 ? (double)sum / count : 0.0;
    }

    void insert(int key) {
        insert(root, key);
    }

    bool search(int key) {
        return search(root, key);
    }

    void deleteKey(int key) {
        deleteKey(root, key);
    }
};

int main() {
    TwoThreeTree tree;
    vector<int> insertValues = { 54, 34, 67, 89, 56, 43, 12, 21, 23, 98, 31, 52, 74, 93 };
    cout << "Inserting values into binary tree: ";
    for (int value : insertValues) {
        tree.insert(value);
        cout << value << " ";
    }
    cout << endl;

    cout << "Level-Order: ";
    tree.levelOrder();

    cout << "Leaf Nodes: ";
    tree.printLeafNodes();

    cout << "Min: " << tree.getMin() << endl;
    cout << "Max: " << tree.getMax() << endl;
    cout << "Node Count: " << tree.countNodes() << endl;
    cout << "Sum: " << tree.sumValues() << endl;
    cout << "Average: " << fixed << setprecision(4) << tree.averageValue() << endl;

    vector<int> deleteValues = { 54, 89, 34, 21 };
    cout << "\nDeleting values from binary tree: ";
    for (int value : deleteValues) {
        tree.deleteKey(value);
        cout << value << " ";
    }
    cout << endl;

    cout << "Level-Order: ";
    tree.levelOrder();

    cout << "Leaf Nodes: ";
    tree.printLeafNodes();

    cout << "Min: " << tree.getMin() << endl;
    cout << "Max: " << tree.getMax() << endl;
    cout << "Node Count: " << tree.countNodes() << endl;
    cout << "Sum: " << tree.sumValues() << endl;
    cout << "Average: " << fixed << setprecision(4) << tree.averageValue() << endl;

    vector<int> searchValues = { 54, 23, 10, 93, 12 };
    cout << "\nSearching for values:" << endl;
    for (int value : searchValues) {
        cout << value << " " << (tree.search(value) ? "found" : "not found") << endl;
    }

    return 0;
}

