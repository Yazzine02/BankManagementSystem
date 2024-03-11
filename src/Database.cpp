#include "Database.h"

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
