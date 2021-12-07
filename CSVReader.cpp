#include "CSVReader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

// This is the course object which stores all of the course information
struct Course {
	string courseNumber;
	string courseName;
	vector<string> prereqs;
	Course() {
		courseNumber = -1;
		courseName = "";
	}
};

// Needed to make this function inline to bypass fatal error LNK1169
inline void CSVReader::readAndParse() {

	// Here I create a vector to temporarily store each row of the csv file
	vector <string> row;

	// I declare an object with function ifstream to be able open the csv file
	ifstream fileInput;

	// I create a string called line to temporarily store each line of the csv file in
	string line;
	
	// Now I open the file
	fileInput.open("CourseList.csv");

	// This while loop reads each line of the file until it ends
	while (!fileInput.eof()) {
		row.clear();

		// Here I get a line from the csv file
		getline(fileInput, line);

		cout << endl;
		cout << line << endl;
		cout << endl;

		stringstream ss(line);
		numPrereqs = 0;

		// Here I split the line from the csv file at the commas and push each part to a vector for temporary holding
		while(ss.good()) {
			string substr;
			getline(ss, substr, ',');
			row.push_back(substr);
			if (row.size() > 2) {
				numPrereqs++;
			}
		}

		// Now I create a new course and fill in the new course's course number and course name from the vector
		Course newCourse;
		newCourse.courseNumber = row.at(0);
		newCourse.courseName = row.at(1);

		cout << newCourse.courseNumber << endl;
		cout << newCourse.courseName << endl;

		// These if statements add the prereqs for the new course to that course's prereqs vector
		if (numPrereqs == 1) {
			newCourse.prereqs.push_back(row.at(2));
		}
		if (numPrereqs == 2) {
			newCourse.prereqs.push_back(row.at(3));
		}

		// This is just so I know I'm reading lines and storing them properly
		for (int i = 0; i < newCourse.prereqs.size(); i++) {
			cout << newCourse.prereqs.at(i) << endl;
		}

		cout << endl;

	}

	// Now I close the file
	fileInput.close();
}