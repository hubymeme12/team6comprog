#ifndef DATABASE_H
#define DATABASE_H

#include "linkedlist.h"
#include "gradebook.h"

// target: data retrieval for teachers and students
// push data to the database (will be done by the admin)

class database {
	public:
		// data retrieval
		gradebooklist* retrieveGBTeacher(string teachername);
		gradebooklist* retrieveGBStudent(string username);
		tridata* retrievedata();

		// setup
		void connect(credential* stud, credential* teac);

		// data manipulation
		void addSubject(string subjectname);		// add subject and deltails
		void deleteSubj(string subjectname);		// whole subject (triad deletion)
		void deleteStudent(string studentName);		// students (specific student will be removed)

		void deleteFromTeacher(string* subject, string Tname);
		void deleteFromStudent(string* subject, string Sname);
	private:
		tridata db_table;
		credential* student;
		credential* teacher;
};

//////////////////////////////////
//	Database definition	//
//////////////////////////////////
// retrieves the subjects for this teacher
gradebooklist* database::retrieveGBTeacher(string teachername) {
	// makes graedebooklist where data will be pushed
	// gradebooklist that will be returned
	// fnode that will be crawled on for retrieval
	tridata* retrievedtriads = new tridata;
	gradebooklist* retrieved = new gradebooklist;
	triad* fnode;

	// retrieve triads with matched teachers and push values to retrievedtriads
	db_table.retrieveTnodes(retrievedtriads, teachername);
	fnode = retrievedtriads->getFirst();

	// recover the gradebooks
	while (fnode != NULL) {
		// push the gradebookdata
		retrieved->pushBack(fnode->subject);
		fnode = fnode->next;
	}

	return retrieved;
}

tridata* database::retrievedata() { return &db_table; }

// connects address for changes
void database::connect(credential* stud, credential* teac) {
	student = stud;
	teacher = teac;
}

//////////////////////////
// 	E N D 		//
//////////////////////////
#endif
