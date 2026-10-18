// HW4_ColehowerLuke.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;
struct Node {
    int data;
    Node* next;
};

void addNode(Node*& head, int value) {
    Node* newNode = new Node();
    newNode->data = value;
    newNode->next = head; 
    head = newNode;      
}

void deleteList(Node*& head) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

void printListToFile(Node* head, ofstream& outputFile) {
    Node* current = head;
    while (current != nullptr) {
        outputFile << current->data << endl;
        current = current->next;
    }
}

void bubbleSort(int* arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (*(arr + j) > *(arr + j + 1)) {
               
                int temp = *(arr + j);
                *(arr + j) = *(arr + j + 1);
                *(arr + j + 1) = temp;
            }
        }
    }
}

int main() 
{
    string inputFileName;
    cout << "Enter name of input file: ";
    cin >> inputFileName;

    ifstream inputFile(inputFileName);
    if (!inputFile) {
        cerr << "Error opening input file!" << endl;
        return 1;
    }

    Node* head = nullptr;
    int value;

    cout << "Opening input file..." << endl;
    cout << "Storing values to linked list..." << endl;

    
    while (inputFile >> value) {
        addNode(head, value);
    }

    inputFile.close();
    cout << "Done reading values from input file." << endl;

    string outputFileName;
    cout << "Enter name of output file: ";
    cin >> outputFileName;

    ofstream outputFile(outputFileName);
    if (!outputFile) {
        cerr << "Error creating output file!" << endl;
        deleteList(head); 
        return 1;
    }

    cout << "Printing values to output file..." << endl;
    printListToFile(head, outputFile);
    outputFile.close();
    cout << "Values printed to " << outputFileName << " in reverse order." << endl;

    deleteList(head); 
    return 0;
}