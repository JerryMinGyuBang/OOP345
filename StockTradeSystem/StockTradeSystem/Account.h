#pragma once
#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <string>
using namespace std;

// Base class `Account`
class Account {
public:
	//// Constructors and copy-control members
	// default constructor
	Account();
	// parameterized constructor
	Account(string, string, string);
	// copy constructor
	Account(const Account &);
	// copy-assignment operator
	Account &operator=(const Account &);
	// destructor - pure virtual function
	virtual ~Account() = 0;

private:
	//// Data members
	string user_id;
	string user_name;
	string password;

}; // end of class `Account`


#endif /* ACCOUNT_H */