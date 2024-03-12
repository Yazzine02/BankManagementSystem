#include "Database.h"
//CONSTRUCTORS
Database::Database(const string &dbName) {
    if (sqlite3_open(dbName.c_str(), &db) != SQLITE_OK) {
        cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
    } else {
        cout << "Database connection established successfully." << endl;
    }
}
Database::~Database() {
    if (sqlite3_close(db) != SQLITE_OK) {
        cerr << "Error closing database: " << sqlite3_errmsg(db) << endl;
    } else {
        cout << "Database connection closed." << endl;
    }
}

//CREDENTIAL CHECKERS
/*
    1-initialize statement as an object of sqlite3_stmt*
    2-Create the prepared statement object using sqlite3_prepare_v2().
    3-Bind values to parameters using the sqlite3_bind_*() interfaces.
    4-Run the SQL by calling sqlite3_step() one or more times.
    5-Reset the prepared statement using sqlite3_reset() then go back to step 2. Do this zero or more times.
    6-Destroy the object using sqlite3_finalize().
*/
bool Database::isUsernameTaken(const string& username){//true if username taken
    const char* checkUsernameQuery = "SELECT COUNT(*) FROM client WHERE username=?;";
    sqlite3_stmt* statement;//step 1
    if(sqlite3_prepare_v2(db,checkUsernameQuery,-1,&statement,0) != SQLITE_OK){//step 2 and 6
        sqlite3_finalize(statement);
        return false;
    }else{
        sqlite3_bind_text(statement,1,username.c_str(),-1,SQLITE_STATIC);//step 3
        if(sqlite3_step(statement) == SQLITE_ROW){//step 4
            int count = sqlite3_column_int(statement,0);
            sqlite3_finalize(statement);//step 6
            return count > 0;
        }
        sqlite3_finalize(statement);//step 6
        return false;
    }
}
bool Database::isPasswordTaken(const string& password){
    const char* checkPasswordQuery = "SELECT COUNT(*) FROM client WHERE password = ?;";
    sqlite3_stmt* statement;
    if(sqlite3_prepare_v2(db,checkPasswordQuery,-1,&statement,0) == SQLITE_OK){
        sqlite3_bind_text(statement,1,password.c_str(),-1,SQLITE_STATIC);
        if(sqlite3_step(statement) == SQLITE_ROW){
            int count = sqlite3_column_int(statement,0);
            sqlite3_finalize(statement);
            return count > 0;
        }
    }
    sqlite3_finalize(statement);
    return false;
}
//USER AUTHENTICATION
bool Database::createUser(const string& username,const string& password){}
bool Database::loginUser(const string& username,const string& password){}