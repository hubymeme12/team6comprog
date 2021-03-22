#ifndef DATABASE_H
#define DATABASE_H

#include "linkedlist.h"
#include "gradebook.h"

// target: data retrieval for teachers and students
// push data to the database (will be done by the admin)

class database {
	public:
		// setup
		database();
		~database();

		void connect(credential* stud, credential* teac);		// connects the node from authentication to database
		void pseudonodecopy();									// copies the original node (student) to pseudostudent (for table purposes)
		void pseudonodedelete(int);								// deletes node from pseudostudent nodes
		void pseudonodedelete(string);							// deletes node with use of name
		void addnode(gradebook*, int);							// adds node from pseudostudent to addme (that will be passed in triad)
		void addnode(gradebook*, string);						// same as addnode, but uses name as parameter instead of index

		// add data
		void pushdata(gradebook*, string, credential*);			// push these data to tridata
		void deletedata(string tname);							// deletes subject through teacher name
		void deletedata(int index);								// deletes subject through index

		// data retrieval
		gradebooklist* retrieveGBTeacher(string teachername);	// retrieves gradebooks with matched teachername
		gradebooklist* retrieveGBStudent(string studname);		// retrieves gradebooks with matched student username??
		gradebooklist* retrieveglist();							// retrieves all subjects registered
		credential* returnpseudonode();							// returns the pseudonode (for table)
		credential* addednode();								// returns all selected node
		tridata* retrievedata();
		char* getbuffer();										// get the data with followd format for file binary writing
		int getbuffersize() const;								// returns the size of buffer
	
		// some debug
		void printpseudonode() {
			creds* x = pseudostudent->getFirst();
			
			cout << endl << "======= pseudonodes debug ========" << endl;
			while (x != NULL) {
				cout << "Current user : " << x->name << endl;
				x = x->next;
			}
			cout << "========== pseudonode debug done =========" << endl << endl;
		}
	private:
		tridata* db_table;
		credential* student;
		credential* teacher;
		credential* pseudostudent;
		credential* addme;

		int buffersize;
};

// additional function for encryption
char* xorEnc(string password) {
	char simple[] = "THISISAKEY";
	char* returnme = new char[password.size()];

	for (int i = 0; i < password.size() + 1; i++) {
		returnme[i] = password[i] ^ simple[i % 10];
	}

	return returnme;
}

//////////////////////////////////
//	Database definition	//
//////////////////////////////////
// constructor
database::database() {
	db_table = new tridata;
}

// self destruct
database::~database() {
	cout << "[!] releasing memory : " << &db_table << endl;
	delete db_table;
	cout << "[!] releasing memory : " << &db_table << endl;
	cout << "[!] releasing memory : " << &db_table << endl;
	cout << "[!] releasing memory : " << &db_table << endl;
	cout << "[!] releasing memory : " << &db_table << endl;
}

// connects address for changes
void database::connect(credential* stud, credential* teac) {
	student = stud;
	teacher = teac;
}

// copies the nodes for student selection
void database::pseudonodecopy() {
	// handler setup
	pseudostudent = new credential;
	addme = new credential;

	if (student != NULL) {
		// from first to last node
		creds* node = student->getFirst();

		// walk through
		while (node != NULL) {
			pseudostudent->add(node->user, node->name, node->pass);
			node = node->next;
		}


	} else {
		cout << "[!] Cannot copy! no students are present" << endl;
	}
}

// deletes nth pseudo node
void database::pseudonodedelete(int index) {
	if (index > pseudostudent->getlistnum()) {
		cout << "[!] Cannot delete selected node! Index exceeded the size of node" << endl;
	} else {
		pseudostudent->remove(index);
	}
}

// deletes node throug =h name
void database::pseudonodedelete(string name) {
	// retrieve name
	pseudostudent->remove(pseudostudent->getFirst(), name);
}

// add node to addme node from pseudostudent
void database::addnode(gradebook* gb, int index) {
	if (index > pseudostudent->getlistnum() || index == 0) {
		cout << "[!] Cannot add node! Index exceeded the size of node" << endl;
	} else {
		// retrieve this nth node
		creds* node = pseudostudent->getNode(index);

		if (node != NULL) {
			// add name to gradebook
			gb->pushdata(node->name, 0.0);
			addme->add(node->user, node->name, node->pass);

			// delete this nth from pseudonode
			pseudonodedelete(index);
		}
	}
}

// add node to addme node from pseudostudent
void database::addnode(gradebook* gb, string name) {
	creds* node = pseudostudent->searchname(pseudostudent->getFirst(), name);

	if (node != NULL) {
		// add this node to addme and delete it
		gb->pushdata(node->name, 0.0);

		addme->add(node->user, node->name, node->pass);

		// deletes this node
		pseudonodedelete(node->user);
	}
}

// pushes data to tridata
void database::pushdata(gradebook* gb, string teachername, credential* stud) {
	db_table->addData(gb, teachername, stud);
}

// deletes data on tridata
void database::deletedata(string tname) {
	db_table->removeSubject(tname);
}

// deletes data on tridata through index
void database::deletedata(int index) {
	db_table->removeSubject(index);
}

// retrieves the subjects for this teacher
gradebooklist* database::retrieveGBTeacher(string teachername) {
	// makes graedebooklist where data will be pushed
	// gradebooklist that will be returned
	// fnode that will be crawled on for retrieval
	tridata* retrievedtriads = new tridata;
	gradebooklist* retrieved = new gradebooklist;
	triad* fnode;

	// retrieve triads with matched teachers and push values to retrievedtriads
	db_table->retrieveTnodes(retrievedtriads, teachername);
	fnode = retrievedtriads->getFirst();

	// recover the gradebooks
	while (fnode != NULL) {
		// push the gradebookdata
		retrieved->pushBack(fnode->subject);
		fnode = fnode->next;
	}

	return retrieved;
}

// retrieves the subjects for this student
// ill be using username here to use less process
gradebooklist* database::retrieveGBStudent(string studentname) {
	// tridata object where retrieved triads will be stored
	tridata* store = new tridata;
	gradebooklist* gblist = new gradebooklist;
	triad* fnode;

	// retrieval
	db_table->retrieveSnodes(store, studentname);
	fnode = store->getFirst();

	// recover and store to gradebook
	while (fnode != NULL) {
		gblist->pushBack(fnode->subject);
		fnode = fnode->next;
	}

	return gblist;
}

gradebooklist* database::retrieveglist() {
	return db_table->retrieveall();
}

credential* database::returnpseudonode() { return pseudostudent; }
credential* database::addednode() { return addme; }
tridata* database::retrievedata() { return db_table; }

// for returning buffer in file output
// format:
char* database::getbuffer() {
	// need the authentication to write first
	int size;
	char* buffer;
	creds* node;
	string data = "";

	// retrieve teacher node first
	node = teacher->getFirst();
	data += "@credsT@\n";
	while (node != NULL) {
		// get the credentials in format; <user> <name> <pass>
		data += "\t" + node->name + "," + node->user + "," + node->pass + "\n";
		node = node->next;
	}
	data += "@credTE@\n\n";

	// retrieve student node
	node = student->getFirst();
	data += "@credsS@\n";
	while (node != NULL) {
		data += "\t" + node->name + "," + node->user + "," + node->pass + "\n";
		node = node->next;
	}
	data += "@credSE@\n\n";


	// for the subjects
	triad* dbnode = db_table->getFirst();

	// data += "@gblist@\n";
	while (dbnode != NULL) {
		// format:
		// @gblist@
		// @sgbook@
		// SUBJECTNAME
		// TEACHERNAME
		//		STUD1
		//		STUD2
		//		...
		// @egbook@
		// @sgbook@
		// ...
		// @egbook@
		// @egblist@

		// fetch data
		data += "@sgbook@\n";
		data += dbnode->subject->getcourseName() + "\n";
		data += dbnode->teacher + "\n";

		// fetch student names
		creds* studnode = dbnode->students->getFirst();

		if (studnode != NULL) {
			data += "\t" + studnode->name;
			studnode = studnode->next;
		}

		while (studnode != NULL) {
			data += "," + studnode->name;
			studnode = studnode->next;
		}

		// student names done
		data += "\n";

		// proceed to next
		dbnode = dbnode->next;
		data += "@egbook@\n";
	}
	// data += "@egblis@\n";

	// convert this into file buffer
	size = data.size();
	buffer = new char[size];

	// fuck the ram, so i have to put + 1.
	for (int i = 0; i < (size + 1); i++) {
		// copy the string to buffer
		buffer[i] = data[i];
	}

	// assign size of buffer
	buffersize = size;
	return buffer;
}

int database::getbuffersize() const {
	return buffersize;
}

//////////////////////////
// 	E N D 		//
//////////////////////////
#endif
