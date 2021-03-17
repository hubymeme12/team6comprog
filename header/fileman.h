#ifndef FILEMAN_H
#define FILEMAN_H

#include <fstream>
#include <iostream>
using namespace std;

// admin contains database and authentication
// which are needed objects in this header file
// admin contains all the data needed
// so writing the bytes of admin is the easiest move we can do
#include "admin.h"

class fileman {
	private:
		admin* data;
	public:
		fileman();
		fileman(admin*);

		// addition of data
		void addData(admin*);
		
		// writing data
		// using parameter as name or by default, using "binary.dat"
		void save(char*);
		void save();

		// reading data and store to first param
		void read(admin*, char*);
		void read(admin&, char*);

		// look through information
		// look for numbers of teachers
		// numbers of students
		// numbers of subjects
};

// definition of fileman object
fileman::fileman() {
	data = NULL;
}

// use this param as the data to be saved
fileman::fileman(admin* obj) {
	data = obj;
}

// manual addition of data
void fileman::addData(admin* obj) {
	data = obj;
}

// saving file with file name
void fileman::save(char* fname) {
	ofstream ofile(fname, ios::out | ios::binary);
	
	// writing file
	ofile.write((char*)(&data), sizeof(data));
	
	// closing file
	ofile.close();
}

// saving file by default
void fileman::save() {
	ofstream ofile("binary.dat", ios::out | ios::binary);

	// writing file
	ofile.write((char*)(&data), sizeof(data));

	// closing file
	ofile.close();
}

// reading file
void fileman::read(admin* passme, char* name) {
	ifstream infile(name, ios::in | ios::binary);

	// variables needed
	int size;
	char* handler;

	// calculates the size of binary
	infile.seekg(0, infile.end);
	size = infile.tellg();
	infile.seekg(0, infile.beg);

	// allocate array for binary of this file
	handler = new char[size];
	
	// read the data
	infile.read(handler, size);
	
	// pass the data
	passme = (admin*)handler;
}

#endif
