#include <iostream>
using namespace std;

#include "header/linkedlist.h"
#include "header/gradebook.h"
#include "header/database.h"
#include "header/authentication.h"
#include "header/tables.h"

#if defined(_WIN32)
	#define CLEAR "cls"
	#define PAUSE "pause"
#else
	#define CLEAR "clear"
	#define PAUSE "read -p \"Press enter key to continue...\" NULL"
#endif

// input filter
float input(string message);

int main() {
	// variables needed
	int inp;

	// initial design
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
		case 2:
		case 3:
		default:
			cout << "[-] Exitting..." << endl;
			break;
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
