/* ----------------------------------------------------------------------------
 *
 * Author: M. Tang
 * Maintainer: M. Tang
 * Creation Date: 2024-Feb-27
 * Previous Edit: 2024-Feb-28
 * -------------------------------------------------------------------------- */

#include "Account.h"

//// Constructors and copy-control members
// default constructor
Account::Account() {

}

// parameterized constructor
Account::Account(string un, string pwd) {

}

// copy constructor
Account::Account(const Account &rhs) {

}

// copy-assignment operator
Account &Account::operator=(const Account &rhs) {

	return *this; // [TODO]
}

// destructor - empty implementation for pure virtual fn
Account::~Account() { }
