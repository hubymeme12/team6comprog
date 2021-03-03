#ifndef TABLES_H
#define TABLES_H

#include <iostream>
using namespace std;

#include "linkedlist.h"
#include "gradebook.h"
#include "authentication.h"


//////////////////////////////////
// 	GLOBAL UTILITIES	//
//////////////////////////////////
class gutilities {
	friend string strmultiply(string str, int howmany) {
		string returnme = "";
		for (int i = 0; i < howmany; i++)
			returnme += str;
		return returnme;
	}
};

//////////////////////////////////
// 	G R A D E B O O K	//
//////////////////////////////////
class gbtable {
	public:
		gbtable();
		gbtable(gradebook*);
		gbtable(gradebooklist*);

		// initializers
		void addData(gradebook*);
		void addData(gradebooklist*);
		void updateData();

		// utilities
		string strmultiply(string, int);
		void settbsize();

		// visuals
		void displaytable();

	private:
		// checks if gradebook linkedlist is passed or not (display by subject or display specific subject details)
		// table size (number of nodes in the list)
		// longest = longest string
		// pair = data
		bool islinked;
		int longest;
		int tbsize;

		gradebook* gb;
		gradebooklist* gbl;

		studentinfo* student;
};

//////////////////////////////////
//	gbtable definition	//
//////////////////////////////////
gbtable::gbtable() {
	islinked = false;
	longest = 8;
	gb = NULL;
}

// for displaying subject details
gbtable::gbtable(gradebook* subj) {
	islinked = false;
	gb = subj;
	longest = gb->largeststring(gb->getFirst(), 8);
	student = gb->getFirst();
	gbl = NULL;
}

// for displaying all subjects
gbtable::gbtable(gradebooklist* glist) {
	islinked = true;
	longest = glist->largeststring(glist->getFirst(), 8);
	gbl = glist;
	gb = NULL;
}


// manual addition of data
void gbtable::addData(gradebook* subj) {
	islinked = false;
	gb = subj;
	longest = gb->largeststring(gb->getFirst(), 8);
	student = gb->getFirst();
	gbl = NULL;
}

// for displaying all subjects
void gbtable::addData(gradebooklist* glist) {
	islinked = true;
	longest = glist->largeststring(glist->getFirst(), 8);
	gbl = glist;
	gb = NULL;
}

// update data by re-callling the addData function
void gbtable::updateData() {
	if (islinked)
		addData(gbl);
	else
		addData(gb);
}

// string multiply
string gbtable::strmultiply(string str, int times) {
	string ret = "";
	for (int i = 0; i < times; i++)
		ret += str;
	return ret;
}

// calculates the tables size by retrieving the size of student node/number of subjects
void gbtable::settbsize() {
	if (islinked) {
		tbsize = gbl->listnum();
	} else {
		tbsize = gb->listnum();
	}
}

// displays table
// precondition: use this function if there are already students/subjects assigned in the gradebook/list
void gbtable::displaytable() {
	this->updateData();
	this->settbsize();
	if (islinked) {
		// storage for the current node
		gnode* maxdelta = gbl->getFirst();

		// upper border
		string bup = " -----  -" +  strmultiply("-", longest) + "-";

		cout << bup << endl;
		cout << "| NO. | SUBJECTS" << strmultiply(" ", longest - 8) << " |" << endl;
		cout << bup << endl;
		for (int i = 0; i < tbsize; i++) {
			// dipshit maths
			string data = gbl->displaysubject(maxdelta);
			cout << "| " << i + 1 << strmultiply(" ", 2 - (i + 1 >= 10) - (i + 1 >= 100)) << " | " << data << strmultiply(" ", longest - data.size()) << " |" << endl;
			maxdelta = maxdelta->next;
		}
		cout << bup << endl;
	} else {
		// storage for the current node
		studentinfo* koala = student;

		// display upper messsage
		gb->message();

		// upper border design (no. names, grades)
		string bup = " ----- -" + strmultiply("-", longest) + "- --------";

		cout << bup << endl;
		cout << "| NO. | NAMES" << strmultiply(" ", longest - 5) << " | GRADES |" << endl;
		cout << bup << endl;
		for (int i = 0; i < tbsize; i++) {
			// data that will be used
			string name = gb->displayname(koala);
			float grade = gb->displaygrade(koala);

			// middle part
			cout << "| " << (i + 1) << strmultiply(" ", 2 - (i + 1 >= 10) - (i + 1 >= 100)) << " | " << name << strmultiply(" ", longest - name.size()) << " | " << fixed << setprecision(2) << grade << "   |" << endl;

			koala = koala->next;
		}
		cout << bup << endl;

	}
}
//////////////////////////
//	E N D		//
//////////////////////////



//////////////////////////////////
//	D A T A B A S E		//
//////////////////////////////////
class dbtable {
	public:
		// constructor
		dbtable();
		dbtable(tridata*);
		dbtable(creds*, creds*);

		// manual data addition
		void addData(database*);
	private:
		int longest;

		database* db;
		triad* db_table;
};

//////////////////////////////////////////
//	A U T H E N T I C A T I O N	//
//////////////////////////////////////////
class authtable {
	public:
		authtable();
		authtable(auth*);

		void addData(auth*);
		void settbsize(bool);
		void updateData(bool);
		void displayteachers();
		void displaystudents();
		string strmultiply(string, int);
	private:
		credential* students;
		credential* teachers;
		gutilities utility;
		auth* stdata;
		int longestuser;
		int longestname;
		int longestpass;
		int tbsize;
};

//////////////////////////////////////////
//	AUTHENTICATION definition	//
//////////////////////////////////////////
authtable::authtable() {
	students = NULL;
	teachers = NULL;
	stdata = NULL;
	longestname = 4;
	longestuser = 8;
	longestpass = 8;
	tbsize = 0;
}

authtable::authtable(auth* obj) {
	if (obj == NULL) {
		cout << "[!] You assigned a NULL pointer! executing default constructor..." << endl;
		authtable();
	} else {
		stdata = obj;
		teachers = stdata->getTeachers();
		students = stdata->getStudents();
		tbsize = 0;
		longestname = 4;
		longestuser = 8;
		longestpass = 8;
	}
}

void authtable::addData(auth* obj) {
	stdata = obj;
	students = stdata->getTeachers();
	teachers = stdata->getStudents();
}

// note that 0 is for teacher and 1 is for student
void authtable::settbsize(bool st) {
	// teacher
	if (st == 0) {
		if (teachers != NULL)
			tbsize = teachers->getlistnum();
		else
			tbsize = 0;
	} else {
		if (students != NULL)
			tbsize = students->getlistnum();
		else
			tbsize = 0;
	}
}

// update spacing of students or teachers table
void authtable::updateData(bool st) {
	// teaher spacing
	if (st == 0) {
		if (teachers != NULL) {
			longestuser = teachers->longestfuckinguser(teachers->getFirst(), longestuser);
			longestname = teachers->longestfuckingname(teachers->getFirst(), longestname);
			longestpass = teachers->longestfuckingpass(teachers->getFirst(), longestpass);
		}
	} else {
		if (students != NULL) {
			longestuser = students->longestfuckinguser(students->getFirst(), longestuser);
			longestname = students->longestfuckingname(students->getFirst(), longestname);
			longestpass = students->longestfuckingpass(students->getFirst(), longestpass);
		}
	}
}


// table for the teacher credentials
void authtable::displayteachers() {
	// setup for teachers table credentails
	this->settbsize(0);
	this->updateData(0);

	// main process
	string ub = " ----- -" + strmultiply("-", longestname) + "- -" + strmultiply("-", longestuser) + "- -" + strmultiply("-", longestpass) + "-";

	cout << "TEACHERS\' CREDENTIAL/s" << endl;
	cout << ub << endl;
	cout << "| NO. | NAME" + strmultiply(" ", longestname - 4) + " | USERNAME" + strmultiply(" ", longestuser - 8) + " | PASSWORD" + strmultiply(" ", longestpass - 8) + " |" << endl;
	cout << ub << endl;

	// retrieve first node for printing values, and other dynamic variables needed
	creds* node = teachers->getFirst();
	string name;
	string user;
	string pass;

	// mid part
	for (int i = 0; i < tbsize; i++) {
		name = teachers->printName(node);
		user = teachers->printUser(node);
		pass = teachers->printPass(node);

		cout << "| " << (i + 1) << strmultiply(" ", 2 - (i + 1 >= 10) - (i + 1 >= 100)) << " | " << name << strmultiply(" ", longestname - name.size()) << " | " << user << strmultiply(" ", longestuser - user.size()) << " | " << pass << strmultiply(" ", longestpass - pass.size()) << " |" << endl;
		node = node->next;
	}
	cout << ub << endl;
}

// table for displaying students credentials
void authtable::displaystudents() {
	// setup for teachers table credentails
	this->settbsize(1);
	this->updateData(1);

	// main process
	string ub = " ----- -" + strmultiply("-", longestname) + "- -" + strmultiply("-", longestuser) + "- -" + strmultiply("-", longestpass) + "-";

	cout << "STUDENTS\' CREDENTIAL/s" << endl;
	cout << ub << endl;
	cout << "| NO. | NAME" + strmultiply(" ", longestname - 4) + " | SR-CODE" + strmultiply(" ", longestuser - 7) + " | PASSWORD" + strmultiply(" ", longestpass - 8) + " |" << endl;
	cout << ub << endl;

	// retrieve first node for printing values, and other dynamic variables needed
	creds* node = students->getFirst();
	string name;
	string user;
	string pass;

	// mid part
	for (int i = 0; i < tbsize; i++) {
		name = students->printName(node);
		user = students->printUser(node);
		pass = students->printPass(node);

		cout << "| " << (i + 1) << strmultiply(" ", 2 - (i + 1 >= 10) - (i + 1 >= 100)) << " | " << name << strmultiply(" ", longestname - name.size()) << " | " << user << strmultiply(" ", longestuser - user.size()) << " | " << pass << strmultiply(" ", longestpass - pass.size()) << " |" << endl;
		node = node->next;
	}
	cout << ub << endl;
}

string authtable::strmultiply(string str, int size) {
	string returnme = "";
	for (int i = 0; i < size; i++)
		returnme += str;
	return returnme;
}
//////////////////
//	End	//
//////////////////


//////////////////////////////////
//	C R E D E N T I A L	//
//////////////////////////////////
class credstable {
	private:
		credential* data;
		int longest;
		int tbsize;
	public:
		credstable(credential*);
		void displaytable();
		string strmultiply(string, int);
};


//////////////////////////////////
//	CREDENTIAL DEFINITION	//
//////////////////////////////////
credstable::credstable(credential* obj) {
	if (obj != NULL) {
		data = obj;

		// setup here
		longest = data->longestfuckingname(data->getFirst(), 4);
		tbsize = data->getlistnum();
	} else {
		tbsize = 0;
		longest = 4;
	}
}

void credstable::displaytable() {
	string name;
	string ub = " -----  -" + strmultiply("-", longest) + "-";

	cout << ub << endl;
	cout << "| NO. | NAME" << strmultiply(" ", longest - 4) << " |" << endl;
	cout << ub << endl;

	// get ready to be fucked up
	creds* fuck = data->getFirst();

	for (int i = 0; i < tbsize; i++) {
		name = fuck->name;
		cout << "| " << (i + 1) << strmultiply(" ", 2 - (i + 1 >= 10) - (i + 1 >= 100)) << " | " << name << strmultiply(" ", longest - name.size()) << " |" << endl;
		fuck = fuck->next;
	}
	cout << ub << endl;
}

string credstable::strmultiply(string str, int size) {
	string returnme = "";
	for (int i = 0; i < size; i++)
		returnme += str;
	return returnme;
}
//////////////////
//	END	//
//////////////////
#endif
