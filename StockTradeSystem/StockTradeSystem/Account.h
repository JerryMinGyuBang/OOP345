/* ----------------------------------------------------------------------------
 *
 * Author: M. Tang
 * Maintainer: M. Tang
 * Creation Date: 2024-Feb-27
 * Previous Edit: 2024-Feb-28
 * -------------------------------------------------------------------------- */

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
	Account(string, string);
	// copy constructor
	Account(const Account &);
	// copy-assignment operator
	Account &operator=(const Account &);
	// destructor - pure virtual function
	virtual ~Account() = 0;

private:
	//// Data members
	// user name
	string user_name;
	// user account password
	string password;

}; // end of class `Account`


#endif /* ACCOUNT_H */