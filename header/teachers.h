#ifndef TEACHERS_H
#define TEACHERS_H

#include "gradebook.h"
#include "tables.h"
#include "linkedlist.h"
#include <iostream>
using namespace std;

#if defined(_WIN32)
	#define CLEAR "cls"
	#define PAUSE "pause"
#else
	#define CLEAR "clear"
	#define PAUSE "bash -c \"read -p \'Press Enter to continue...\'\""
#endif

class teacher {
	private:
		gradebooklist* glist;
	public:
		teacher(gradebooklist*);

		void teacherInterface();
		void viewSubject();
		void viewSubjectdetail();
		void editGrade();
		float error(string);
};

teacher::teacher(gradebooklist* obj) {
	glist = obj;
}

void teacher::teacherInterface() {
	int choice;
	bool breakme = 1;

	while (breakme) {
		system(CLEAR);
		cout << "=====================================" << endl;
		cout << "          TEACHER INTERFACE" << endl;
		cout << "=====================================" << endl;
		cout << " [1] View subjects" << endl;
		cout << " [2] View subject details" << endl;
		cout << " [3] Edit grade" << endl;
		cout << " [4] Log out" << endl << endl;

		choice = error(": ");

		switch (choice) {
			case 1:
				viewSubject();
				break;
			case 2:
				viewSubjectdetail();
				break;
			case 3:
				editGrade();
				break;
			default:
				cout << "[!] Logging out..." << endl;
				breakme = 0;
				break;
		}
		system(PAUSE);
	}
}

void teacher::viewSubject() {
	system(CLEAR);
	cout << "=====================================" << endl;
	cout << "           LIST OF SUBJECTS" << endl;
	cout << "=====================================" << endl;

	gbtable tb(glist);
	tb.displaytable();
}

void teacher::viewSubjectdetail() {
	system(CLEAR);
	int x;
	cout << "=====================================" << endl;
	cout << "             SUBJECT DATA" << endl;
	cout << "=====================================" << endl;
	gbtable tb(glist);
	tb.displaytable();

	x = error("Display subject data (row) : ");

	cout << endl;
	gradebook* data;
	data = glist->access(x);

	if (data != NULL) {
		system(CLEAR);
		gbtable tbl(data);
		tbl.displaytable();
	} else {
		cout << "[!] Cannot display table of nonexistent subject!" << endl;
	}
}

void teacher::editGrade() {
	system(CLEAR);
	int x;
	float y;
	bool anji = 1;
	cout << "=====================================" << endl;
	cout << "             EDIT GRADES" << endl;
	cout << "=====================================" << endl;
	gbtable tb(glist);
	tb.displaytable();

	x = error("Enter row num. : ");

	cout << endl;
	gradebook* data;
	data = glist->access(x);

	// fix this bug when accessing nonexistent subject
	if (data == NULL)
		anji = 0;
	
	// so loop doesnt start
	while (anji) {
		system(CLEAR);
		cout << "[NOTE] You can exit by entering \'0\'" << endl;
		gbtable tbl(data);
		tbl.displaytable();

		x = error("Edit grade on student no. : ");
		if (x == 0) { break; }
		y = error("New grade of student : ");

		data->editgrade(x, y);

		system(CLEAR);
		gbtable ntb(data);
		ntb.displaytable();
	}
}

float teacher::error(string shite) {
	float a;

	while (1) {
		cout << shite;
		if (!(cin >> a)) {
			cin.clear();
			cin.ignore();
			cout << "[!] Enter valid input!" << endl;
		} else {
			return a;
		}
	}
}
#endif
