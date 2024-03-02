/* ----------------------------------------------------------------------------
 *
 * Author: M. Tang
 * Maintainer: M. Tang
 * Creation Date: 2024-Feb-27
 * Previous Edit: 2024-Feb-28
 * -------------------------------------------------------------------------- */

#include "Member.h"

//// Constructors and copy-control members
// default constructor
Member::Member() {

}

// parameterized constructor
Member::Member(string name, string pwd, double fund) {

}

// copy constructor
Member::Member(const Member &rhs) {

}

// copy-assignment operator
Member &Member::operator=(const Member &rhs) {

	return *this; // [TODO]
}

// destructor
Member::~Member() {

}


//// Public interfaces
// deposit available fund (add money into account)
bool Member::depositMoney(double) {

	return true; // [TODO]
}

// withdraw money from available fund (get money out from account)
bool Member::withdrawMoney(double) {

	return true; // [TODO]
}

// buy a stock
bool Member::buyStock(string symbol, size_t num) {

	return true; // [TODO]
}

// sell a stock
bool Member::sellStock(string symbol, size_t num) {

	return true; // [TODO]
}



