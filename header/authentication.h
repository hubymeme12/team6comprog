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
		database db;
		string adminuser;
		string adminpass;
	public:
		// constructors
		auth();
		auth(string, string);

		// account management
		void addTeacherAccount(string, string, string);
		void addStudentAccount(string, string, string);
		void delTeacherAccount(string);
		void delStudentAccount(string);

		// credentials validation
		void loginTeacher(string, string);		// teacherDatatype
		void loginStudent(string, string);		// studentDatatype

		// debug
		void retrieveDB();
};

class authVisuals {
	void credsTable(const auth smoldb) const;
};




//////////////////////////////////
//	Auth definition		//
//////////////////////////////////
// admin credentials initializer
auth::auth() {
	adminuser = "admin";
	adminpass = "pass";

	// initialize the students and teachers
	teachers = new credential;
	students = new credential;

	// connects to database
	db.connect(students, teachers);
}

auth::auth(string username, string password) {
	adminuser = username;
	adminpass = password;

	// initialize the students and teachers
	teachers = new credential;
	students = new credential;

	// connects to database
	db.connect(students, teachers);
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

void auth::delTeacherAccount(string username) {
	teachers->remove(teachers->getFirst(), username);
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
#endif
