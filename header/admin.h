#include <iostream>
#include "authentication.h"
#include "database.h"
using namespace std;

#if defined(_WIN32)
        #define CLEAR "cls"
        #define PAUSE "pause"
#else
        #define CLEAR "clear"
        #define PAUSE "read -p \"Press enter key to continue...\" NULL"
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
		int getFucked(string);
	public:
		// constructors
		admin();
		admin(string, string);

		// utilities
		void changeacc(string, string);
		auth* getauth() const;

		// interface/s
		void login();
};

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
	cout << "Password : ";
	getline(cin >> ws, p);

	if (adminuser == u && adminpass == p) {
		maininterface();
	} else {
		cout << "[!] Wrong password..." << endl;
		system(PAUSE);
	}
}

void admin::maininterface() {
	bool breakme = 1;
	int choice;

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
		cout << " [7] Delete a subject" << endl;
		cout << " **UTILITIES**" << endl;
		cout << " [8] Change admin account" << endl;
		cout << " [9] Exit" << endl << endl;

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
			case 8:
				changeaccinterface();
				break;
			case 9:
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
	cout << "Below is the table list of student\'s accounts... Enter the number of row that will be deleted account" << endl;
	tb.displayteachers(); cout << endl;
	index = getFucked("Row number : ");

	// delete this teacher's account
	secret->delStudentAccount(index);
	cout << "[+] Account number " << index << " deleted!" << endl;
	system(PAUSE);
}

void admin::displayaccinterface() {
	system(CLEAR);
	authtable tstable(secret);
	tstable.displayteachers();
	cout << endl << "==========================================" << endl << endl;
	tstable.displaystudents();
	system(PAUSE);
}

void admin::changeaccinterface() {
	// some variables:
	string newuser, newpass;

	system(CLEAR);
	cout << "================================" << endl;
	cout << "         Account changes" << endl;
	cout << "================================" << endl;
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
	} else {
		// nah shit, change ur shit
		cout << "[!] Error, credentials entered are not valid." << endl;
	}
	system(PAUSE);
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
