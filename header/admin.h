#include <iostream>
#include "authentication.h"
#include "database.h"
using namespace std;

class admin {
	private:
		database* db;
		auth* secret;

		string adminuser;
		string adminpass;
	public:
		admin();
		admin(string, string);
};

//////////////////////////
//	admin		//
//////////////////////////
admin::admin() {
	db = new database;
	secret = new auth;

	adminuser = "admin";
	adminpass = "admin";
}

admin::admin(string username, string password) {
	admin();
	adminuser = username;
	adminpass = password;
}
