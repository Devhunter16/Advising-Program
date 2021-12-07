#include "CSVReader.cpp"
#include <iostream>
using namespace std;

/*
* Created by: Devin Hunter
* Date: 12/6/2021
* SNHU CS-300
* Professor Sanford
**/

class AdvisingHashTable {
private:
    void optionSelector();

public:
    void displayMenu();
};

// This function simply displays the menu options
void AdvisingHashTable::displayMenu() {
    cout << endl;
    cout << "1. Load Data Structure." << endl;;
    cout << "2. Print Full Course List." << endl;
    cout << "3. Find Course Info." << endl;
    cout << "4. Exit" << endl;
    cout << endl;
    optionSelector();
}

// This function gets user input and calls the appropriate function
void AdvisingHashTable::optionSelector() {

    // Local variable which stores input from user to be used in switch statement
    int userInput;

    cout << "What would you like to do ? ";
    cin >> userInput;
    cout << endl;

    CSVReader reader;

    switch(userInput) {
    case 1 :
        // FIXME LOAD DATA STRUCTURE
        cout << "Not done yet." << endl;
        break;
    case 2 :
        // FIXME SORT AND PRINT FULL COURSE LIST
        reader.readAndParse();
        cout << "end";
        break;
    case 3 :
        // FIXME FIND AND PRINT COURS INFO
        cout << "Not done yet." << endl;
        break;
    case 4 :
        cout << "Goodbye!" << endl;
        break;
    }

}

int main()
{
    AdvisingHashTable program;

    cout << endl;
    cout << "Welcome to the course planner." << endl;

    program.displayMenu();
    return 0;
}

