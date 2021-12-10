#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

/*
* Created by: Devin Hunter
* Date: 12/6/2021
* SNHU CS-300
* Professor Sanford
**/

// Here is my Course object
struct Course {
    string courseID;
    string courseName;
    string courseNum;
    vector<string> prereqs;
    Course() {
        courseID = -1;
        courseName = "";
    }
};


// This will be the initial size of the nodes vector
const unsigned int DEFAULT_SIZE = 17;


class AdvisingHashTable {
private:

    // Define structures to hold courses
    struct Node {
        Course course;
        unsigned int key;
        Node* next;

        // Default constructor
        Node() {
            key = UINT_MAX;
            next = nullptr;
        }

        // Initialize with a course
        Node(Course aCourse) : Node() {
            course = aCourse;
        }

        // Initialize with a course and a key
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
    void printAll();
    Course Search(AdvisingHashTable* hashTable, string courseID);
};



class CSVReader {
private:
    int numPrereqs;

public:
    void readAndParse(AdvisingHashTable* hashTable);
    vector<Course> courses;
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

        // Inserting the node we just created into the nodes vector
        nodes.insert(nodes.begin() + key, (*newNode));
    }
    // If a node is found...
    else {

        // If the key for the node has not been used, assign oldNode (the node we found that is already in the vector) with the key, the course, and then point to null
        if (oldNode->key == UINT_MAX) {
            oldNode->key = key;
            oldNode->course = course;
            oldNode->next = nullptr;
        }
        // If the key for the node has been used by at least one node...
        else {

            // This while loop keeps iterating through until it finds an open space
            while (oldNode->next != nullptr) {

                // This jumps to the next node if the node we're looking at is not null
                oldNode = oldNode->next;
            }
            // When we find an empty node, we assign the course
            oldNode->next = new Node(course, key);
        }
    }
}




// Needed to make this function inline to bypass fatal error LNK1169
inline void CSVReader::readAndParse(AdvisingHashTable* hashTable) {

    // Here I create a vector to temporarily store each row of the csv file
    vector<string> row;

    // I declare an object with function ifstream to be able open the csv file
    ifstream fileInput;

    // I create a string called line to temporarily store a line of the csv file
    string line;

    // Now I open the file
    fileInput.open("CourseList.csv");

    // This while loop reads each line of the file until it ends
    while (!fileInput.eof()) {
        row.clear();

        // Here I get a line from the csv file
        getline(fileInput, line);

        stringstream ss(line);
        numPrereqs = 0;

        // Then I split the line from the csv file at the commas and push each part to a vector for temporary holding
        while (ss.good()) {
            string substr;
            getline(ss, substr, ',');
            row.push_back(substr);

            if (row.size() > 2) {
                numPrereqs++;
            }
            else if (row.size() > 3) {
                numPrereqs++;
            }
        }

        // Now I create a new course and fill in the new course's course ID, course number (which I'll turn into a key later with my hash function), and course name from the vector
        Course newCourse;
        newCourse.courseID = row.at(0);
        newCourse.courseName = row.at(1);
        newCourse.courseNum = row.at(0).erase(0, 4);

        // These if statements add the prereqs for the new course to that course's prereqs vector
        if (numPrereqs == 0) {

        }
        else if (numPrereqs == 1) {
            newCourse.prereqs.push_back(row.at(2));

        }
        else if (numPrereqs == 2) {
            newCourse.prereqs.push_back(row.at(2));
            newCourse.prereqs.push_back(row.at(3));
        }

        // Now I add the new course to the courses vector
        courses.push_back(newCourse);

        // For loop wich inserts each course into the hash table from the courses vector
        for (unsigned int i = 0; i < courses.size(); i++) {
            hashTable->insertCourse(courses.at(i));
        }

    }

    // Now I close the file
    fileInput.close();
}



/**
 * Search for the specified courseID
 */
Course AdvisingHashTable::Search(AdvisingHashTable* hashTable, string courseID) {
    Course course;

    // I cut off all of the non-numerical characters in the courseID so I can apply my hash fucntion
    string courseNum = courseID.erase(0, 4);

    // Here we calculate the key for the given course by applying the hash function to the courseNum
    unsigned key = hash(atoi(courseNum.c_str()));

    // Here we use the key we calculated to retrieve the node
    Node* node = &(nodes.at(key));

    // If the node is not empty, and it is not a new unused node, and if the node's courseNum matches the one we passed in, return that node's course
    if (node != nullptr && node->key != UINT_MAX && node->course.courseNum.compare(courseNum) == 0) {

        // This block of code prints out all of the course info if the courseNum of the course within the node matches the one we passed in
        cout << hashTable->nodes.at(key).course.courseID << ": " << hashTable->nodes.at(key).course.courseName << endl;
        cout << "Prerequisites: ";
        if (hashTable->nodes.at(key).course.prereqs.size() < 1) {
            cout << "None" << endl;
        }
        else if (hashTable->nodes.at(key).course.prereqs.size() == 1) {
            cout << hashTable->nodes.at(key).course.prereqs.at(0) << endl;
        }
        else if (hashTable->nodes.at(key).course.prereqs.size() == 2) {
            cout << hashTable->nodes.at(key).course.prereqs.at(0) << ", " << hashTable->nodes.at(key).course.prereqs.at(1) << endl;
        }
        cout << endl;

        return node->course;
    }

    // If there is no node or the node is empty, then return the empty course
    if (node == nullptr || node->key == UINT_MAX) {
        cout << "Please input a valid course ID." << endl;
        cout << endl;
        return course;
    }

    // While the node is not empty...
    while (node != nullptr) {

        // If the key is not empty and it matches then we return the node's course
        if (node->key != UINT_MAX && node->course.courseNum.compare(courseNum) == 0) {
            cout << "Match found!";

            // This block of code prints out all of the course info if the courseNum matches the one we passed in
            cout << hashTable->nodes.at(key).course.courseID << ": " << hashTable->nodes.at(key).course.courseName << endl;
            cout << "Prerequisites: ";
            if (hashTable->nodes.at(key).course.prereqs.size() < 1) {
                cout << "None" << endl;
            }
            else if (hashTable->nodes.at(key).course.prereqs.size() == 1) {
                cout << hashTable->nodes.at(key).course.prereqs.at(0) << endl;
            }
            else if (hashTable->nodes.at(key).course.prereqs.size() == 2) {
                cout << hashTable->nodes.at(key).course.prereqs.at(0) << ", " << hashTable->nodes.at(key).course.prereqs.at(1) << endl;
            }
            cout << endl;

            return node->course;
        }

        // Otherwise we move on and continue searching
        node = node->next;
    }

    // If we haven't returned a matching node then we return and empty course
    cout << "No Match Found!" << endl;
    cout << endl;
    return course;
}




// This function displays a course's info
void displayCourse(Course course) {

    cout << course.courseID << ": " << course.courseName << endl;
    cout << "Prerequisites: ";
    if (course.prereqs.size() < 1) {
        cout << "None" << endl;
    }
    else if (course.prereqs.size() == 1) {
        cout << course.prereqs.at(0) << endl;
    }
    else if (course.prereqs.size() == 2) {
        cout << course.prereqs.at(0) << ", " << course.prereqs.at(1) << endl;
    }
    cout << endl;
}




/**
 * Print all courses
 */
void AdvisingHashTable::printAll() {

    // For loop which loops through the nodes vector  
    for (unsigned int i = 0; i < nodes.size(); i++) {

        // If key not equal to UINT_MAX
        if (nodes.at(i).key != UINT_MAX) {

            // Print course info
            displayCourse(nodes.at(i).course);
        }
    }
}




// This function gets user input and calls the appropriate function
void AdvisingHashTable::optionSelector() {

    // Local variables which store input from user to be used below
    string userID;
    int userInput;

    cout << "What would you like to do ? ";
    cin >> userInput;
    cout << endl;

    // Originally I used a switch statement instead of this while loop but these if/esle statements were simpler for me
    while (userInput != 3) {

        AdvisingHashTable* myHashTable;
        CSVReader reader;

        if (userInput == 1) {
            myHashTable = new AdvisingHashTable;
            reader.readAndParse(myHashTable);

            cout << "Courses loaded." << endl;
            cout << endl;
            myHashTable->printAll();
            
            cout << "Main Menu:" << endl;
            cout << endl;
            cout << "1. Load and Display Course Info." << endl;;
            cout << "2. Find Specific Course Info." << endl;
            cout << "3. Exit" << endl;
            cout << endl;

            cout << "What would you like to do ? ";
            cin >> userInput;
            cout << endl;
            if (userInput == 3) {
                break;
            }
        }
        else if (userInput == 2) {
            myHashTable = new AdvisingHashTable;
            reader.readAndParse(myHashTable);

            cout << "Please enter the coure ID: ";
            cin >> userID;
            cout << endl;

            myHashTable->Search(myHashTable, userID);
            
            cout << "Main Menu:" << endl;
            cout << endl;
            cout << "1. Load and Display Course Info." << endl;;
            cout << "2. Find Specific Course Info." << endl;
            cout << "3. Exit" << endl;
            cout << endl;

            cout << "What would you like to do ? ";
            cin >> userInput;
            cout << endl;
            if (userInput == 3) {
                break;
            }
        }
        else if (userInput > 3 || userInput < 1) {
            cout << "Please enter a valid menu input." << endl;
            cout << endl;

            cout << "Main Menu:" << endl;
            cout << endl;
            cout << "1. Load and Display Course Info." << endl;;
            cout << "2. Find Specific Course Info." << endl;
            cout << "3. Exit" << endl;
            cout << endl;

            cout << "What would you like to do ? ";
            cin >> userInput;
            cout << endl;
            if (userInput == 3) {
                break;
            }
        }
        else {
            break;
        }
    }
    
}



// This function simply displays the menu options
void AdvisingHashTable::displayMenu() {
    cout << endl;
    cout << "Main Menu:" << endl;
    cout << endl;
    cout << "1. Load and Display Course Info." << endl;;
    cout << "2. Find Specific Course Info." << endl;
    cout << "3. Exit" << endl;
    cout << endl;
    optionSelector();
}



int main()
{
    AdvisingHashTable program;

    cout << endl;
    cout << "Welcome to the course planner." << endl;

    program.displayMenu();

    return 0;
}
