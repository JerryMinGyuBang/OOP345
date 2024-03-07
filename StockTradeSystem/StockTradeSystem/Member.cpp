/* ----------------------------------------------------------------------------
 *
 * Author: M. Tang
 * Maintainer: M. Tang
 * Creation Date: 2024-Feb-27
 * Previous Edit: 2024-March-05
 * -------------------------------------------------------------------------- */

#include "Member.h"

//// Constructors and copy-control members
// default constructor
Member::Member(const string name, const string pwd, shared_ptr<StockExchange> &ex)
	: Account(name, pwd), portfolio_ptr(std::make_shared<Portfolio>(name, ex))
{
	//cout << "Member::Member(const string, const string, shared_ptr<StockExchange> &)" << endl; // [TODO]: remove this line
}

// copy constructor
Member::Member(const Member &rhs) {
	//cout << "Member::Member(const Member &)" << endl; // [TODO]: remove this line
	*this = rhs;
}

// copy-assignment operator
Member &Member::operator=(const Member &rhs) {
	//cout << "Member &Member::operator=" << endl; // [TODO]: remove this line
	// check for self-assignment
	if (!(this == &rhs)) {
		this->portfolio_ptr = rhs.portfolio_ptr;
	}
	return *this;
}

// destructor
Member::~Member() {
	//cout << "Member::~Member()" << endl; // [TODO]: remove this line
}


//// Public interfaces
// get the smart pointer to portfolio data member
std::shared_ptr<Portfolio> &Member::getPortfolioPtr() {
	return this->portfolio_ptr;
}

// deposit available fund (add money into account)
bool Member::depositMoney(const double amt) {
	try {
		if (amt > 0) {
			this->portfolio_ptr->available_fund += amt;
			this->portfolio_ptr->total_invest += amt;
			cout << std::fixed << std::setprecision(2)		// keep two decimal places
				 << "\nSuccessfully deposited: "
				 << "$" << amt
				 << endl;
			// update user data into file after deposit
			this->getPortfolioPtr()->writePortfolioToFile();
			return true;
		}
		else {
			throw std::invalid_argument("Cannot deposit non-positive amount.");
		}
	}
	catch (const std::exception &e) {
		std::cerr << "Failed deposit operation: "
			<< e.what()
			<< endl;
	}
	return false;
}

// withdraw money from available fund (get money out from account)
bool Member::withdrawMoney(const double amt) {
	try {
		if (amt > 0) {
			if (this->getPortfolioPtr()->getAvailableFund() >= amt) {
				this->portfolio_ptr->available_fund -= amt;
				this->portfolio_ptr->total_withdrawal += amt;
				cout << "\nSuccessfully withdrew: "
					<< "$" << amt
					<< endl;
				// update user data into file after withdrawal
				this->getPortfolioPtr()->writePortfolioToFile();
				return true;
			}
			else
			{
				throw std::runtime_error("Withdrawal amount is greater than the available fund in account.");
			}
		}
		else {
			throw std::invalid_argument("Cannot withdraw non-positive amount.");
		}
	}
	catch (const std::exception &e) {
		std::cerr << "Failed withdrawal operation: "
			<< e.what()
			<< endl;
	}
	return false;
}

// buy a stock
bool Member::buyStock(const string symbol, const size_t num) {
	// call Portfolio::createOrder with TRADETYPE::BUY
	if (this->portfolio_ptr->createOrder(symbol, num, TRADETYPE::BUY)) {
		cout << "Trade order finished." << endl;
		return true;
	}
	else {
		cout << "Trade order aborted." << endl;
		return false;
	}
}

// sell a stock
bool Member::sellStock(const string symbol, const size_t num) {
	// call Portfolio::createOrder with TRADETYPE::SELL
	if (this->portfolio_ptr->createOrder(symbol, num, TRADETYPE::SELL)) {
		cout << "Trade order finished." << endl;
		return true;
	}
	else {
		cout << "Trade order aborted." << endl;
		return false;
	}
}



