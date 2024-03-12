#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include "sqlite3.h"
#include <string>
using namespace std;

class Database {
	sqlite3* db;
public:
	//CONSTRUCTORS
	Database()=delete;
	Database(const string& dbPath);
	~Database();
	//CREDENTIAL CHECKERS
	bool isUsernameTaken(const string& username);
	bool isPasswordTaken(const  string& password);
	//USER AUTHENTICATION
	bool createUser(const string& username,const string& password);
	bool loginUser(const string& username,const string& password);
};

#endif // DATABASE_H