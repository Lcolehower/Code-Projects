// Overloading_BinaryTree_ColehowerLuke.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std; 

class IntBinaryTree {
private:
    struct TreeNode {
        int value;
        TreeNode* left;
        TreeNode* right;
        TreeNode(int v) : value(v), left(nullptr), right(nullptr) {}
    };

    TreeNode* root;

    TreeNode* copyTree(TreeNode* node) {
        if (node == nullptr) {
            return nullptr;
        }
        TreeNode* newNode = new TreeNode(node->value);
        newNode->left = copyTree(node->left);
        newNode->right = copyTree(node->right);
        return newNode;
    }
    void deleteTree(TreeNode* node) {
        if (node != nullptr) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }

public:
    IntBinaryTree() : root(nullptr) {}

    IntBinaryTree(const IntBinaryTree& other) {
        root = copyTree(other.root);
    }

    IntBinaryTree& operator=(const IntBinaryTree& rhs) {
        if (this == &rhs) {
            return *this;
        }
        deleteTree(root);
        root = copyTree(rhs.root);
        return *this;
    }
    void insert(int value) {
        TreeNode** cur = &root;
        while (*cur) {
            if (value < (*cur)->value) {
                cur = &(*cur)->left;
            }
            else {
                cur = &(*cur)->right;
            }
        }
        *cur = new TreeNode(value);
    }
    void printTree() const {
        printTree(root);
    }

    void printTree(TreeNode* node) const {
        if (node) {
            printTree(node->left);
            std::cout << node->value << " ";
            printTree(node->right);
        }
    }
    ~IntBinaryTree() {
        deleteTree(root);
    }
};

int main() {
    IntBinaryTree treeA;
    treeA.insert(5);
    treeA.insert(3);
    treeA.insert(7);

    cout << "Tree A: ";
    treeA.printTree(); 

    IntBinaryTree treeB;
    treeB.insert(10);
    treeB.insert(8);
    treeB.insert(12);

    cout << "\nTree B: ";
    treeB.printTree(); 

    // Perform assignment: A = B
    treeA = treeB;

    cout << "\nAfter assignment, Tree A: ";
    treeA.printTree();  // Should print 8 10 12 (deep copy of Tree B)

    return 0;
}
