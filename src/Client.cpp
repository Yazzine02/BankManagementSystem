#include "Client.h"
Client::Client(const int& id,const string& un,const string& p,const string& dbPath,const string& errorLogPath,const string& successLogPath)
:db(dbPath,errorLogPath,successLogPath){
	user_id=id;
	username=un;
	password=p;
	balance=db.getBalance(user_id);
}

int Client::get_userid() const {
    return user_id;
}

string Client::get_username() const {
    return username;
}

// Setter methods
/*void Client::set_password(const string& new_password) {
    password = new_password;
}

void Client::set_username(const string& new_username) {
    username = new_username;
}*/

double Client::get_balance()const{
	return balance;
}

void Client::set_balance(const double& new_balance){
	balance=new_balance;
}

void Client::Deposit(const double& deposit,const int& id){
	if(deposit>=0){
		double new_balance = deposit + get_balance();
		set_balance(new_balance);
		db.setBalance(new_balance,id);
		cout<<"Balance: MAD "<<get_balance()<<endl;
	}else cout<<"Enter a positive number!"<<endl;
}

void Client::Withdraw(const double& withdraw,const int& id){
	if(withdraw>0 && withdraw<=get_balance()){
		double new_balance = get_balance()-withdraw;
		set_balance(new_balance);
		db.setBalance(new_balance,id);
		cout<<"Balance: MAD "<<get_balance()<<endl;
	}else{
		cout<<"You cannot withdraw this ammount."<<endl;
	}
}
