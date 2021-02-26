#include <iostream>
using namespace std;

#include "header/linkedlist.h"
#include "header/gradebook.h"
#include "header/database.h"
#include "header/authentication.h"
#include "header/tables.h"
#include "header/admin.h"

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
void teacherlogin();
void studentlogin();

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
				cout << "Soon..." << endl;
				break;
			case 3:
				cour << "Soon..." << endl;
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
