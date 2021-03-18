#ifndef FILEMAN_H
#define FILEMAN_H

#include <fstream>
#include "database.h"
#include "authentication.h"

// pass this header to admin for writing file
// writing file and file interpretation
// since we are using linked list as database
// we need to manually write the data
class fileman {
	private:
		// file buffer and filename
		char* buffer;
		char* fname;
		int filesize;
	public:
		// constructor for preparation of filename
		fileman();
		fileman(char*);

		// some process setup
		void target(char*);
		void retrievedata(database*);				// retrieves data from the database

		// bool : flag for encrypted or not
		char* read(bool);
		void write(bool);
};

// use gradebook and pass to gradebook list
// string buffer finder is a must
class gbparser : public fileman {

};

// parse authentication and pass to values
class authparser : public fileman {
};


////////////////////////////////
// FILE MANIPULATOR DEFINITION//
////////////////////////////////
fileman::fileman() {
	buffer = NULL;
	fname = NULL;
}

fileman::fileman(char* name) {
	fname = name;
}

// manually add file name
void fileman::target(char* name) {
	fname = name;
}

// retrieves data that will be written
void fileman::retrievedata(database* ptr) {
	buffer = ptr->getbuffer();
	filesize = ptr->getbuffersize();
}

// read file and know if this is encrypted
char* fileman::read(bool encrypted) {
	ifstream reader(fname, ios::binary | ios::ate);

	// get size
	filesize = reader.tellg();
	
	// allocate buffer
	buffer = new char[filesize];

	// back to normal
	reader.seekg(0, reader.beg);
	
	// read and pass to buffer
	reader.read(buffer, filesize);
	
	// check if encrypted or not
	if (encrypted) {
		return xorEnc(buffer);
	} else {
		return buffer;
	}
}

// writing file bytes
void fileman::write(bool encrypted) {
	ofstream writer(fname, ios::binary);
	writer.write(buffer, filesize);
}
//////////////////////////////////
//	END OF FILEMAN DEFINITION	//
//////////////////////////////////
#endif
