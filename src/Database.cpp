#include "Database.h"
//CONSTRUCTORS
Database::Database(const string& dbPath,const string& errorLogPath,const string& successLogPath)
        :logger(errorLogPath,successLogPath) {
    if (sqlite3_open(dbPath.c_str(), &db) != SQLITE_OK) {
        //cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
        logger.logError("Error opening database: " + string(sqlite3_errmsg(db)));
    } else {
        //cout << "Database connection established successfully." << endl;
        logger.logSuccess("Database connection established successfully.");
    }
}
Database::~Database() {
    if (sqlite3_close(db) != SQLITE_OK) {
        //cerr << "Error closing database: " << sqlite3_errmsg(db) << endl;
        logger.logError("Error closing database: " + string(sqlite3_errmsg(db)));
    } else {
        //cout << "Database connection closed." << endl;
        logger.logSuccess("Database connection closed.");
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
bool Database::createUser(const string& username,const string& password){
    if(isUsernameTaken(username) || isPasswordTaken(password)){
        cerr << "Username or Password is already taken." << endl;
        logger.logError("Username or Password is already taken.");
        return false;
    }
    const char* createUserQuery = "INSERT INTO client (username,password) VALUES (?, ?);";
    sqlite3_stmt* statement;

    if(sqlite3_prepare_v2(db,createUserQuery,-1,&statement,0) == SQLITE_OK){
        sqlite3_bind_text(statement,1,username.c_str(),-1,SQLITE_STATIC);
        sqlite3_bind_text(statement,2,password.c_str(),-1,SQLITE_STATIC);

        if(sqlite3_step(statement) == SQLITE_DONE){
            cout << "User created successfully." << endl;
            logger.logSuccess("User created successfully.");
            logger.logSuccess("Username: "+username);
            logger.logSuccess("Password: "+password);
            sqlite3_finalize(statement);
            return true;
        }
    }
    //cerr << "Error creating new user: " << sqlite3_errmsg(db) << endl;
    logger.logError("Error creating new user: "+string(sqlite3_errmsg(db)));
    sqlite3_finalize(statement);
    return false;
}
bool Database::loginUser(const string& username,const string& password){
    const char* loginUserQuery = "SELECT COUNT(*) FROM client WHERE username=? AND password=?;";
    sqlite3_stmt* statement;
	/*
	By using parameterized queries, the SQLite library ensures that user input is properly 
	sanitized, reducing the risk of SQL injection attacks. Always validate and sanitize user 
	input before using it in SQL queries to protect your application from security vulnerabilities.
	*/
    if(sqlite3_prepare_v2(db,loginUserQuery,-1,&statement,0) == SQLITE_OK){
        sqlite3_bind_text(statement,1,username.c_str(),-1,SQLITE_STATIC);
        sqlite3_bind_text(statement,2,password.c_str(),-1,SQLITE_STATIC);

        if(sqlite3_step(statement) == SQLITE_ROW){
            int count = sqlite3_column_int(statement,0);
            sqlite3_finalize(statement);
            if(count!=1){
            	cout << "Username or Password is wrong."<<endl;
            	logger.logError("Username or Password is wrong.");
            	logger.logSuccess("Username: "+username);
            	logger.logSuccess("Password: "+password);
            }else{
            	cout << "Logged in successfully."<<endl;
            	logger.logSuccess("Logged in successfully.");
            	logger.logSuccess("Username: "+username);
            	logger.logSuccess("Password: "+password);
            }
            return count > 0;
        }
        //cerr << "Username or Password is wrong." << endl;
        return false;
    }
    //cerr << "Error during login: " << sqlite3_errmsg(db) << endl;
    logger.logError("Error during login: " + string(sqlite3_errmsg(db)));
    sqlite3_finalize(statement);
    return false;
}
