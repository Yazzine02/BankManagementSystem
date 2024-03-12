#include <iostream>
#include "sqlite3.h"
#include <string>

using namespace std;

#include "Database.h"

int main(){
	Database database("../DBMS/database");
	if(database.isUsernameTaken("test")){
		cout << "Username test is taken" << endl;
	}else {
		cout << "Username test is not taken" << endl;
	}
	return 0;
}