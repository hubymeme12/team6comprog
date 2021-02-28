#include <iostream>
#include "header/gradebook.h"
#include "header/tables.h"
#include "header/linkedlist.h"
using namespace std;

class teacher {
	private:
		gradebooklist* glist;
	public:
		teacher(gradebooklist*);

		void teacherInterface();
		void viewSubject();
		void viewSubjectdetail();
		void editGrade();
		int error(string);
};

teacher::teacher(gradebooklist* obj) {
	glist = obj;
}

void teacher::teacherInterface() {
	int choice;
	bool breakme = 1;

	while (breakme) {
		system ("cls");
		cout << "=====================================" << endl;
		cout << "          TEACHER INTERFACE" << endl;
		cout << "=====================================" << endl;
		cout << " [1] View subjects" << endl;
		cout << " [2] View subject details" << endl;
		cout << " [3] Edit grade" << endl << endl;
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
				cout << "end..." << endl;
				breakme = 0;
				break;
		}
		system ("pause");
	}
}

void teacher::viewSubject() {
	cout << "=====================================" << endl;
	cout << "           LIST OF SUBJECTS" << endl;
	cout << "=====================================" << endl;
	gbtable tb(glist);
	tb.displaytable();
}

void teacher::viewSubjectdetail() {
	int x;
	cout << "=====================================" << endl;
	cout << "             SUBJECT DATA" << endl;
	cout << "=====================================" << endl;
	gbtable tb(glist);
	tb.displaytable();

	x = error("Display data on subject number : ");

	cout << endl;
	gradebook* data;
	data = glist->access(x);
	gbtable tbl(data);
	tbl.displaytable();
}

void teacher::editGrade() {
	int x;
	float y;
	cout << "=====================================" << endl;
	cout << "             EDIT GRADES" << endl;
	cout << "=====================================" << endl;
	gbtable tb(glist);
	tb.displaytable();

	x = error("Select subject number you want to edit the grades : ");

	cout << endl;
	gradebook* data;
	data = glist->access(x);
	gbtable tbl(data);
	tbl.displaytable();

	x = error("Edit grade on student no. : ");
	y = error("New grade of student : ");

	cout << endl;
	data->editgrade(x, y);
	gbtable ntb(data);
	ntb.displaytable();
}

int teacher::error(string shite) {
	int a;

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
