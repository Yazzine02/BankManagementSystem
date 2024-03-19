#ifndef CLIENT_H
#define CLIENT_H

#include "Logger.h"
#include "Database.h"
#include <string>

class Client{
private:
	Database db;
	
	int user_id;
	string username,password;
	double balance;
	
public:
	//Constructors
	Client()=default;
	Client(const int& id,const string& un,const string& p,const string& dbPath,const string& errorLogPath,const string& successLogPath);
	
	//GETTERS AND SETTERS
	//id
	int get_userid()const;
	//username
	string get_username()const;
	//void set_username(const string& new_username); 
	//password
	//void set_password(const string& new_password);
	//balance
	double get_balance()const;
	void set_balance(const double& new_balance);
	
	//Methods
	void Deposit(const double& new_balance,const int& id);
	//bool Borrow();
	//bool ReturnLoan();
	void Withdraw(const double& withdraw,const int& id);
	//bool Deposit();
	//void Checkinfo()const;
};


#endif
