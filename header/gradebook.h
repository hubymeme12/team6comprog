#ifndef GRADEBOOK_H
#define GRADEBOOK_H

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct studentinfo {
	string name;
	float grade;

	studentinfo* next;
	studentinfo* prev;
};

class gradebook {
	public:
		// constructors
		gradebook(string);
		gradebook();

		// function to set course name
		void setcourseName(string);
		void message();
		string getcourseName();

		// added functionalities:
		void pushdata(string, float);
		void deletedata(string);
		void deletedata(int);				
		void editname(int, string);
		void editgrade(int, float);
		int listnum();
		int largeststring(studentinfo*, int);
		float displaygrade(studentinfo*);
		string displayname(studentinfo*);
		studentinfo* getFirst();
		studentinfo* searchname(studentinfo*, string);
	private:
		string courseName;
		studentinfo* first;
		studentinfo* last;
		int linksize;
};





//////////////////////////////////
//	gradebook definition	//
//////////////////////////////////
gradebook::gradebook(string name) {
	//validate and store courseName
	setcourseName(name);
	first = NULL;
	last  = NULL;
	linksize = 0;
}

gradebook::gradebook() {
	setcourseName("");
	first = NULL;
	last  = NULL;
	linksize = 0;
}

//function member with binary scope resolution (::) to link the funtion to its class
void gradebook::setcourseName(string name) {
	//function to set the course name and ensure it has the length of 25 characters
	//if the characters is less than 25 in length
	if (name.length()<=25) {
		// store the course name in the object
		courseName = name;
	} else {
		//if grater than 25
		//set to first 25 character with parameter name and start at 0 of lenght 25
		courseName = name.substr(0, 25);
		cout << "[!!!] Course name exceeds 25 characters" << endl;
	}
}

void gradebook::message() {
	cout << "STUDENT GRADEBOOK " << getcourseName() << endl;
}


string gradebook::getcourseName() {
	//return object s course name
	return courseName;
}

// pushes the student name and student grade
void gradebook::pushdata(string name, float grade) {
	// make new node for the student detail
	studentinfo* node = new studentinfo;
	node->name = name;
	node->grade = grade;
	node->next = NULL;

	if (first == NULL) {
		first = node;
		last  = node;
		node->prev = NULL;
	} else {
		last->next = node;
		node->prev = last;
		last = node;
	}

	linksize += 1;
}

void gradebook::deletedata(string name) {
	// searches for this student and re-route the other nodes
	studentinfo* delme = searchname(first, name);

	if (delme == first) {
		// set next as the first node
		first = delme->next;

		// release the previos node
		delete delme->prev;
		delme->prev = NULL;
	} else if (delme == last) {
		// set the last as the last node
		last = delme->prev;

		// release the last node
		delete delme->next;
		delme->next = NULL;
	} else {
		delme->prev->next = delme->next;
		delme->next->prev = delme->prev;
	}
}

// edit name of student through the use of index
void gradebook::editname(int target, string newname) {
	studentinfo* node = first;

	if (target > linksize) {
		cout << "[!] Input exceeded on the number of students!" << endl;
	} else {
		for (int i = 1; i < target; i++)
			node = node->next;

		// edit the name of that student
		node->name = newname;
	}
}

// edits grade of student through the use of index
void gradebook::editgrade(int target, float newgrade) {
	studentinfo* node = first;

	if (target > linksize) {
		cout << "[!] Input exceeded on the number of studetns!" << endl;
	} else {
		for (int i = 1; i < target; i++)
			node = node->next;

		// replace the grade of student
		node->grade = newgrade;
	}
}

string gradebook::displayname(studentinfo* node) {
	return node->name;
}

float gradebook::displaygrade(studentinfo* node) {
	return node->grade;
}

int gradebook::listnum() {
	return linksize;
}

int gradebook::largeststring(studentinfo* fnode, int largest = 0) {
	if (fnode == NULL)
		return largest;

	if (fnode->name.size() > largest)
		largest = fnode->name.size();

	if (fnode->next != NULL)
		return largeststring(fnode->next, largest);
	else
		return largest;
}

studentinfo* gradebook::getFirst() { return first; }

studentinfo* gradebook::searchname(studentinfo* firstnode, string name) {
	if (firstnode->name == name)
		return firstnode;
	else
		if (firstnode->next != NULL)
			return searchname(firstnode->next, name);
		else
			return NULL;
}
#endif
