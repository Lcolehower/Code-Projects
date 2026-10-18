// HW2_ColehowerLuke.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std; 

void printVector(const vector<int>& vec);
void selectionSort(vector<int>& vec);
int linearSearch(const vector<int>& vec, int value, int& comparison);
int binarySearch(const vector<int>& vec, int value, int& comparison); 

void printVector(const vector<int>& vec) {
	cout << "[ ";
	for (int num : vec) {
		cout << num << "  ";
	}
	cout << "]\n"; 
}
void selectionSort(vector<int>& vec) {
	for (size_t i = 0; i < vec.size() - 1; ++i) {
		size_t minIndex = i;
		for (size_t j = i + 1; j < vec.size(); ++j) {
			if (vec[j] < vec[minIndex]) {
				minIndex = j; 
			}
		}
		swap(vec[i], vec[minIndex]);
	}
}
int linearSearch(const vector<int>& vec, int value, int& comparison) {
	for (int i = 0; i < vec.size(); ++i) {
		++comparison;
		if (vec[i] == value) {
			return i;
		}
	}
	return -1; 
}
int binarySearch(const vector<int>& vec, int value, int& comparison) {
	int left = 0;
	int right = vec.size() - 1;
	while (left <= right) {
		++comparison;
		int mid = left + (right - left) / 2;
		if (vec[mid] == value) {
			return mid; 
		}
		if (vec[mid] < value) {
			left = mid + 1;
		}
		else {
			right = mid - 1; 
		}
	}
	return -1; 
}

int main()
{
	
	vector<int> values = {
		8284, 4663, 5670, 2284, 1197,
		9109, 6547, 7652, 7925, 2421,
		8717, 6976, 1671, 5533, 1170,
		1112, 4921, 9702, 4177, 9821,
		2454, 3211, 5594, 2417, 7294 };

	cout << "Values (Unsorted):\n";
	printVector(values); //Printing the unsorted vector

	vector<int> sortedValues = values;
	selectionSort(sortedValues);

	cout << "Values (Sorted): \n";
	printVector(sortedValues); //Printing the sorted vector

	int searchValue;
	cout << "What Value Are you searching for? \n";
	cin >> searchValue; 

	int linearComparison = 0;
	int linearIndex = linearSearch(values, searchValue, linearComparison);
	if (linearIndex == -1) {
		cout << "Linear Search:\nValue " << searchValue << " not found after "
			<< linearComparison << " comparisons.\n";
	}
	else {
		cout << "Linear Search:\nValue " << searchValue << " found at index "
			<< linearIndex << " on comparison #" << linearComparison << "\n";
	}

	// Binary search
	int binaryComparisons = 0;
	int binaryIndex = binarySearch(sortedValues, searchValue, binaryComparisons);
	if (binaryIndex == -1) {
		cout << "Binary Search:\nValue " << searchValue << " not found after "
			<< binaryComparisons << " comparisons.\n";
	}
	else {
		cout << "Binary Search:\nValue " << searchValue << " found at index "
			<< binaryIndex << " on comparison #" << binaryComparisons << "\n";
	}
	return 0; 
}


