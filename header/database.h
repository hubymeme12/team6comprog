#ifndef DATABASE_H
#define DATABASE_H

#include "linkedlist.h"
#include "gradebook.h"

// target: data retrieval for teachers and students
// push data to the database (will be done by the admin)

class database {
	public:
		// setup
		void connect(credential* stud, credential* teac);		// connects the node from authentication to database
		void pseudonodecopy();						// copies the original node (student) to pseudostudent (for table purposes)
		void pseudonodedelete(int);					// deletes node from pseudostudent nodes
		void addnode(gradebook*, int);					// adds node from pseudostudent to addme (that will be passed in triad)

		// add data
		void pushdata(gradebook*, string, credential*);			// push these data to tridata

		// data retrieval
		gradebooklist* retrieveGBTeacher(string teachername);		// retrieves gradebooks with matched teachername
		gradebooklist* retrieveGBStudent(string studname);		// retrieves gradebooks with matched student username??
		credential* returnpseudonode();					// returns the pseudonode (for table)
		credential* addednode();					// returns all selected node
		tridata* retrievedata();
	private:
		tridata db_table;
		credential* student;
		credential* teacher;
		credential* pseudostudent;
		credential* addme;
};

//////////////////////////////////
//	Database definition	//
//////////////////////////////////
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

// add node to addme node from pseudostudent
void database::addnode(gradebook* gb, int index) {
	if (index > pseudostudent->getlistnum()) {
		cout << "[!] Cannot add node! Index exceeded the size of node" << endl;
	} else {
		// retrieve this nth node
		creds* node;
		node = pseudostudent->getNode(index);

		if (node != NULL) {
			// add name to gradebook
			gb->pushdata(node->name, 0.0);
			addme->add(node->user, node->name, node->pass);

			// delete this nth from pseudonode
			pseudonodedelete(index);
		}
	}
}

// pushes data to tridata
void database::pushdata(gradebook* gb, string teachername, credential* stud) {
	db_table.addData(gb, teachername, stud);
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

// retrieves the subjects for this student
// ill be using username here to use less process
gradebooklist* database::retrieveGBStudent(string studentname) {
	// tridata object where retrieved triads will be stored
	tridata* store = new tridata;
	gradebooklist* gblist = new gradebooklist;
	triad* fnode;

	// retrieval
	db_table.retrieveSnodes(store, studentname);
	fnode = store->getFirst();

	// recover and store to gradebook
	while (fnode != NULL) {
		gblist->pushBack(fnode->subject);
		fnode = fnode->next;
	}

	return gblist;
}

credential* database::returnpseudonode() { return pseudostudent; }
credential* database::addednode() { return addme; }
tridata* database::retrievedata() { return &db_table; }
//////////////////////////
// 	E N D 		//
//////////////////////////
#endif
