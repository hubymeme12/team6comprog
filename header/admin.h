#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>
#include <conio.h>
#include "authentication.h"
#include "database.h"
#include "tables.h"
#include "fileman.h"
using namespace std;

#if defined(_WIN32)
        #define CLEAR "cls"
        #define PAUSE "pause"
#else
        #define CLEAR "clear"
        #define PAUSE "bash -c \"read -p \'Press Enter to continue...\'\""
#endif

class admin {
	private:
		database* db;
		auth* secret;

		string adminuser;
		string adminpass;

		// some functions u cannot access
		void maininterface();
		void addstudentinterface();
		void addteacherinterface();
		void delteacherinterface();
		void delstudentinterface();
		void displayaccinterface();
		void changeaccinterface();
		void addsubjectinterface();
		void writedatainterface();
		void readdatainterface();
		void deletesubjectinterface();

		// input filter
		int getFucked(string);
	public:
		// constructors
		admin();
		admin(string, string);
		~admin();

		// utilities
		void changeacc(string, string);				// changes account of admin
		auth* getauth() const;						// so auth object can be used outside (for logging in)

		// interface/s
		void login();								// login admin account (only public member to access the private functions)
};

string passlogin(string display) {
	char pw;
	char* longpass;
	string password;

	cout << display;
	while (1) {
		pw = getch();
		if (pw == '\r') {
			break;
		} else if (pw == '\b')  {
			if (password.size() > 0) {
				password.erase((password.end() - 1));
				cout << "\b \b";
			}
		} else {
			password.push_back(pw);
			cout << '*';
		}
	}

	cout << endl;
	return password;
}

//////////////////////////
//	admin		//
//////////////////////////
admin::admin() {
	db = new database;
	secret = new auth;

	adminuser = "admin";
	adminpass = "admin";
}

admin::admin(string username, string password) {
	admin();

	adminuser = username;
	adminpass = password;
}

// destructor
admin::~admin() {
	cout << "[!] Releasing memory : " << &db << endl;
	delete db;

	cout << "[!] Releasing memory : " << &secret << endl;
	delete secret;
}

void admin::changeacc(string username, string password) {
	adminuser = username;
	adminpass = password;
}

auth* admin::getauth() const {
	return secret;
}

void admin::login() {
	system(CLEAR);
	string u, p;

	cout << "=========================" << endl;
	cout << "    ADMIN LOGIN PANEL" << endl;
	cout << "=========================" << endl;
	cout << "Username : ";
	getline(cin >> ws, u);
	p = passlogin("Password : ");

	if (adminuser == u && adminpass == p) {
		maininterface();
	} else {
		cout << "[!] Wrong credentials entered!" << endl;
		system(PAUSE);
	}
}

void admin::maininterface() {
	bool breakme = 1;
	int choice;

	secret->setDatabase(db);
	secret->connectDatabase();

	while (breakme) {
		system(CLEAR);
		cout << "======================================" << endl;
		cout << "            ADMIN INTERFACE" << endl;
		cout << "======================================" << endl;
		cout << " **ACCOUNTS**" << endl;
		cout << " [1] Add teacher account" << endl;
		cout << " [2] Add student account" << endl;
		cout << " [3] Delete teacher account" << endl;
		cout << " [4] Delete student account" << endl;
		cout << " [5] Display all accounts" << endl;
		cout << " **SUBJECTS**" << endl;
		cout << " [6] Add new subject" << endl;
		cout << " [7] Delete/View subject" << endl;
		cout << " **UTILITIES**" << endl;
		cout << " [8] Save data" << endl;
		cout << " [9] Load data" << endl;
		cout << " [10] Change admin account" << endl;
		cout << " [11] Log out" << endl << endl;

		choice = getFucked(": ");

		switch (choice) {
			case 1:
				addteacherinterface();
				break;
			case 2:
				addstudentinterface();
				break;
			case 3:
				delteacherinterface();
				break;
			case 4:
				delstudentinterface();
				break;
			case 5:
				displayaccinterface();
				break;
			case 6:
				addsubjectinterface();
				break;
			case 7:
				deletesubjectinterface();
				break;
			case 8:
				writedatainterface();
				break;
			case 9:
				readdatainterface();
				break;
			case 10:
				changeaccinterface();
				break;
			case 11:
				breakme = 0;
				break;
			default:
				cout << "[!] Error : Please enter proper input!" << endl;
				break;
		}
	}
}

void admin::addstudentinterface() {
	string studname, studuname, studpass;

	system(CLEAR);
	cout << "====================================" << endl;
	cout << "         ADD STUDENT CREDENTIAL" << endl;
	cout << "====================================" << endl;

	authtable stable(secret);
	stable.displaystudents();

	cout << "Enter student full name : ";
	getline(cin >> ws, studname);
	cout << "Enter student sr-code : ";
	getline(cin >> ws, studuname);
	cout << "Enter student password : ";
	getline(cin >> ws, studpass);

	// add this student credentials to auth
	secret->addStudentAccount(studuname, studname, studpass);

	// new interface for displaying table of new students
	system(CLEAR);
	cout << "[UPDATED]" << endl;
	stable.displaystudents();
	system(PAUSE);
}

void admin::addteacherinterface() {
	string teachname, teachuname, teachpass;

	system(CLEAR);
	cout << "====================================" << endl;
	cout << "         ADD TEACHER CREDENTIAL" << endl;
	cout << "====================================" << endl;

	authtable ttable(secret);
	ttable.displayteachers();

	cout << "Enter teacher full name : ";
	getline(cin >> ws, teachname);
	cout << "Enter teacher username : ";
	getline(cin >> ws, teachuname);
	cout << "Enter teacher password : ";
	getline(cin >> ws, teachpass);

	// add this student credentials to auth
	secret->addTeacherAccount(teachuname, teachname, teachpass);

	// new interface for displaying the updated table
	system(CLEAR);
	cout << "[UPDATED]" << endl;
	ttable.displayteachers();
	system(PAUSE);
}

void admin::delteacherinterface() {
	authtable tb(secret);
	int index;

	system(CLEAR);
	cout << "Below is the table list of teacher\'s accounts... Enter the number of row that will be deleted account" << endl;
	tb.displayteachers(); cout << endl;
	index = getFucked("Row number : ");

	// delete this teacher's account
	secret->delTeacherAccount(index);
	cout << "[+] Account number " << index << " deleted!" << endl;
	system(PAUSE);
}

void admin::delstudentinterface() {
	authtable tb(secret);
	int index;

	system(CLEAR);
	// this is a freakin table
	cout << "Below is the table list of student\'s accounts... Enter the number of row that will be deleted account" << endl;
	tb.displaystudents(); cout << endl;
	index = getFucked("Row number : ");

	// delete this teacher's account
	secret->delStudentAccount(index);
	cout << "[+] Account no. " << index << " deleted!" << endl;
	system(PAUSE);
}

void admin::displayaccinterface() {
	system(CLEAR);

	// display teacher credentials table
	authtable tstable(secret);
	tstable.displayteachers();
	cout << endl << "==========================================" << endl << endl;

	// display student credentials table
	tstable.displaystudents();

	// try the parser
	// char* fileo = db->getbuffer();
	// cout << "Sample file buffer : " << endl;
	// cout << fileo << endl;

	system(PAUSE);
}

void admin::changeaccinterface() {
	// some variables:
	string newuser, newpass;

	system(CLEAR);
	cout << "================================" << endl;
	cout << "         Account changes" << endl;
	cout << "================================" << endl;

	// inputsssscxz
	cout << "Current username : ";
	getline(cin >> ws, newuser);
	cout << "Current password : ";
	getline(cin >> ws, newpass);

	// check credentials
	if (adminuser == newuser && adminpass == newpass) {
		// allow to change password
		cout << "Enter new username : ";
		getline(cin >> ws, newuser);
		cout << "Enter new password : ";
		getline(cin >> ws, newpass);

		// change password
		changeacc(newuser, newpass);
		cout << "[+] Password changed!!" << endl;
	} else {
		// nah shit, change ur shit
		cout << "[!] Error, credentials entered are not valid." << endl;
	}
	system(PAUSE);
}

void admin::addsubjectinterface() {
	// variables, variables...
	int choice;
	bool breakme = 1;
	bool breakme2 = 1;
	short num;
	creds* tchr;
	string subjname;
	string teachername;

	system(CLEAR);
	cout << "================================" << endl;
	cout << "         SUBJECT SETUP" << endl;
	cout << "================================" << endl;
	cout << "Enter subject name : ";
	getline(cin >> ws, subjname);

	// make new gradebook for this subject
	gradebook* subj = new gradebook;
	subj->setcourseName(subjname);

	system(CLEAR);
	// some display
	cout << "[+] Subject : " << subjname << " Added" << endl;
	cout << "[*] Select teacher row below to assign a teacher" << endl;
	cout << "Enter \'0\' to exit" << endl;

	// this displays table
	// select from the teacher credentials
	credstable teachtables(secret->getTeachers());
	teachtables.displaytable();

	// some variables needed
	credential* tchrnode;
	credential* node;
	creds* chosen;

	// input loop unless user entered valid input
	while (breakme2) {
		choice = getFucked("Select row : ");

		// retrieve node
		tchrnode = secret->getTeachers();
		chosen = tchrnode->getNode(choice);

		if (choice == 0) {
			breakme = 0;
			break;
		}

		// check if index is valid
		if (chosen != NULL) {
			// get name from this node
			teachername = chosen->name;

			// setup database values if chosen node is valid (not null)
			db->pseudonodecopy();
			node = db->returnpseudonode();
			breakme2 = 0;
		}
	}

	while (breakme) {
		system(CLEAR);
		cout << "Below are list of students that are registered " << endl;
		cout << "Select the row number of student to be enrolled" << endl;
		cout << "Select \'0\' to add details" << endl;
		cout << "===============================================" << endl;
		cout << "Subject : " << subjname << endl;
		cout << "Teacher : " << teachername << endl;

		// table
		credstable crtable(node);
		crtable.displaytable(); cout << endl;

		num = getFucked("row number : ");

		if (num == 0) {
			db->pushdata(subj, teachername, db->addednode());
			breakme = 0;
		} else {
			db->addnode(subj, num);	// add this node to selected students
		}
	}
}

void admin::writedatainterface() {
	string filename;
	fileman fl;
	char* converted;
	char choice;

	system(CLEAR);
	cout << "=================================" << endl;
	cout << "     WRITE FILE INTERFEACE" << endl;
	cout << "=================================" << endl;
	cout << "Enter file name : ";
	getline(cin >> ws, filename);
	//cout << "Encrypt file? y/n : ";
	//cin >> choice;

	cout << "[*] Converting string to char*..." << endl;

	// convert this to char*
	converted = new char[filename.size()];
	for (int i = 0; i < filename.size() + 1; i++) {
		converted[i] = filename[i];
	}

	cout << "[+] Saving to filename : " << filename << "..." << endl;
	fl.target(converted);
	fl.retrievedata(db);
	//fl.write((choice == 'y' || choice == 'Y'));

	fl.write(0);
	cout << "[+] File Saved!" << endl;
	system(PAUSE);
}

void admin::readdatainterface() {
	string fname;
	char choice;

	system(CLEAR);
	cout << "===========================" << endl;
	cout << "        FILE LOADING" << endl;
	cout << "===========================" << endl;
	cout << "Enter file name : ";
	getline(cin >> ws, fname);

	// cout << "Encrypted? Y/N  : ";
	// cin >> choice;

	// convert to char[]
	char* nfnam = new char[fname.size()];
	for (int i = 0; i < fname.size() + 1; i++) {
		nfnam[i] = fname[i];
	}

	// parse accounts
	authparser aparser(nfnam, secret);
	if (!aparser.fillauth(0)) {
		cerr << "[!] An error occured in parsing credentials." << endl;
	}

	// setup pseudonodes for this parser
	//db->pseudonodecopy();

	// parse gradebook
	gbparser gbookparse(nfnam, db);
	if (!gbookparse.filldb(0)) {
		cerr << "[!] An error occured in parsing database values." << endl;
	}

	system(PAUSE);
}

void admin::deletesubjectinterface() {
	system(CLEAR);
	cout << "================================" << endl;
	cout << "         DELETE SUBJECT" << endl;
	cout << "================================" << endl;
	cout << "Enter index of subject you want to delete" << endl;
	cout << "You can enter \'0\' to exit" << endl;
	
	// retrieve all gradebook list for table display
	gradebooklist* all = db->retrieveglist();

	// display table
	gbtable subtable(all);
	subtable.displaytable();

	// get input
	int index = getFucked("Enter Index : ");

	if (index != 0) {
		// delete subject
		db->deletedata(index);

		// re-display table
		all = db->retrieveglist();
		
		system(CLEAR);
		cout << "Updated subject/s list :" << endl;
		gbtable newtable(all);
		newtable.displaytable();
		system(PAUSE);
	}
}

int admin::getFucked(string out) {
	int myass;

	while (1) {
		cout << out;
		if (!(cin >> myass)) {
			cin.clear();
			cin.ignore();
			cout << "[!] Enter valid input!" << endl;
		} else {
			return myass;
		}
	}
}
#endif
