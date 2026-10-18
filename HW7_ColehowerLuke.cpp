// HW7_ColehowerLuke.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

class IntBinaryTree {
private:
    struct TreeNode {
        int value;
        TreeNode* left;
        TreeNode* right;

        TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
    };

    TreeNode* root;

    void insert(TreeNode*& node, int value) {
        if (node == nullptr) {
            node = new TreeNode(value);
        }
        else if (value < node->value) {
            insert(node->left, value);
        }
        else {
            insert(node->right, value);
        }
    }

    void displayInOrder(TreeNode* node) {
        if (node != nullptr) {
            displayInOrder(node->left);
            cout << setw(4) << node->value; 
            displayInOrder(node->right);
        }
    }

    void displayPreOrder(TreeNode* node) {
        if (node != nullptr) {
            cout << setw(4) << node->value; 
            displayPreOrder(node->left);
            displayPreOrder(node->right);
        }
    }

    void displayPostOrder(TreeNode* node) {
        if (node != nullptr) {
            displayPostOrder(node->left);
            displayPostOrder(node->right);
            cout << setw(4) << node->value; 
        }
    }

    void printLeafNodes(TreeNode* node) {
        if (node != nullptr) {
            if (node->left == nullptr && node->right == nullptr) {
                cout << setw(4) << node->value; 
            }
            printLeafNodes(node->left);
            printLeafNodes(node->right);
        }
    }

public:
    IntBinaryTree() : root(nullptr) {}

    void insert(int value) {
        insert(root, value);
    }

    void showInOrder() {
        displayInOrder(root);
        cout << endl;
    }

    void showPreOrder() {
        displayPreOrder(root);
        cout << endl;
    }

    void showPostOrder() {
        displayPostOrder(root);
        cout << endl;
    }

    void showLeafNodes() {
        printLeafNodes(root);
        cout << endl;
    }
};

int main() {
    IntBinaryTree tree;
    string filename;

    cout << "Enter input filename: ";
    cin >> filename;
    ifstream inputFile(filename);

    if (!inputFile) {
        cout << "Error opening " << filename << "..." << endl;
        return 1;
    }

    cout << "\nOpening " << filename << "..." << endl;
    cout << "Inserting values into binary tree...\n" << endl;

    int value;
    while (inputFile >> value) {
        tree.insert(value);
    }

    inputFile.close();

    cout << "Printing Values In-Order:\n";
    cout << "-------------------------\n";
    tree.showInOrder();

    cout << "\nPrinting Values Pre-Order:\n";
    cout << "--------------------------\n";
    tree.showPreOrder();

    cout << "\nPrinting Values Post-Order:\n";
    cout << "---------------------------\n";
    tree.showPostOrder();

    cout << "\nPrinting Leaf Nodes:\n";
    cout << "---------------------\n";
    tree.showLeafNodes();

    return 0;
}

