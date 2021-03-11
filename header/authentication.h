#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include "linkedlist.h"
#include "database.h"

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
		gradebooklist* loginTeacher(string, string);		// teacherDatatype
		gradebooklist* loginStudent(string, string, string&);		// studentDatatype

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

gradebooklist* auth::loginTeacher(string username, string password) {
	creds* fnode = teachers->getFirst();
	if (teachers->matchData(fnode, username, password)) {
		cout << "[+] Logged In!!" << endl;

		// retrieve the gradebooklist of teacher
		string name = teachers->search(fnode, username)->name;
		return db->retrieveGBTeacher(name);
	} else {
		cout << "[-] Invalid Username or Password!" << endl;
		return NULL;
	}
}

gradebooklist* auth::loginStudent(string username, string password, string &stname) {
	creds* fnode = students->getFirst();
	if (students->matchData(fnode, username, password)) {
		cout << "[+] Logged In!!" << endl;

		// retrieve the student name
		string name = students->search(fnode, username)->name;
		stname = name;
		return db->retrieveGBStudent(name);
	} else {
		cout << "[-] Invalid Username or Password!" << endl;
		return NULL;
	}
}

database* auth::retrieveDB() { return db; }
credential* auth::getTeachers() { return teachers; }
credential* auth::getStudents() { return students; }

#endif
