// DynaBird_Project_Colehower.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

const string GREEN = "\033[32m";   // Correct position
const string YELLOW = "\033[33m";  // Wrong position
const string RED = "\033[31m";     // Not in the word
const string RESET = "\033[0m";    // Reset color

void bubbleSort(string* arr, int size);
vector<string> readWordsFromFile(const string& filename);
void playGame(const vector<string>& wordList, int wordLength);
void displayWordState(const string& wordToGuess, const vector<char>& guessedLetters, const vector<char>& notInWord);
bool isGuessValid(const string& guess, int expectedLength);
void processGuess(const string& guess, const string& wordToGuess, vector<char>& guessedLetters, vector<char>& notInWord);

int main() {
    string filename;
    cout << "Enter the name of the input text file: ";
    cin >> filename;

    vector<string> wordList = readWordsFromFile(filename);
    if (wordList.empty()) {
        cout << "No words found in the file." << endl;
        return 1;
    }
    int size = wordList.size();
    bubbleSort(wordList.data(), size);

    int maxWordLength = 0;
    for (const string& word : wordList) {
        if (word.length() > maxWordLength) {
            maxWordLength = word.length();
        }
    }

    int wordLength;
    do {
        cout << "Enter the integer length of the word you'd like to guess (up to " << maxWordLength << "): ";
        cin >> wordLength;
    } while (wordLength < 1 || wordLength > maxWordLength);

    vector<string> filteredWords;
    for (const string& word : wordList) {
        if (word.length() == wordLength) {
            filteredWords.push_back(word);
        }
    }

    srand(static_cast<unsigned int>(time(0)));
    string wordToGuess = filteredWords[rand() % filteredWords.size()];

    playGame(filteredWords, wordLength);

    return 0;
}


void bubbleSort(string* arr, int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

vector<string> readWordsFromFile(const string& filename) {
    ifstream file(filename);
    vector<string> words;
    string word;

    while (file >> word) {
        words.push_back(word);
    }

    return words;
}

void playGame(const vector<string>& wordList, int wordLength) {
    string wordToGuess = wordList[rand() % wordList.size()];
    vector<char> guessedLetters;
    vector<char> notInWord;
    int rounds = 0;

    while (true) {
        rounds++;
        string guess;

        displayWordState(wordToGuess, guessedLetters, notInWord);
        cout << "Guess #" << rounds << ": ";
        cin >> guess;

        while (!isGuessValid(guess, wordLength)) {
            cout << "That number is too big. Try again: ";
            cin >> guess;
        }

        processGuess(guess, wordToGuess, guessedLetters, notInWord);

        if (guess == wordToGuess) {
            cout << "Congratulations! You've guessed the word: " << wordToGuess << endl;
            cout << "Total guesses: " << rounds << endl;
            break;
        }
    }
}

void displayWordState(const string& wordToGuess, const vector<char>& guessedLetters, const vector<char>& notInWord) {
    cout << "\nLetters Not Included: ";
    for (char ch : notInWord) {
        cout << RED << ch << " " << RESET;
    }
    cout << endl;

    for (size_t i = 0; i < wordToGuess.length(); ++i) {
        char ch = wordToGuess[i];
        if (find(guessedLetters.begin(), guessedLetters.end(), ch) != guessedLetters.end()) {
            cout << "_ ";  
        }
        else {
            cout << "_ ";  
        }
    }
    cout << endl;
}

bool isGuessValid(const string& guess, int expectedLength) {
    return guess.length() == expectedLength;
}

void processGuess(const string& guess, const string& wordToGuess, vector<char>& guessedLetters, vector<char>& notInWord) {
    for (char ch : guess) {
        if (find(guessedLetters.begin(), guessedLetters.end(), ch) == guessedLetters.end()) {
            guessedLetters.push_back(ch);
        }
    }

    vector<bool> matched(wordToGuess.length(), false);

    for (size_t i = 0; i < guess.length(); ++i) {
        if (guess[i] == wordToGuess[i]) {
            cout << GREEN << guess[i] << " " << RESET;  
            matched[i] = true;  
        }
        else {
            cout << "_ ";  
        }
    }
    for (size_t i = 0; i < guess.length(); ++i) {
        if (!matched[i] && wordToGuess.find(guess[i]) != string::npos) {
            cout << YELLOW << guess[i] << " " << RESET;  
        }
        else if (!matched[i]) {
            if (find(notInWord.begin(), notInWord.end(), guess[i]) == notInWord.end()) {
                notInWord.push_back(guess[i]); 
            }
            cout << RED << guess[i] << " " << RESET;  
        }
    }
    cout << endl;
}

