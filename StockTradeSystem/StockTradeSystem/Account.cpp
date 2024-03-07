/* ----------------------------------------------------------------------------
 *
 * Author: M. Tang
 * Maintainer: M. Tang
 * Creation Date: 2024-Feb-27
 * Previous Edit: 2024-March-06
 * -------------------------------------------------------------------------- */

#include "Account.h"

//// Constructors and copy-control members
// default constructor
Account::Account() {

}

// parameterized constructor
Account::Account(const string un, const string pwd) 
	: user_name(un), password(pwd)
{

}

// copy constructor
Account::Account(const Account &rhs) {

}

// copy-assignment operator
Account &Account::operator=(const Account &rhs) {
	this->user_name = rhs.user_name;
	this->password = rhs.password;
	return *this;
}

// destructor - empty implementation for pure virtual fn
Account::~Account() { }


//// Public interfaces
// get user name
string Account::getUserName() const {
	return this->user_name;
}