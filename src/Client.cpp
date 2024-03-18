#include "Client.h"
Client::Client(const int& id,const string& un,const string& p){
	user_id=id;
	username=un;
	password=p;
	cout<<"Client object created successfully, username = "+un+" and password= "+p<<endl;
}

int Client::get_userid() const {
    return user_id;
}

string Client::get_username() const {
    return username;
}

// Setter methods
void Client::set_password(const string& new_password) {
    password = new_password;
}

void Client::set_username(const string& new_username) {
    username = new_username;
}
