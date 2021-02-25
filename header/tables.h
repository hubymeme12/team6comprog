#ifndef TABLES_H
#define TABLES_H

#include <iostream>
using namespace std;

#include "linkedlist.h"
#include "gradebook.h"
#include "authentication.h"

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
	updateData();
	settbsize();
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


class dbtable {

};

class authtable {

};
#endif
