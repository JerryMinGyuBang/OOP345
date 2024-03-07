/* ----------------------------------------------------------------------------
 *
 * Author: M. Tang
 * Maintainer: M. Tang
 * Creation Date: 2024-Feb-27
 * Previous Edit: 2024-March-06
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
	Account(const string, const string);
	// copy constructor
	Account(const Account &);
	// copy-assignment operator
	Account &operator=(const Account &);
	// destructor - pure virtual function
	virtual ~Account() = 0;


	//// Public interfaces
	// get user name
	string getUserName() const;

private:
	//// Data members
	// user name
	string user_name;
	// user account password
	string password;

}; // end of class `Account`


#endif /* ACCOUNT_H */