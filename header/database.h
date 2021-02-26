#ifndef DATABASE_H
#define DATABASE_H

#include "linkedlist.h"
#include "gradebook.h"

// target: data retrieval for teachers and students
// push data to the database (will be done by the admin)

class database {
	private:
		tridata db_table;

		credential* student;
		credential* teacher;
	public:
		// data retrieval
		gradebooklist* retrieveTeacher(string teachername);
		gradebooklist* retrieveStudent(string username);

		// setup
		void connect(credential* stud, credential* teac);

		// data manipulation
		void addSubject(string subjectname);
		void deleteSubj(string subjectname);		// whole subject (triad deletion)
		void deleteTeacher(string teachername);		// teachers (specific teacher will be removed)
		void deleteStudent(string studentName);		// students (specific student will be removed)

		void deleteFromTeacher(string* subject, string Tname);
		void deleteFromStudent(string* subject, string Sname);
};

//////////////////////////////////
//	Database definition	//
//////////////////////////////////
// connects address for changes
void database::connect(credential* stud, credential* teac) {
	student = stud;
	teacher = teac;
}

// retrieves the subjects for this teacher
gradebooklist* database::retrieveTeacher(string teachername) {
	// makes graedebooklist where data will be pushed
	tridata* retrievedtriads = new triad;
	gradebooklist* retrieved = new gradebooklist;

	// search if teacher name exists in triad.
	// retrieve this gradebook from triad
}

//////////////////////////
// 	E N D 		//
//////////////////////////
#endif
