/* ----------------------------------------------------------------------------
 *
 * Author: M. Tang
 * Maintainer: M. Tang
 * Creation Date: 2024-Feb-27
 * Previous Edit: 2024-Feb-28
 * -------------------------------------------------------------------------- */

#pragma once
#ifndef MEMBER_H
#define MEMBER_H

#include <iostream>
#include <memory>
#include <string>
using namespace std;

#include "Account.h"
#include "Portfolio.h"


// class `Member` - derived class of `Account`
class Member : public Account {
public:
	//// Constructors and copy-control members
	// default constructor
	Member();
	// parameterized constructor
	Member(string name, string pwd, double fund=0.0);
	// copy constructor
	Member(const Member &);
	// copy-assignment operator
	Member &operator=(const Member &);
	// destructor
	~Member() override;


	//// Public interfaces
	// deposit available fund (add money into account)
	bool depositMoney(double);
	// withdraw money from available fund (get money out from account)
	bool withdrawMoney(double);
	// buy a stock
	bool buyStock(string symbol, size_t num);
	// sell a stock
	bool sellStock(string symbol, size_t num);


private:
	//// Data members
	// available fund to invest
	double available_fund;
	// total cash deposited since account creation
	double total_invest;
	// portfolio object associated with the account
	Portfolio portfolio;

};



#endif /* MEMBER_H */
