#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <sqlite3.h>
#include <string>
#include "Logger.h"
using namespace std;

class Database {
	sqlite3* db;
	Logger logger;
	//CREDENTIAL CHECKERS
	bool isUsernameTaken(const string& username);
	bool isPasswordTaken(const  string& password);
public:
	//CONSTRUCTORS
	Database()=delete;
	Database(const string& dbPath,const string& errorLogPath,const string& successLogPath);
	~Database();
	
	//USER AUTHENTICATION
	bool createUser(const string& username,const string& password);
	bool loginUser(const string& username,const string& password);
	
	//TOOLS
	int getUserId(const string& username,const string& password);
};

#endif // DATABASE_H
