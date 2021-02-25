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
		gradebook* retrieveTeacher(string username);
		gradebook* retrieveStudent(string username);

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

struct databaseVisuals {
	void displayTable(const database &db) const;
};

//////////////////////////////////
//	Database definition	//
//////////////////////////////////
void database::connect(credential* stud, credential* teac) {
	student = stud;
	teacher = teac;
}

//////////////////////////////////
//	Visuals definition	//
//////////////////////////////////
#endif
