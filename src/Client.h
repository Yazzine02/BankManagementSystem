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
	Client(int id,string un,string p);
	
	//Methods
	//int Balance();
	//bool Borrow();
	//bool ReturnLoan();
	//bool Withdraw();
	//bool Deposit();
	//void Checkinfo()const;
};


#endif
