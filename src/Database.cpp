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

/*
	When using sqlite3_step:
		SQLITE_DONE if not expecting a result
		SQLITE_ROW if expecting a result
*/
bool Database::isUsernameTaken(const string& username){//true if username taken
    const char* checkUsernameQuery = "SELECT COUNT(*) FROM Client WHERE username=?;";
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
    const char* checkPasswordQuery = "SELECT COUNT(*) FROM Client WHERE password = ?;";
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
	//checking if username or password is taken
    if(isUsernameTaken(username) || isPasswordTaken(password)){
        cerr << "Username or Password is already taken." << endl;
        logger.logError("Username or Password is already taken.");
        return false;
    }
    	//queries
    const char* createClientQuery = "INSERT INTO Client (username,password) VALUES (?, ?);";
    const char* createAccountQuery = "INSERT INTO Account (account_id, balance) VALUES (?, ?);";
    	//statements
    sqlite3_stmt* client_statement;
    sqlite3_stmt* account_statement;
	//preparing BOTH statements
    if(sqlite3_prepare_v2(db,createClientQuery,-1,&client_statement,0) == SQLITE_OK && sqlite3_prepare_v2(db,createAccountQuery,-1,&account_statement,0) == SQLITE_OK){
    	//binding client statement with username and password
        sqlite3_bind_text(client_statement,1,username.c_str(),-1,SQLITE_STATIC);
        sqlite3_bind_text(client_statement,2,password.c_str(),-1,SQLITE_STATIC);
	//executing client insertion and checking if it returns true
        if(sqlite3_step(client_statement) == SQLITE_DONE){
        	//Get client id from the inserted client row
        	int client_id = sqlite3_last_insert_rowid(db);
        	//binding account statement with user id and balance=0.0
        	sqlite3_bind_int(account_statement,1,client_id);//this is an int bind
        	sqlite3_bind_double(account_statement,2,0.0);//this is a double bind
        	//executing account insertion and checking if it returns true
        	if(sqlite3_step(account_statement) == SQLITE_DONE){
        		cout << "User created successfully." << endl;
		    	logger.logSuccess("User created successfully.");
		    	logger.logSuccess("Username: "+username);
		    	logger.logSuccess("Password: "+password);
		    	//finalizing statements
		    	sqlite3_finalize(client_statement);
		    	sqlite3_finalize(account_statement);
		    	return true;
        	}else{
		        cerr << "Error creating account for the user." << endl;
			logger.logError("Error creating account for the user.");
		}
        }
    }
    cerr << "Error creating new user: " << sqlite3_errmsg(db) << endl;
    logger.logError("Error creating new user: "+string(sqlite3_errmsg(db)));
    
    sqlite3_finalize(client_statement);
    sqlite3_finalize(account_statement);
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

//TOOLS
int Database::getUserId(const string& username, const string& password) {
    const char* getUserIdQuery = "SELECT user_id FROM client WHERE username=? AND password=?;";
    sqlite3_stmt* statement;
    int userId = -1; // Default value if user is not found

    if (sqlite3_prepare_v2(db, getUserIdQuery, -1, &statement, 0) == SQLITE_OK) {
        sqlite3_bind_text(statement, 1, username.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(statement, 2, password.c_str(), -1, SQLITE_STATIC);

        if (sqlite3_step(statement) == SQLITE_ROW) {
            // Retrieve the user ID from the query result
            userId = sqlite3_column_int(statement, 0);
        }
    }

    sqlite3_finalize(statement);
    return userId;
}

double Database::getBalance(const int& id){
	const char* getBalanceQuery = "SELECT balance FROM account where account_id=?;";
	sqlite3_stmt* statement;
	double balance=0;
	
	if(sqlite3_prepare_v2(db,getBalanceQuery,-1,&statement,0)==SQLITE_OK){
		sqlite3_bind_int(statement,1,id);
		if(sqlite3_step(statement)==SQLITE_ROW){
			balance = sqlite3_column_double(statement,0);
		}
	}else{
		cerr<<"Error: couldn't get balance."<<sqlite3_errmsg(db)<<endl;
	}
	sqlite3_finalize(statement);
    	return balance;
}

void Database::setBalance(const double& new_balance, const int& id) {
    const char* setBalanceQuery = "UPDATE Account SET balance=? WHERE account_id=?;";
    sqlite3_stmt* statement;

    if (sqlite3_prepare_v2(db, setBalanceQuery, -1, &statement, 0) == SQLITE_OK) {
        sqlite3_bind_double(statement, 1, new_balance);
        sqlite3_bind_int(statement, 2, id);
        
        if (sqlite3_step(statement) != SQLITE_DONE) {
            cerr << "Error updating balance." << endl;
            logger.logError("Error updating balance.");
        }else{
            logger.logSuccess("Balance updated successfully for account ID: " + to_string(id));
        }
    } else {
        cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
        logger.logError("Error preparing statement: " + string(sqlite3_errmsg(db)));
    }

    sqlite3_finalize(statement);
}
