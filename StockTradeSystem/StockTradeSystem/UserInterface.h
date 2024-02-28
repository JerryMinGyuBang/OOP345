#pragma once
#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <iostream>
#include <string>
using namespace std;

// class `UserInterface`
class UserInterface {
public:
	//// Constructors and copy-control members
	// default constructor
	UserInterface();

	//// Public interfaces
	// open menu
	void openMenu();
	// login account
	void logIn();
	// register user
	bool registerUser();

private:

}; // end of class `UserInterface`


#endif /* USERINTERFACE_H */