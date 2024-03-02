/* ----------------------------------------------------------------------------
 *
 * Author: M. Tang
 * Maintainer: M. Tang
 * Creation Date: 2024-Feb-27
 * Previous Edit: 2024-Feb-28
 * -------------------------------------------------------------------------- */

#include "UserInterface.h"

//// Constructors and copy-control members
// default constructor
UserInterface::UserInterface() {
	//cout << "UserInterface::UserInterface()" << endl; // [TODO]: remove this line
}

// destructor
UserInterface::~UserInterface() {
	//cout << "UserInterface::~UserInterface()" << endl; // [TODO]: remove this line
}


//// Public interfaces
// open menu
void UserInterface::openMenu() {
	cout << "================= Welcome to Stock Trade System =================" << endl;
	cout << endl << "Please enter your role:" << endl;
	cout << "\t\t --------------------------------------\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|        1. Existing Member           |\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|        2. Register New Member       |\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|        3. System Administrator      |\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|        0. Exit                      |\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t --------------------------------------\n";
	cout << "Please enter your action: ";
}

// login account
/**
 * @brief Login function to the Trading System
 *
 * @param fileName  string, File MARCO that relates to the filename
 * @param u_type    size_t, User's login option
 */
void UserInterface::loginIn(string filename, size_t u_type) {
	// create a smart pointer to base class for objects to derived classes
	std::shared_ptr<Account> user;

	// read data file
	ifstream ifs;
	ifs.open(filename, ifstream::in);

	// check file existency
	if ( !ifs.is_open() ) {
		cerr << "Failed to open file: " << filename << endl;
		return ;
	}

	// if file opened successfully, prepare to accept user's input
	string uname;	// user name for login
	string pwd;		// password for login

	// check user login type
	if (u_type == 1) // existing user
	{
		cout << "Please enter your user name: " << endl;
		cin >> uname;
		cout << "Please enter your password: " << endl;
		cin >> pwd;

		// verify login information
		string f_name, f_pwd;	// user name and password strings from file
		// traverse the file line-by-line, space separated
		while (ifs >> f_name && ifs >> f_pwd) {
			// compare user input to the records in file
			if (f_name == uname && f_pwd == pwd) {
				cout << "\nMember verfication succeeds!" << endl;
				system("pause");
				system("cls");

				// create a `Member` smart pointer using its parameterized constructor
				user = std::make_shared<Member>(uname, pwd);
				// enter sub-menu belongs to `Member`
				// [TODO]: call member's submenu

				// ending account member menu
				ifs.close();	// closing data file
				return ;
			}
		}
	}
	else if (u_type == 3) // system administrator
	{
		cout << "Please enter admin user name: " << endl;
		cin >> uname;
		cout << "Please enter admin password: " << endl;
		cin >> pwd;

		// verify login information
		string f_name, f_pwd;	// admin name and password strings from file
		// traverse the file line-by-line, space separated
		while (ifs >> f_name && ifs >> f_pwd) {
			// compare user input to the records in file
			if (f_name == uname && f_pwd == pwd) {
				cout << "\nAdmin verfication succeeds!" << endl;
				system("pause");
				system("cls");

				// create a `Member` smart pointer using its parameterized constructor
				//user = std::make_shared<Member>(uname, pwd, 0.0);
				// enter sub-menu belongs to `Member`
				// [TODO]: call admin's submenu

				// ending account member menu
				ifs.close();
				return ;
			}
		}
	}

	// failed to login
	ifs.close();
	cout << "\nLogin failed..." << endl;
	system("pause");
	system("cls");
	return ;
}

// register user
bool UserInterface::registerUser() {
	// define variables for user input storage
	string u_name;	// user name
	string u_pwd;	// user password
	ifstream ifs;	// input file stream
	ofstream ofs;	// output file stream

	cout << "Enter user name for the new account (cannot contain space): ";
	cin >> u_name;

	// check if the u_name has been used
	std::istringstream iss; // using an input stringstream to read a line per time
	string f_name;	// user name string from file
	ifs.open(MEMBER_FILE, fstream::in);
	if (ifs.is_open()) {
		iss.clear(); // clear the string stream before assignment
		// travese the file to check if the user name already exists
		for (string line; std::getline(ifs, line); iss.clear()) {
			iss.str(line);
			iss >> f_name; // the first part of each line is the user name
			if (f_name == u_name) {
				cout << "User name already exists. Registration failed.\n" << endl;
				ifs.close();
				return false;
			}
		}
	}
	else {
		cerr << "Failed to open file: " << MEMBER_FILE << endl;
		return false;
	}

	// at this point, the specified user name is valid, asks for password
	ifs.close(); // close input stream file
	cout << "Enter password for the new account: ";
	cin >> u_pwd;

	// write information to file, open file in append mode
	ofs.open(MEMBER_FILE, ofstream::out | ofstream::app);
	// information stored in space delimited format
	ofs << u_name << " " << u_pwd << endl;
	
	// close file and clear screen
	ofs.close();	// close output stream file
	cout << "\nAccount created successfully." << endl;
	system("pause");
	system("cls");
	return true;
}

// main function to keep the system running
void UserInterface::spin() {
	size_t select = 0; // variable to store the user's option input

	while (true) {
		this->openMenu();
		cin >> select; // obtain the user's input

		switch (select)  // invokes different interface based on user's option
		{
		case 1: {
			this->loginIn(MEMBER_FILE, 1);
			break;
		}
		case 2: {
			system("cls");
			cout << endl;
			if (this->registerUser()) {
				cout << "You can now login with the new account!\n" << endl;
			}
			break;
		}
		case 3: {
			cout << "System admin menu" << endl; // [TODO]
			this->loginIn(ADMIN_FILE, 3);
			break;
		}
		case 0: {
			cout << "\n\nThank you for using the Stock Trade System!" << endl;
			system("pause");
			system("cls");
			return ;
		}
		default:
			system("cls");
			cout << "\nInvalid option, please re-select a valid option.\n" << endl;
		}
	}
}