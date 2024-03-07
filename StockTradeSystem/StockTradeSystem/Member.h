/* ----------------------------------------------------------------------------
 *
 * Author: M. Tang
 * Maintainer: M. Tang
 * Creation Date: 2024-Feb-27
 * Previous Edit: 2024-March-05
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
#include "StockExchange.h"
//#include "UserInterface.h" // [TODO]: remove this line


// forward declaration
class Portfolio;
class StockExchange;
class UserInterface;

// class `Member` - derived class of `Account`
class Member : public Account {
	friend UserInterface;

public:
	//// Constructors and copy-control members
	// default constructor - parameters <name, password, exchange_ptr>
	Member(const string, const string pwd, shared_ptr<StockExchange> &);
	// copy constructor
	Member(const Member &);
	// copy-assignment operator
	Member &operator=(const Member &);
	// destructor
	~Member() override;


	//// Public interfaces
	// get the smart pointer to portfolio data member
	std::shared_ptr<Portfolio> &getPortfolioPtr();
	// deposit available fund (add money into account)
	bool depositMoney(const double);
	// withdraw money from available fund (get money out from account)
	bool withdrawMoney(const double);
	// buy a stock
	bool buyStock(const string symbol, const size_t num);
	// sell a stock
	bool sellStock(const string symbol, const size_t num);


private:
	//// Data members
	// shared_ptr points to a portfolio object associated with the account
	std::shared_ptr<Portfolio> portfolio_ptr;

};



#endif /* MEMBER_H */
