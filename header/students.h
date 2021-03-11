#include <iostream>
#include "tables.h"
using namespace std;

class student {
	private:
		gradebooklist* list;
		string name;
	public:
		student(gradebooklist*, string);
		void maininterface();
};

student::student(gradebooklist* gbl, string studname) {
	list = gbl;
	name = studname;
}

void student::maininterface() {
	gradestbl table(list, name);
	table.displaytable();
}
