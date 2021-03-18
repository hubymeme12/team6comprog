#include <fstream>
#include "database.h"

// pass this header to admin for writing file
// writing file and file interpretation
// since we are using linked list as database
// we need to manually write the data
class fileman {
	private:
		// file buffer and filename
		char* buffer;
		char* fname;
	public:
		// constructor for preparation of filename
		fileman();
		fileman(char*);

		// some process setup
		void target(char*);

		// read data
		char* read();
		void write();

		// append the data to current file
		void append();
};

// use gradebook and pass to gradebook list
// string buffer finder is a must
class gbparser : public fileman {

};

//
class authparser : public fileman {
};
