#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include "linkedlist.h"
#include "database.h"

//#include "teachers."h
//#include "students.h"

class auth {
	private:
		credential* teachers;
		credential* students;
		database* db;
	public:
		// constructors
		auth();
		auth(database*);

		// account management
		void setDatabase(database*);
		void connectDatabase();
		void addTeacherAccount(string, string, string);
		void addStudentAccount(string, string, string);
		void delTeacherAccount(string);
		void delTeacherAccount(int);
		void delStudentAccount(string);
		void delStudentAccount(int);

		// credentials validation
		void loginTeacher(string, string);		// teacherDatatype
		void loginStudent(string, string);		// studentDatatype

		// debug
		database* retrieveDB();
		credential* getTeachers();
		credential* getStudents();
};


//////////////////////////////////
//	Auth definition		//
//////////////////////////////////
// admin credentials initializer
auth::auth() {
	// initialize the students and teachers
	teachers = new credential;
	students = new credential;
}

auth::auth(database* dbaddress) {
	// initialize the students and teachers
	teachers = new credential;
	students = new credential;

	db = dbaddress;
}

void auth::setDatabase(database* thisdb) {
	db = thisdb;
}

void auth::connectDatabase() {
	if (db == NULL)
		cout << "[-] Can\'t connect to database! Set database first!" << endl;
	else
		db->connect(students, teachers);
}

void auth::addTeacherAccount(string username, string name, string password) {
	teachers->add(username, name, password);
}

void auth::addStudentAccount(string username, string name, string password) {
	students->add(username, name, password);
	// connect to database and add information (admin)
}

void auth::delStudentAccount(string username) {
	students->remove(students->getFirst(), username);
}

void auth::delStudentAccount(int index) {
	students->remove(index);
}

void auth::delTeacherAccount(string username) {
	teachers->remove(teachers->getFirst(), username);
}

void auth::delTeacherAccount(int index) {
	teachers->remove(index);
}

void auth::loginTeacher(string username, string password) {
	if (teachers->matchData(teachers->getFirst(), username, password)) {
		cout << "[+] Logged In!!" << endl;
		// do process here
		// get gradebook from the database and pass it teacher(gradebook*)
		// use the teacher interface here
	} else {
		cout << "[-] Invalid Username or Password!" << endl;
	}
}

void auth::loginStudent(string username, string password) {
	if (students->matchData(students->getFirst(), username, password)) {
		cout << "[+] Logged In!!" << endl;
		// do process here
		// get gradebook from the database and pass it: student(gradebook*)
		// use the student interface here
	} else {
		cout << "[-] Invalid Username or Password!" << endl;
	}
}

database* auth::retrieveDB() { return db; }
credential* auth::getTeachers() { return teachers; }
credential* auth::getStudents() { return students; }

#endif
