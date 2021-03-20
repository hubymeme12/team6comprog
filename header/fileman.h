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
	protected:
		// file buffer and filename
		char* buffer;
		char* fname;
		int filesize;
	public:
		// constructor for preparation of filename
		fileman();
		fileman(char*);

		// some process setup
		void target(char*);							// setups target file
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
	private:
		auth* accounts;
	public:
		// constructor
		authparser();
		authparser(char*, auth*);

		// utilities
		void addauth(auth*);		// add target auth object to fill in values
		bool fillauth(bool);			// push in account values in auth object
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

	// error checking
	if (!reader.fail()) {
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
	} else {
		cerr << "[Error] The filename had a shit name." << endl;
		cerr << "Returning NULL..." << endl;
		return NULL;
	}
}

// writing file bytes
void fileman::write(bool encrypted) {
	ofstream writer(fname, ios::binary);

	if (!writer.fail()) {
		if (encrypted)
			writer.write(xorEnc(buffer), filesize);
		else
			writer.write(buffer, filesize);
	} else {
		cerr << "[Error] Uhh.. I donno... probably the file name u entered is in use." << endl;
	}
}
//////////////////////////////////
//	END OF FILEMAN DEFINITION	//
//////////////////////////////////

//////////////////////////////
//	AUTH PARSER DEFINITION	//
//////////////////////////////
authparser::authparser(): fileman(){
	// initialize local variables values
	accounts = NULL;
}

authparser::authparser(char* fname, auth* authaddress): fileman(fname) {
	accounts = authaddress;
}

// add target authentication object
void authparser::addauth(auth* target) {
	accounts = target;
}

// parse file bytes by reading values
// need to confirm if the file is encrypted first
bool authparser::fillauth(bool enc) {
	// confirmation for filename
	if (fname == NULL) {
		cout << "[Error] No filename added!" << endl;
	} else if (accounts == NULL) {
		cout << "[Error] Setup auth object properly!" << endl;
	} else {
		// read filename bytes
		// and store it to its local variable
		// returning to nowhere
		buffer = read(enc);
		char flag[] = "@credsT@";
		char flagend[] = "@credTE@";

		// too lazy to adjust the whole codee
		if (buffer == NULL) {
			return 0;
		}

		// this will be used as first value in next loop
		int updated;

		cout << "[+] Loading accounts (Teachers) :" << endl;
		// walk through buffer until we find @credsT@
		for (int i = 0; i < filesize - 8; i++) {
			if (flag[0] == buffer[i] &&
				flag[1] == buffer[i + 1] &&
				flag[2] == buffer[i + 2] &&
				flag[3] == buffer[i + 3] &&
				flag[4] == buffer[i + 4] &&
				flag[5] == buffer[i + 5] &&
				flag[6] == buffer[i + 6] &&
				flag[7] == buffer[i + 7]) {

				// cout << "MATCHEDD!!!" << endl;
				// get the accounts of teachers here
				// skip the current buffers
				i += 8;
				// cout << "Buffer after match : " << buffer[i] << " Fonr" << endl;

			} else if (flagend[0] = buffer[i] &&
				flagend[1] == buffer[i + 1] &&
				flagend[2] == buffer[i + 2] &&
				flagend[3] == buffer[i + 3] &&
				flagend[4] == buffer[i + 4] &&
				flagend[5] == buffer[i + 5] &&
				flagend[6] == buffer[i + 6] &&
				flagend[7] == buffer[i + 7]) {

				// end of the fucking bitch ass checking
				// teacher accounts
				// cout << "END MATCHED!!!" << endl;
				break;
			} else if (buffer[i] == '\t'){
				// for the next character
				++i;

				// yeah damn it, crawl and find the commas bitch
				char uname[100] = {'\0'};
				char name[100] = {'\0'};
				char pass[100] = {'\0'};
				int indx = 0;

				// name retrieval
				while (buffer[i] != ',') {
					name[indx] = buffer[i];
					++indx;
					++i;
				} cout << "Name : " << name << endl;
				++i;
				indx = 0;

				// username retrieval
				while (buffer[i] != ',') {
					uname[indx] = buffer[i];
					++indx;
					++i;
				} cout << "Username : " << uname << endl;
				++i;
				indx = 0;

				// password retrieval
				while (buffer[i] != '\n') {
					pass[indx] = buffer[i];
					++indx;
					++i;
				} cout << "Password : " << pass << endl << endl;

				// append these data to linked list
				accounts->addTeacherAccount(uname, name, pass);
			}

			// where the loop stops
			updated = i;
		}

		char sflag[] = "@credsS@";
		char sflagend[] = "@credSE@";

		cout << "[+] Loading accounts (Students) :" << endl;
		// walk through buffer until we find @credsT@
		for (int i = updated; i < filesize - 8; i++) {
			if (sflag[0] == buffer[i] &&
				sflag[1] == buffer[i + 1] &&
				sflag[2] == buffer[i + 2] &&
				sflag[3] == buffer[i + 3] &&
				sflag[4] == buffer[i + 4] &&
				sflag[5] == buffer[i + 5] &&
				sflag[6] == buffer[i + 6] &&
				sflag[7] == buffer[i + 7]) {

				// cout << "MATCHEDD!!!" << endl;
				// get the accounts of teachers here
				// skip the current buffers
				i += 8;
				// cout << "Buffer after match : " << buffer[i] << " Fonr" << endl;

			} else if (sflagend[0] = buffer[i] &&
				sflagend[1] == buffer[i + 1] &&
				sflagend[2] == buffer[i + 2] &&
				sflagend[3] == buffer[i + 3] &&
				sflagend[4] == buffer[i + 4] &&
				sflagend[5] == buffer[i + 5] &&
				sflagend[6] == buffer[i + 6] &&
				sflagend[7] == buffer[i + 7]) {

				// end of the fucking bitch ass checking
				// of teacher accounts
				// cout << "END MATCHED!!!" << endl;
				break;
			} else if (buffer[i] == '\t'){
				// for the next character
				++i;

				// yeah damn it, crawl and find the commas bitch
				char uname[100] = {'\0'};
				char name[100] = {'\0'};
				char pass[100] = {'\0'};
				int indx = 0;

				// name retrieval
				while (buffer[i] != ',') {
					name[indx] = buffer[i];
					++indx;
					++i;
				} cout << "Name : " << name << endl;
				++i;
				indx = 0;

				// username retrieval
				while (buffer[i] != ',') {
					uname[indx] = buffer[i];
					++indx;
					++i;
				} cout << "Username : " << uname << endl;
				++i;
				indx = 0;

				// password retrieval
				while (buffer[i] != '\n') {
					pass[indx] = buffer[i];
					++indx;
					++i;
				} cout << "Password : " << pass << endl << endl;

				// append these data to linked list
				accounts->addStudentAccount(uname, name, pass);
			}
		}
		
		// yeah shit
		return true;
	}
}
//////////////////////////
//	END OF AUTHPARSER	//
//////////////////////////
#endif
