// HW6_ColehowerLuke.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <map>
#include <string>

using namespace std;
// States class 
class State {
private:
    string name;
    string abbreviation;
    string capital;
    string population;
    string area;

public:
    State() : name(""), abbreviation(""), capital(""), population(""), area("") {}
    State(string name, string abbreviation, string capital, string population, string area)
        : name(name), abbreviation(abbreviation), capital(capital), population(population), area(area) {}
    string getName() const {
        return name;
    }

    string getAbbreviation() const {
        return abbreviation;
    }

    string getCapital() const {
        return capital;
    }

    string getPopulation() const {
        return population;
    }

    string getArea() const {
        return area;
    }
};

int main() {
    map<string, State> statesMap;
    string filename;

    cout << "Enter name of input file: ";
    cin >> filename;
    cout << "Opening input file..." << endl;

    ifstream inputFile(filename);
    if (!inputFile) {
        cerr << "Error: File could not be opened." << endl;
        return 1;
    }

    cout << "Storing values to map..." << endl;
    string line;

    while (getline(inputFile, line)) {
        string name = line;
        string abbreviation;
        string capital;
        string population;
        string area;

        getline(inputFile, abbreviation);
        getline(inputFile, capital);
        getline(inputFile, population);
        getline(inputFile, area);

        // Create a State object and store it in the map
        statesMap[abbreviation] = State(name, abbreviation, capital, population, area);
    }

    inputFile.close();
    cout << "Done reading values from input file." << endl;

    string userInput;
    while (true) {
        cout << "Enter State Abbreviation, Q to Quit: ";
        cin >> userInput;

        if (userInput == "Q" || userInput == "q") {
            break;
        }

        auto it = statesMap.find(userInput);
        if (it != statesMap.end()) {
            const State& state = it->second;
            cout << "Name: " << state.getName() << endl;
            cout << "Abbreviation: " << state.getAbbreviation() << endl;
            cout << "Capital: " << state.getCapital() << endl;
            cout << "Population: " << state.getPopulation() << endl;
            cout << "Area (Sq Miles): " << state.getArea() << endl;
        }
        else {
            cout << "State not found." << endl;
        }
    }

    return 0;
}

