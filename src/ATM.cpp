#include "ATM.h"

ATM::ATM(const string& dbPath,const string& errorLogPath,const string& successLogPath):db(dbPath,errorLogPath,successLogPath){
	bool continue_loop = true;
	while(continue_loop){
		cout<<"Welcome to the ATM machine project!"<<endl;
		cout<<"Select how you want to connect by entering the corresponding number: "<<endl;
		cout<<"1. Login."<<endl;
		cout<<"2. Sign up."<<endl;
		cout<<"0. Exit the program."<<endl;
		//Necessary variables to store input data
		int option = 0;
		string username="",password="";
		cin>>option;
		cin.ignore();
		switch(option){
			case 1:{ //login functionality
				login(username,password);
				int user_id = db.getUserId(username,password);
				if(user_id == -1)exit(EXIT_FAILURE);
				Client client(user_id,username,password,"/home/yazzine/Desktop/Projects/BankManagementSystem/DBMS/database","/home/yazzine/Desktop/Projects/BankManagementSystem/src/logError","/home/yazzine/Desktop/Projects/BankManagementSystem/src/logSuccess");
				client_interface(client);
				continue_loop=false;
				break;
			}
				
			case 2:{ //signup functionality
				signup(username,password);
				int user_id = db.getUserId(username,password);
				if(user_id == -1)exit(EXIT_FAILURE);
				Client client(user_id,username,password,"/home/yazzine/Desktop/Projects/BankManagementSystem/DBMS/database","/home/yazzine/Desktop/Projects/BankManagementSystem/src/logError","/home/yazzine/Desktop/Projects/BankManagementSystem/src/logSuccess");
				client_interface(client);
			    	continue_loop=false;
			    	break;
			}
			    
			case 0:{ //exit program
				cout << "Exiting the program. Goodbye!" << endl;
			    	exit(EXIT_SUCCESS);
			    	break;
			}
			    
			default:{ //invalid input
				cout << "Invalid option. Please select a valid option." << endl;
			    	break;	
			}
			    
		};
	}
}
//AUTHENTICATION INTERFACES
void ATM::login(string& username,string& password){
	int attempts = 3;
	bool login_success = false;
	while(attempts>0 && !login_success){
		cout<<"LOG IN"<<endl;
		cout<<"Username:"<<endl;
		cin>>username;
		cin.ignore();
		cout<<"Password:"<<endl;
		cin>>password;
		cin.ignore();
		if(db.loginUser(username,password)){	
			login_success=true;	
		}else{
			cout<<"Login Incorrect. "<< attempts - 1 << " attempts remaining." << endl;
			login_success=false;
			attempts--;
		}
	}			
	if(attempts==0){
		cout<<"Maximum number of login attempts reached. Exiting the program. Goodbye!"<<endl;
		exit(EXIT_FAILURE);
	}
}

void ATM::signup(string& username,string& password){
	int attempts = 5;
	bool createuser_success = false;
	while(attempts>0 && !createuser_success){
		cout<<"CREATE ACCOUNT"<<endl;
		cout<<"Username:"<<endl;
		cin>>username;
		cin.ignore();
		cout<<"Password:"<<endl;
		cin>>password;
		cin.ignore();
		if(db.createUser(username,password)){ //executes when creating user in database successfully
			cout<<"Created User successfully."<<endl;
			createuser_success = true;
		}else{ //diminishing number of attempts
			cout<< attempts - 1 << " attempts remaining." << endl;
			createuser_success=false;
			attempts--;
		}
	}
	if(attempts==0){//3 false attempts => program exit
		cout<<"Maximum number of sign in attempts reached. Exiting the program. Goodbye!"<<endl;
		exit(EXIT_FAILURE);
	}
}

void ATM::client_interface(Client& client){
	bool exit_program = false;
	while(!exit_program){
		cout<<"Welcome Mr.Ms "<<client.get_username()<<endl;
		cout<<"What can we do for you?" <<endl;
		cout<<"1. Check credentials"<<endl;
		cout<<"2. Check balance"<<endl;
		cout<<"3. Deposit"<<endl;
		cout<<"4. Withdraw"<<endl;
		cout<<"0. Exit"<<endl;
		int option = 0;
		cin >> option;
		cin.ignore();
		switch(option){
			case 1:{ //checking credentials
				cout<<"User ID: "<<client.get_userid()<<endl;
				cout<<"Username: "<<client.get_username()<<endl;
				break;
			}
				
			case 2:{ //checking balance
				cout<<"Balance: MAD "<<client.get_balance()<<endl;
			    	break;
			}
			
			case 3:{ //deposit functionality
				DepositFunctionality(client);
			    	break;
			}
			case 4:{ //withdraw functionality
				WithdrawFunctionality(client);
			    	break;
			}
			case 0:{ //exit program
				cout << "Exiting the program. Goodbye!" << endl;
			    	exit(EXIT_SUCCESS);
			    	break;
			}
			    
			default:{ //invalid input
				cout << "Invalid option. Please select a valid option." << endl;
			    	break;	
			}
		}
	}
}

//CLIENT FUNCTIONALITIES
void ATM::DepositFunctionality(Client& client){
	double deposit = 0;
	cout<<"Balance: MAD "<<client.get_balance()<<endl;
	cout<<"Enter the ammount you want to deposit: "<<endl;
	cin>>deposit;
	cin.ignore();
	client.Deposit(deposit,client.get_balance());	
}

void ATM::WithdrawFunctionality(Client& client){
	//void Withdraw(const double& withdraw,const int& id)
	double withdraw = 0;
	cout<<"Balance: MAD "<<client.get_balance()<<endl;
	cout<<"Enter the ammount you want to withdraw: "<<endl;
	cin>>withdraw;
	cin.ignore();
	client.Withdraw(withdraw,client.get_userid());
}
