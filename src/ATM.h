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
		void Login();
		void SignIn();
		void Logout();
		//Utility Interfaces
		//void Balance()const;
		//void Deposit();
		//void Borrow();
		//void ReturnLoan();
		//void Withdraw();
		void Checkinfo()const;

};

#endif
