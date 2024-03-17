#ifndef ATM_H
#define ATM_H

#include <iostream>
#include <string>
#include "Client.h"
#include "Database.h"

using namespace std;

class ATM{
	private:
		Client client;
		Database db;
	public:
		//Constructor
		ATM(const string& dbPath,const string& errorLogPath,const string& successLogPath);
		//authentication interfaces
		void login(string& username,string& password);
		void signin(string& username,string& password);
		void logout();
		//Utility Interfaces
		//void Balance()const;
		//void Deposit();
		//void Borrow();
		//void ReturnLoan();
		//void Withdraw();
		void checkinfo()const;

};

#endif
