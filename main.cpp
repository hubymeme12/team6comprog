#include <iostream>
#include <conio.h>
using namespace std;

#include "header/database.h"
#include "header/authentication.h"
#include "header/admin.h"
#include "header/fileman.h"
#include "header/teachers.h"
#include "header/students.h"

#if defined(_WIN32)
	#define CLEAR "cls"
	#define PAUSE "pause"
#else
	#define CLEAR "clear"
	#define PAUSE "bash -c \"read -p \'Press Enter to continue...\'\""
#endif

// global variables
admin administrator;
auth *authentication = administrator.getauth();

// input filter
float input(string message);

// weird functions
void Tlogin();
void Slogin();

int main() {
	// variables needed
	int inp;
	bool breakme = 1;

	// initial design
	while (breakme) {
		system(CLEAR);
		cout << "=============================" << endl;
		cout << "      SELECTION PANEL" << endl;
		cout << "=============================" << endl;
		cout << " [1] Admin login" << endl;
		cout << " [2] Teacher login" << endl;
		cout << " [3] Student login" << endl;
		cout << " [4] Exit" << endl << endl;

		inp = input(": ");

		switch (inp) {
			case 1:
				administrator.login();
				break;
			case 2:
				Tlogin();
				break;
			case 3:
				Slogin();
				break;
			case 4:
				cout << "[-] Exitting..." << endl;
				breakme = 0;
				break;
			default:
				cout << "[!] Invalid input!" << endl;
				break;
		}
	}

	return 0;
}

float input(string message) {
	float ret;

	while (true) {
		cout << message;
		if (!(cin >> ret)) {
			cin.clear();
			cin.ignore();
			cout << "[!] Invalid input!" << endl;
		} else {
			return ret;
		}
	}
}

void Tlogin() {
	string user, passw;
	char pw;

	system(CLEAR);
	cout << "==========================" << endl;
	cout << "      TEACHER LOGIN" << endl;
	cout << "==========================" << endl;
	cout << "Enter username : ";
	getline(cin >> ws, user);
	passw = passlogin("Enter password : ");

	// login these input credentials
	gradebooklist* retrievedgb = authentication->loginTeacher(user, passw);
	if (retrievedgb != NULL) {
		teacher maam(retrievedgb);
		maam.teacherInterface();
	} else {
		system(PAUSE);
	}
}

void Slogin() {
	string user, passw;
	char pw;

	system(CLEAR);
	cout << "==========================" << endl;
	cout << "      STUDENT LOGIN" << endl;
	cout << "==========================" << endl;
	cout << "Enter username : ";
	getline(cin >> ws, user);
	passw = passlogin("Enter password : ");

	// login these input credentials
	string studentname;
	gradebooklist* retrievedgb = authentication->loginStudent(user, passw, studentname);
	if (retrievedgb != NULL) {
		system(CLEAR);
		student stud(retrievedgb, studentname);
		stud.maininterface();
		system(PAUSE);
	} else {
		system(PAUSE);
	}
}
