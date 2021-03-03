#include <iostream>
using namespace std;

#include "header/linkedlist.h"
#include "header/gradebook.h"
#include "header/database.h"
#include "header/authentication.h"
#include "header/tables.h"
#include "header/admin.h"
#include "header/teachers.h"

#if defined(_WIN32)
	#define CLEAR "cls"
	#define PAUSE "pause"
#else
	#define CLEAR "clear"
	#define PAUSE "read -p \"Press enter key to continue...\" NULL"
#endif

// global variables
admin* administrator = new admin;
auth* authentication = administrator->getauth();

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
				administrator->login();
				break;
			case 2:
				Tlogin();
				break;
			case 3:
				Slogin();
				break;
			default:
				cout << "[-] Exitting..." << endl;
				breakme = 0;
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

	system(CLEAR);
	cout << "==========================" << endl;
	cout << "      TEACHER LOGIN" << endl;
	cout << "==========================" << endl;
	cout << "Enter username : ";
	getline(cin >> ws, user);
	cout << "Enter password : ";
	getline(cin >> ws, passw);

	// login these input credentials
	gradebooklist* retrievedgb = authentication->loginTeacher(user, passw);
	system(PAUSE);
}

void Slogin() {
	string user, passw;

	system(CLEAR);
	cout << "==========================" << endl;
	cout << "      STUDENT LOGIN" << endl;
	cout << "==========================" << endl;
	cout << "Enter username : ";
	getline(cin >> ws, user);
	cout << "Enter password : ";
	getline(cin >> ws, passw);

	// login these input credentials
	authentication->loginStudent(user, passw);
	system(PAUSE);
}
