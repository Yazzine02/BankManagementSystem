#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include "sqlite3.h"
#include <string>
using namespace std;

class Database {
	sqlite3* db;
public:
	Database()=delete;
	Database(const string& dbPath);
	~Database();
};

#endif // DATABASE_H