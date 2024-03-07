/* ----------------------------------------------------------------------------
 *
 * Author: M. Tang
 * Maintainer: M. Tang
 * Creation Date: 2024-Feb-27
 * Previous Edit: 2024-March-06
 * -------------------------------------------------------------------------- */

#include "UserInterface.h"

//// Constructors and copy-control members
// default constructor
UserInterface::UserInterface() {
	this->exchange_ptr = std::make_shared<StockExchange>();
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
				// call resetScreen utility
				resetScreen();

				// create a `Member` smart pointer using its parameterized constructor
				user = std::make_shared<Member>(uname, pwd, exchange_ptr);
				// dynamic cast the base-type smart poitner to the derived-type ptr
				shared_ptr<Member> m_ptr = std::dynamic_pointer_cast<Member>(user);
				// enter sub-menu belongs to `Member`
				this->runMemberUI(m_ptr); // [TODO]: call member user interface

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
				// call resetScreen utility
				resetScreen();

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
	// call resetScreen utility
	resetScreen();
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
	// call resetScreen utility
	resetScreen();
	return true;
}

// main function to keep the system running
void UserInterface::spin() {
	// to avoid invalid input such as letters, use `string` for user input
	string select = "0"; // variable to store the user's option input

	while (true) {
		this->openMenu();
		cin >> select; // obtain the user's input
		// invokes different interface based on user's option
		if (select == "1") {
			// [TODO]: finalize the member options
			this->loginIn(MEMBER_FILE, 1); 
		}
		else if (select == "2") {
			system("cls");
			std::cout << std::endl;
			if (this->registerUser()) {
				std::cout << "You can now login with the new account!\n" << std::endl;
			}
		}
		else if (select == "3") {
			std::cout << "(Under Development ...) System admin menu" << std::endl; // [TODO]
			//this->loginIn(ADMIN_FILE, 3); [TODO]
		}
		else if (select == "0") {
			std::cout << "\n\nThank you for using the Stock Trade System!" << endl;
			// call resetScreen utility
			resetScreen();
			return;
		}
		else {
			system("cls");
			std::cout << "\nInvalid option, please re-select a valid option.\n" << endl;
		}
	} // end of while loop
}


//// Private utilities
// run Account member submenu
void UserInterface::runMemberUI(std::shared_ptr<Member> &m_ptr) {
	
	/* [TODO]: REMOVE this block
	cout << "Testing..." << endl;
	m_ptr->portfolio_ptr->displayFundInfo();

	m_ptr->portfolio_ptr->showPositions();
	m_ptr->portfolio_ptr->showAllTradeRecords();
	*/

	while (true) {
		// display a welcome message
		cout << "\n\t\t========= Welcome: " << m_ptr->getUserName() << " =========" << endl;
		// invokes member's submenu
		this->openMemberMenu();
		// define variable to store user input for menu selection
		string select;
		// ask for user input
		cin >> select;	// obtain user's input

		// action based on user input
		if (select == "1") // show current portfolio positions
		{
			system("cls");		// clear current screen
			cout << endl;		// adjust spacing
			
			// call Portfolio::showPositions() interface
			m_ptr->portfolio_ptr->showPositions();
			
			// call resetScreen utility
			resetScreen();
		}
		else if (select == "2") // deposit money into portfolio
		{
			double amt;		// variable to store user input
			cout << "Please enter the amount to deposit: ";
			// check if the amount entered is a valid input
			if (cin >> amt) {
				// if valid call `Member::depositMoney(double)` interface
				m_ptr->depositMoney(amt);
			}
			else	// invalid user input
			{
				cout << "\nInvalid input. " 
					 << "Deposit operation unsuccessful." 
					 << endl;
				cin.clear();
				while (cin.get() != '\n'); // empty loop
			}
			
			// call resetScreen utility
			resetScreen();
		}
		else if (select == "3") // withdraw money from portfolio
		{
			cout << "\nAvailable cash in portfolio to withdraw: $"
				<< m_ptr->portfolio_ptr->getAvailableFund()
				<< endl << endl;

			double amt;		// variable to store user input
			cout << "Please enter the amount to withdraw: ";
			// check if the amount entered is a valid input
			if (cin >> amt) {
				// if valid call `Member::depositMoney(double)` interface
				m_ptr->withdrawMoney(amt);
			}
			else	// invalid user input
			{
				cout << "\nInvalid input. "
					<< "Withdrawal operation unsuccessful."
					<< endl;
				cin.clear();
				while (cin.get() != '\n'); // empty loop
			}

			// call resetScreen utility
			resetScreen();
		}
		else if (select == "4") // buy a single stock
		{
			cout << "\n\tAvailable cash in portfolio for investment: $"
				<< m_ptr->portfolio_ptr->getAvailableFund()
				<< endl << endl
				<< "\tService charge for a successful order: $" << SERVICE_CHARGE
				<< endl;

			// define variables to accept user's input
			string sym;		// stock symbol
			size_t num;		// number of shares
			cout << "\n\tEnter the stock's symbol to buy: ";
			cin >> sym;
			cout << "\n\tEnter the number of shares to buy: ";
			// check if the amount entered is a valid input
			if (cin >> num) {
				cout << endl;
				// if valid call `Member::buyStock(string, size_t)` interface
				m_ptr->buyStock(sym, num);
			}
			else	// invalid user input
			{
				cout << "\nInvalid input. "
					<< "Buy Stock action unsuccessful."
					<< endl;
				cin.clear();
				while (cin.get() != '\n'); // empty loop
			}

			// call resetScreen utility
			resetScreen();
		}
		else if (select == "5") // sell a single stock
		{
			system("cls"); // clean up the screen
			cout << "\n\tCurrent stock positions " 
				 << "(Note: actual trade price can fluctuate): "
				 << endl << endl;
			m_ptr->portfolio_ptr->displayStockInfo();
			cout << "\n\tService charge for a successful order: $" << SERVICE_CHARGE
				 << endl;

			// define variables to accept user's input
			string sym;		// stock symbol
			size_t num;		// number of shares
			cout << "\n\tEnter the stock's symbol to sell: ";
			cin >> sym;
			cout << "\n\tEnter the number of shares to sell: ";
			// check if the amount entered is a valid input
			if (cin >> num) {
				cout << endl;
				// if valid call `Member::sellStock(string, size_t)` interface
				m_ptr->sellStock(sym, num);
			}
			else	// invalid user input
			{
				cout << "\nInvalid input. "
					<< "Sell Stock action unsuccessful."
					<< endl;
				cin.clear();
				while (cin.get() != '\n'); // empty loop
			}

			// call resetScreen utility
			resetScreen();
		}
		else if (select == "6") // display all trade records for current portfolio
		{
			// showing all trade records for the current portfolio
			cout << "\nAll trading records of the portfolio:\n" << endl;
			// call `Portfolio::showAllTradeRecords` interface to show all records
			m_ptr->portfolio_ptr->showAllTradeRecords();

			// call resetScreen utility
			resetScreen();
		}
		else if (select == "7") // display trade records of a single stock in portfolio
		{
			// define a variable to store user input
			std::string sym;
			// showing trade records for a single stock
			cout << "\nEnter the stock symbol for trade record: ";
			cin >> sym;
			// call `Portfolio::showTradeRecord(sym)` to show records of a stock
			cout << "\nTrade records of stock <" << sym << ">: " << endl << endl;
			m_ptr->portfolio_ptr->showTradeRecord(sym);

			// call resetScreen utility
			resetScreen();
		}
		else if (select == "M" || select == "m") // display market stock data
		{	
			system("cls"); 
			// call `StockExchange::displayMarket` interface to display martket info
			this->exchange_ptr->displayMarket();
		}
		else if (select == "0") {
			cout << "\nExiting Member page."
				<< " Press any key to the main menu ..."
				<< endl;
			
			// call resetScreen utility
			resetScreen();
			return;
		}
		else {
			system("cls");
			std::cout << "\nInvalid option, please select a valid option to continue\n\n"
				<< std::endl;
		}
	}

}

// display member submenu
void UserInterface::openMemberMenu() const {
	cout << endl << "\t\tAction menu:" << endl;
	cout << "\t\t---------------------------------------\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|   1. Show Portfolio Positions       |\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|   2. Deposit Money to Portfolio     |\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|   3. Withdraw Money from Portfolio  |\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|   4. Buy Stock                      |\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|   5. Sell Stock                     |\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|   6. Display All Trade Records      |\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|   7. Display Single Stock Records   |\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|   M. Display Market                 |\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|   0. Exit                           |\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t --------------------------------------\n";
	cout << "Please enter your action: ";
}