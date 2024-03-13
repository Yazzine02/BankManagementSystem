#include <iostream>
#include "sqlite3.h"
#include <string>

using namespace std;

#include "Database.h"

int main(){
	Database database("../DBMS/database","logError","logSuccess");
	database.loginUser("test","toztoz");
	return 0;
}