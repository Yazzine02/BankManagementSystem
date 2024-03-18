#ifndef CLIENT_H
#define CLIENT_H

#include "Logger.h"
#include "Database.h"
#include <string>

class Client{
private:
	int user_id;
	string username,password;
	
public:
	//Constructors
	Client()=default;
	Client(const int& id,const string& un,const string& p);
	
	//GETTERS AND SETTERS
	int get_userid()const;
	string get_username()const;
	
	void set_password(const string& new_password);
	void set_username(const string& new_username); 
	//Methods
	//int Balance();
	//bool Borrow();
	//bool ReturnLoan();
	//bool Withdraw();
	//bool Deposit();
	//void Checkinfo()const;
};


#endif
