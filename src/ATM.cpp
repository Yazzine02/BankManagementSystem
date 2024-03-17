#include "ATM.h"

ATM::ATM(const string& dbPath,const string& errorLogPath,const string& successLogPath):db(dbPath,errorLogPath,successLogPath){
	bool continue_loop = true;
	while(continue_loop){
		cout<<"Welcome to the ATM machine project!"<<endl;
		cout<<"Select how you want to connect by entering the corresponding number: "<<endl;
		cout<<"1.Login."<<endl;
		cout<<"2.Sign up."<<endl;
		cout<<"0.Quit the program."<<endl;
		//Necessary variables to store input data
		int option = 0;
		string username="",password="";
		cin>>option;
		cin.ignore();
		switch(option){
			case 1:
				login(username,password);
				continue_loop=false;
				break;
			case 2:
			    signin(username,password);
			    continue_loop=false;
			    break;
			case 0:
			    cout << "Exiting the program. Goodbye!" << endl;
			    exit(EXIT_SUCCESS);
			    break;
			default:
			    cout << "Invalid option. Please select a valid option." << endl;
			    break;
		};
	}
}

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
			cout<<"Welcome Mr.Ms "<<username<<endl;	
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

void ATM::signin(string& username,string& password){
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
		if(db.createUser(username,password)){
			cout<<"Created User successfully."<<endl;
			createuser_success = true;
		}else{
			cout<< attempts - 1 << " attempts remaining." << endl;
			createuser_success=false;
			attempts--;
		}
	}
	if(attempts==0){
		cout<<"Maximum number of sign in attempts reached. Exiting the program. Goodbye!"<<endl;
		exit(EXIT_FAILURE);
	}
}