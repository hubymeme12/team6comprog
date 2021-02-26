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
		cout << " **SUBJECTS**" << endl;
		cout << " [5] Add new subject" << endl;
		cout << " [6] Delete a subject" << endl;
		cout << " **UTILITIES**" << endl;
		cout << " [7] Change admin account" << endl;
		cout << " [8] Exit" << endl << endl;

		choice = getFucked(": ");

		switch (choice) {
			case 1:
				addteacherinterface();
				break;
			case 2:
				addstudentinterface();
				break;
			default:
				breakme = 0;
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
	cout << "Enter student full name : ";
	getline(cin >> ws, studname);
	cout << "Enter student username : ";
	getline(cin >> ws, studuname);
	cout << "Enter student password : ";
	getline(cin >> ws, studpass);

	// add this student credentials to auth
	secret->addStudentAccount(studuname, studname, studpass);
	cout << "[+] Student account added!" << endl;
	system(PAUSE);
}

void admin::addteacherinterface() {
	string teachname, teachuname, teachpass;

	system(CLEAR);
	cout << "====================================" << endl;
	cout << "         ADD TEACHER CREDENTIAL" << endl;
	cout << "====================================" << endl;
	cout << "Enter teacher full name : ";
	getline(cin >> ws, teachname);
	cout << "Enter teacher username : ";
	getline(cin >> ws, teachuname);
	cout << "Enter teacher password : ";
	getline(cin >> ws, teachpass);

	// add this student credentials to auth
	secret->addTeacherAccount(teachuname, teachname, teachpass);
	cout << "[+] Teacher account added!" << endl;
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
