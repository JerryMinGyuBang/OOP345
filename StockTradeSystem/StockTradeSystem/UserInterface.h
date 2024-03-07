/* ----------------------------------------------------------------------------
 *
 * Author: M. Tang
 * Maintainer: M. Tang
 * Creation Date: 2024-Feb-27
 * Previous Edit: 2024-March-06
 * -------------------------------------------------------------------------- */

#pragma once
#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <memory>
using namespace std;
using std::cout;

#include "Common.h"
#include "Account.h"
#include "Member.h"
//#include "Admin.h"
#include "StockExchange.h"

// class `UserInterface`
class UserInterface {
public:
	//// Constructors and copy-control members
	// default constructor
	UserInterface();
	// destructor
	~UserInterface();

	//// Public interfaces
	// open menu
	void openMenu();
	// login account
	void loginIn(string, size_t);
	// register user
	bool registerUser();
	
	// main function to keep the system running
	void spin();

private:
	//// Data members
	// stock exchange member
	std::shared_ptr<StockExchange> exchange_ptr;


	//// Private utilities
	// run Account member user interface
	void runMemberUI(std::shared_ptr<Member> &);
	// display member submenu
	void openMemberMenu() const;

}; // end of class `UserInterface`


#endif /* USERINTERFACE_H */