#include "CSVReader.cpp"
#include <iostream>
using namespace std;

/*
* Created by: Devin Hunter
* Date: 12/6/2021
* SNHU CS-300
* Professor Sanford
**/

const unsigned int DEFAULT_SIZE = 9;

class AdvisingHashTable {
private:

    // Define structures to hold courses
    struct Node {
        Course course;
        unsigned int key;
        Node* next;

        // default constructor
        Node() {
            key = UINT_MAX;
            next = nullptr;
        }

        // initialize with a course
        Node(Course aCourse) : Node() {
            course = aCourse;
        }

        // initialize with a course and a key
        Node(Course aCourse, unsigned int aKey) : Node(aCourse) {
            key = aKey;
        }
    };

    vector<Node> nodes;
    unsigned int tableSize = DEFAULT_SIZE;
    unsigned int hash(int key);
    void optionSelector();

public:
    AdvisingHashTable();
    AdvisingHashTable(unsigned int size);
    virtual ~AdvisingHashTable();
    void insertCourse(Course course);
    void displayMenu();
};


/**
 * Default constructor
 */
AdvisingHashTable::AdvisingHashTable() {

    // Initalize node structure by resizing tableSize
    nodes.resize(tableSize);
}


// This constructor function updates the tableSize variable
AdvisingHashTable::AdvisingHashTable(unsigned int size) {
    this->tableSize = size;
}


// This is a destructor function
AdvisingHashTable::~AdvisingHashTable() {

    // This erases an element from the nodes vector and frees storage;
    nodes.erase(nodes.begin());
}


unsigned int AdvisingHashTable::hash(int key) {

    // This line of code includes logic to calculate a hash value 
    return key % tableSize;
}


void AdvisingHashTable::insertCourse(Course course) {

    // This line of code gets the courseNum, converts it to a c-style string, then turns the string into an integer, then uses the hash function to turn it into a key
    unsigned key = hash(atoi(course.courseNum.c_str()));

    // Here we are searching to see if there is a node at the key position
    Node* oldNode = &(nodes.at(key));

    // If no entry is found for the key, creates a node and assigns this node to the key position
    if (oldNode == nullptr) {
        Node* newNode = new Node(course, key);

        // Inserting the node we just created into nodes vector
        nodes.insert(nodes.begin() + key, (*newNode));
    }

    // If a node is found...
    else {

        // if the key for the node has not been used, assign oldNode (the node we found that is already in the vector) with the key, the bid, and then point to null, rather than any other nodes. 
        if (oldNode->key == UINT_MAX) {
            oldNode->key = key;
            oldNode->course = course;
            oldNode->next = nullptr;
        }

        // if the key for the node has been used by at least one node...
        else {

            // this while loop keeps iterating through until it finds an open space
            while (oldNode->next != nullptr) {

                // this jumps to the next node if the node we're looking at is not null
                oldNode = oldNode->next;
            }

            // when we find an empty node, we assign the bid
            oldNode->next = new Node(course, key);
        }
    }
}


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
        cout << "the end";
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


//void loadCourses(vector<Course> courses, AdvisingHashTable* hashTable) {
    //CSVReader reader;

    // For loop wich inserts each course into the hash table
    //for (unsigned int i = 0; i < courses.size(); i++) {
        //hashTable->insertCourse(courses.at(i));
    //}

//}


int main()
{
    AdvisingHashTable program;

    cout << endl;
    cout << "Welcome to the course planner." << endl;

    program.displayMenu();

    return 0;
}
