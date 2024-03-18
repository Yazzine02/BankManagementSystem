#ifndef ATM_H
#define ATM_H

#include <iostream>
#include <string>
#include "Client.h"
#include "Database.h"

using namespace std;

class ATM{
	private:
		Database db;
	public:
		//Constructor
		ATM(const string& dbPath,const string& errorLogPath,const string& successLogPath);
		//AUTHENTICATION INTERFACES
		void login(string& username,string& password);
		void signup(string& username,string& password);
		void logout();
		//UTILITY INTERFACES
		//void Balance()const;
		//void Deposit();
		//void Borrow();
		//void ReturnLoan();
		//void Withdraw();
		void client_interface(Client& client);
		
		//CLIENT FUNCTIONALITIES
		void DepositFunctionality(Client& client);
};

#endif
