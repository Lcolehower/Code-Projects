// Hw3_ColehowerLuke.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

// Function to sort the array using Bubble Sort
void bubbleSort(int* arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (*(arr + j) > *(arr + j + 1)) {
                // Swap
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
    cout << "Enter the Input file or File path : ";
    cin >> inputFileName;

    ifstream inputFile(inputFileName);
    if (!inputFile) {
        cerr << "Error opening input file!" << endl;
        return 1;
    }

    int numberOfValues;
    inputFile >> numberOfValues;

    int* values = new int[numberOfValues];

    // Step 5: Read values from the file into the array
    cout << "Opening input file..." << endl;
    cout << "Storing " << numberOfValues << " values to array..." << endl;
    for (int i = 0; i < numberOfValues; i++) {
        inputFile >> *(values + i);
    }
    inputFile.close();
    cout << "Done reading values from input file." << endl;

    cout << "Sorting values..." << endl;
    bubbleSort(values, numberOfValues);

    string outputFileName;
    cout << "Enter the output file or output file path: ";
    cin >> outputFileName;

    ofstream outputFile(outputFileName);
    if (!outputFile) {
        cerr << "Error creating output file!" << endl;
        delete[] values;
        return 1;
    }

    cout << "Printing sorted values to output file..." << endl;
    for (int i = 0; i < numberOfValues; i++) {
        outputFile << *(values + i) << endl;
    }
    outputFile.close();
    cout << "Sorted values printed to " << outputFileName << endl;
    delete[] values;

    return 0;
}
