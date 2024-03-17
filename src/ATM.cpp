#include "ATM.h"

ATM::ATM(const string& dbPath,const string& errorLogPath,const string& successLogPath):db(dbPath,errorLogPath,successLogPath){
	cout<<"Welcome to the ATM machine project!"<<endl;
	cout<<"Select how you want to connect by entering the corresponding number: "<<endl;
	cout<<"1.Login."<<endl;
	cout<<"2.Sign up."<<endl;
	cout<<"0.Quit the program."<<endl;
	//Necessary variables to store input data
	int option = 0;
	string username,password;
	cin>>option;
	switch(option){
		case 1:
			//PROTECTED FROM SQL INJECTIONS
			cout<<"LOG IN"<<endl;
			cout<<"Username:"<<endl;
			cin>>username;
			cout<<"Password:"<<endl;
			cin>>password;
			if(db.loginUser(username,password)){
				cout<<"Welcome Mr.Ms "<<username<<endl;		
			}else{
				cout<<"Login Incorrect"<<endl;
			}
			break;
		case 2:
		    // Implement sign-up functionality
		    break;
		case 0:
		    cout << "Exiting the program. Goodbye!" << endl;
		    break;
		default:
		    cout << "Invalid option. Please select a valid option." << endl;
		    break;
	};
}
