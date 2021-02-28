#ifndef LINKEDLIST_H
#define LINKEDLIST_H

// A doubly linked list made by Hubert for:
//	storing dynamic teacher-student credentials
//	storing gradebook with dynamic size
// end

#include <iostream>
#include "gradebook.h"
using namespace std;

struct gnode {
	gradebook* value;

	gnode* next;
	gnode* prev;
};

struct creds {
	string name;
	string user;
	string pass;

	creds* next;
	creds* prev;
};


class gradebooklist {
	public:
		// constructors
		gradebooklist();
		gradebooklist(gradebook* value);			// use this value as first value

		// utilities
		gnode* getFirst() const;					// gets the first node address
		void pushBack(gradebook*);			// pushes this value to the last list
		void remove(gnode*, gradebook*);		// removes this gradebook address from the list
		void countMatchedData(gnode*, string);	// counts how many name has matched on the gradebook list (stored in arrsize)
		bool matchData(gnode*, string);		// returns true if the gradebook has matched student id
		string displaysubject(gnode*) const;			// display subject of the node
		gradebook* access(int) const;				// access the nth gradebook

		// debug
		void printValues(gnode*);				// prints all content from first to last
		void printAddress(gnode*);			// prints all address from first to last
		int listnum();					// number of nodes present
		int largeststring(gnode*, int);			// calculates the number of largest string (subject name)
		int numberMatch();
	private:
		gnode* first;
		gnode* last;
		int linksize;

		gradebook* arr;
		int arrsize;
};


class credential {
	public:
		// constructor
		credential();
		credential(string, string, string);			// first node with username and password

		// utilities
		creds* getFirst() const;				// gets the first node address
		creds* findFirst(creds&);				// finds the first node of a "lost node"
		creds* search(creds*, string);				// op function that searches for matched data and returns that node with matched data
		creds* searchname(creds*, string);			// op function that searches for name and return the node
		creds* getNode(int);					// get nth node
		string printName(creds*);
		string printUser(creds*);
		string printPass(creds*);
		void add(string, string, string);			// pushes these values to the last list
		void remove(creds*, string);				// removes this gradebook address from the list
		void remove(int);					// removes the nth node from the list
		bool matchData(creds*, string, string);			// returns true if the gradebook has matched student id
		int longestfuckingname(creds*, int);			// returns the size of the longest fucking name
		int longestfuckingpass(creds*, int);
		int longestfuckinguser(creds*, int);
		int getlistnum();					// returns the number of lists

		// debugging
		void printData(creds*);
	private:
		creds* first;
		creds* last;
		int linksize;
};

struct triad {
	gradebook* subject;
	string teacher;
	credential* students;

	triad* next;
	triad* prev;
};

class tridata {
	public:
		tridata();

		// data manipulation
		void addData(gradebook*, string, string*, int, creds*);
		void addData(gradebook*, string, credential*);
		void removeSubject(string);
		void removeStudent(string);

		// tools
		void retrieveTnodes(tridata*, string);
		void retrieveSnodes(tridata*, string);

		// utilities
		triad* getFirst();
		void getlongestfuckingstring(int&, int&, int&);
	private:
		triad* first;
		triad* last;
		int linksize;
		int longestfuckingstring;
};

//////////////////////////////////
//	tridata definition	//
//////////////////////////////////
tridata::tridata() {
	first = NULL;
	last  = NULL;
	linksize = 0;
}

void tridata::addData(gradebook* subject, string teacherUsername, string* namesArray, int size, creds* studentlist) {
	credential *cute = new credential;
	triad* tnode = new triad;
	creds *node;

	// push this data to the last
	// checks for the first null
	for (int i = 0; i < size; i++) {
		node = cute->search(studentlist, namesArray[i]);
		cute->add(node->user, node->name, node->pass);
	}

	// assign values to triad
	tnode->subject = subject;
	tnode->teacher = teacherUsername;
	tnode->students = cute;

	if (first == NULL) {
		first = tnode;
		last = tnode;
	} else {
		last->next = tnode;
		tnode->prev = last;
		tnode->next = NULL;

		last = tnode;
	}

	// increment link size
	linksize += 1;
}

void tridata::addData(gradebook* subj, string tname, credential* studdata) {
	// make new node
	triad* node = new triad;

	// assign values
	node->subject = subj;
	node->teacher = tname;
	node->students = studdata;
	node->next = NULL;

	// push value:
	if (first == NULL) {
		first = node;
		last  = node;
	} else {
		last->next = node;
		node->prev = last;
		last = node;
	}

	// increment size
	linksize += 1;
}

// returns first node
triad* tridata::getFirst() {
	return first;
}

// assign their fucking values
void tridata::getlongestfuckingstring(int &subject, int &teacher, int &students) {
	int longest = 0;
	int currsize;
	triad* fuck = first;

	// crawl all subjects
	while (fuck != NULL) {
		currsize = fuck->subject->getcourseName().size();
		longest = longest * (longest > currsize) + currsize * (currsize >= longest);
		fuck = fuck->next;
	}

	subject = longest;
	longest = 0;
	fuck = first;

	// crawl all students
	while (fuck != NULL) {
		longest = fuck->subject->largeststring(fuck->subject->getFirst(), 0);
		fuck = fuck->next;
	}
	students = longest;
	longest = 0;
	fuck = first;

	// crawl all teachers
	while (fuck != NULL) {
		currsize = fuck->teacher.size();
		longest = longest * (longest > currsize) + currsize * (currsize >= longest);
		fuck = fuck->next;
	}
}

// retrieves all nodes with matched teacher name
void tridata::retrieveTnodes(tridata* storage, string name) {
	if (storage == NULL) {
		cout << "[!] Use tridata object address! not null pointer!" << endl;
	} else {
		// crawl the node from the first and push the data to storage
		triad* pseudonode = first;

		// matches the teacher name
		while (pseudonode != NULL) {
			// look for the teacher name
			if (pseudonode->teacher == name) {
				// push to the storage
				storage->addData(pseudonode->subject, pseudonode->teacher, pseudonode->students);
			}
		}
	}
}

// retrieve all nodes with matched student
void tridata::retrieveSnodes(tridata* storage, string name) {
	if (storage == NULL) {
		cout << "[!] Use tridata object address! not null pointer!" << endl;
	} else {
		triad* pseudonode = first;

		while (pseudonode != NULL) {
			// crawl to the node's credential (match the student name)
			if(pseudonode->students->searchname(pseudonode->students->getFirst(), name) != NULL) {
				storage->addData(pseudonode->subject, pseudonode->teacher, pseudonode->students);
			}
		}
	}
}

//////////////////
//	END	//
//////////////////


//////////////////////////////////
//	credential definition	//
//////////////////////////////////
// default constructor
credential::credential() {
	first = NULL;
	last = NULL;
	linksize = 0;
}

// parametric constructor for assigning first node
credential::credential(string username, string name, string password) {
	// initialize node.
	creds *node = new creds;
	node->user = username;
	node->pass = password;
	node->name = name;

	// assign next and prev as NULL, since it is the first node
	node->next = NULL;
	node->prev = NULL;

	// assign as first and last node
	first = node;
	last  = node;

	// increment linksize
	linksize = 1;
}

// returns the first node for keeping in track
creds* credential::getFirst() const { return first; }


// searches for the matched username of the student
creds* credential::search(creds* firstnode, string username) {
	if (firstnode->user == username)
		return firstnode;
	else
		if (firstnode->next != NULL)
			return search(firstnode->next, username);
		else
			return NULL;
}

// searches for the matched name
creds* credential::searchname(creds* firstnode, string name) {
	if (firstnode->name == name)
		return firstnode;
	else
		if (firstnode->next!= NULL)
			return searchname(firstnode->next, name);
		else
			return NULL;
}

creds* credential::getNode(int index) {
	// limiter
	if (index > linksize) {
		cout << "[!] Error! input value is not valid!" << endl;
		return NULL;
	} else {
		creds* node = first;
		for (int i = 1; i < index; i++) {
			node = node->next;
		}

		return node;
	}
}

// for table printing
string credential::printName(creds* address) { return address->name; }
string credential::printUser(creds* address) { return address->user; }
string credential::printPass(creds* address) { return address->pass; }

// pushback this credential node to last node
void credential::add(string username, string name, string password) {
	// makes new node and assign values
	creds *node = new creds;
	node->user = username;
	node->name = name;
	node->pass = password;

	// if there's no first and last, assign this as first node
	if (first == NULL && last == NULL) {
		first = node;
		last  = node;
	} else {
		// push to the last node
		last->next = node;
		node->prev = last;
		node->next = NULL;

		// assign as last node
		last = node;
	}

	// increment size
	linksize += 1;
}

// checks for username of the student (unique) so this node can be deleted
void credential::remove(creds* firstnode, string username) {
	if (firstnode->user == username) {
		// reroute node
		if (firstnode == first) {
			first = first->next;
			first->prev = NULL;
		} else if (firstnode == last) {
			last = last->prev;
			last->next = NULL;
		} else {
			firstnode->prev->next = firstnode->next;
			firstnode->next->prev = firstnode->prev;
		}
	} else {
		if (firstnode->next != NULL) {
			remove(firstnode->next, username);
		}
	}

	// decrement link size
	linksize -= 1;
}

void credential::remove(int index) {
	if (index > linksize) {
		cout << "[-] The number you input exceeded the link size." << endl;
	} else {
		creds* node = first;
		for (int i = 1; i < index; i++) {
			node = node->next;
		}

		// re-route this node
		if (node == first) {
			// somehow release its value here to avoid memory leak lol
			first = node->next;
			first->prev = NULL;
		} else if (node == last) {
			last = node->prev;
			last->next = NULL;
		} else {
			// ultra mega rerouttteee
			node->next->prev = node->prev;
			node->prev->next = node->next;
		}
	}

	linksize -= 1;
}

bool credential::matchData(creds* firstnode, string username, string password) {
	// search for username before matching to password
	if (firstnode->user == username) {
		if (firstnode->pass == password) {
			// permission to retrieve username
			// retrieve username
			return 1;
		} else {
			return 0;
		}
	} else {
		if (firstnode->next != NULL)
			return matchData(firstnode->next, username, password);
	}

	return 0;
}

int credential::longestfuckingname(creds* fnode, int longest = 0) {
	if (fnode == NULL)
		return longest;

	if (fnode->name.size() > longest)
		longest = fnode->name.size();

	if (fnode->next != NULL)
		return longestfuckingname(fnode->next, longest);
	else
		return longest;
}

int credential::longestfuckinguser(creds* fnode, int longest = 0) {
	if (fnode == NULL)
		return longest;

	if (fnode->user.size() > longest)
		longest = fnode->user.size();

	if (fnode->next != NULL)
		return longestfuckinguser(fnode->next, longest);
	else
		return longest;
}

int credential::longestfuckingpass(creds* fnode, int longest = 0) {
	if (fnode == NULL)
		return longest;

	if (fnode->pass.size() > longest)
		longest = fnode->pass.size();

	if (fnode->next != NULL)
		return longestfuckingpass(fnode->next, longest);
	else
		return longest;
}


int credential::getlistnum() { return linksize; }

void credential::printData(creds* first) {
	if (first->next == NULL)
		cout << "| " << first->user << " | " << first->name << " | " << first->pass << " |" << endl;
	else {
		cout << "| " << first->user << " | " << first->name << " | " << first->pass << " |" << endl;
		printData(first->next);
	}
}

///////////////////////////////////////////
//	gradebook list definition	//
//////////////////////////////////////////
// default constructor definition
gradebooklist::gradebooklist() {
	first = NULL;
	last = NULL;
	linksize = 0;
}

// parametric constructor
// pass this value as the first node
gradebooklist::gradebooklist(gradebook* value) {
        // create new node and assign this value.
	gnode *node = new gnode;
	node->value = value;

        // assign the next and previous of the node
	node->next = NULL;
	node->prev = NULL;

        // make this node as the first and last node
	first = node;
	last  = node;

	// increment link size
	linksize = 1;
}

// returns the first address
gnode* gradebooklist::getFirst() const {
	return first;
}

// pushbacks value to the list
void gradebooklist::pushBack(gradebook* value) {
	// make a new node and assign the value
	gnode *node = new gnode;
	node->value = value;
	node->next = NULL;

	// check if there's no last yet (meaning : no node has been added yet)
	if (last != NULL) {
		// connect this node to the last node
		node->prev = last;
		last->next = node;

		// since new node is added, this node will become the last node
		last = node;

		// increment linklist size
		linksize += 1;
	} else {
		// push back this value to the last node
		first = node;
		last = node;

		// first node so, one node
		linksize = 1;
	}
}

// removes value from the list
void gradebooklist::remove(gnode* node, gradebook* address) {
	if (node->value == address) {
		// obsessively checks for null
		if (first == node) {
			delete node->value;
			first = node->next;
			first->prev = NULL;
		} else {
			node->prev->next = node->next;
			node->next->prev = node->prev;
		}
	} else {
		if (node->next != NULL)
			remove(node->next, address);
		// else it isn't in the list
	}

	// decrement link size
	linksize -= 1;
}

// check if name is registered in the value of this node
bool gradebooklist::matchData(gnode* node, string name) {
	// searches this student name
	// the function returns NULL if the student isnt found
	if (node->value->searchname(node->value->getFirst(), name) == NULL)
		return false;
	else
		return true;
}

// counts how many subjects have this student name
void gradebooklist::countMatchedData(gnode* node, string name) {
	if (node == first)
		arrsize = 0;

	if (matchData(node, name))
		arrsize++;

	if (node->next != NULL)
		countMatchedData(node->next, name);
}

string gradebooklist::displaysubject(gnode* node) const {
	return node->value->getcourseName();
}

gradebook* gradebooklist::access(int index) const {
	if (index > linksize) {
		cout << "[!] Error, size exceeded!" << endl;
		return NULL;
	} else {
		gnode* node = first;

		// crawl up to index th node
		for (int i = 1; i < index; i++) {
			node = node->next;
		}

		return node->value;
	}
}

// prints all values
void gradebooklist::printValues(gnode* node) {
	if (node->next != NULL) {
		cout << " | " << node->value->getcourseName();
		printValues(node->next);
	} else {
		cout << " | " << node->value->getcourseName() << " |" << endl;
	}
}

// prints all values
void gradebooklist::printAddress(gnode* node) {
	if (node->next != NULL) {
		cout << " | " << node;
		printAddress(node->next);
	} else {
		cout << " | " << node << " |" << endl;
	}
}

// get the number of nodes present
int gradebooklist::listnum() {
	return linksize;
}

int gradebooklist::largeststring(gnode* fnode, int largest = 0) {
	if (fnode == NULL)
		return 8;

	if (fnode->value->getcourseName().size() > largest) {
		largest = fnode->value->getcourseName().size();
	}

	if (fnode->next == NULL)
		return largest;
	else
		return largeststring(fnode->next, largest);
}

int gradebooklist::numberMatch() {
	return arrsize;
}
#endif
