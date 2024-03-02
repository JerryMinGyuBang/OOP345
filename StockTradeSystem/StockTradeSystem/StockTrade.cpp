/* ----------------------------------------------------------------------------
 *
 * Author: M. Tang
 * Maintainer: M. Tang
 * Creation Date: 2024-Feb-27
 * Previous Edit: 2024-Feb-29
 * -------------------------------------------------------------------------- */

#include "StockTrade.h"

//// Constructors and copy-control members
// default constructor
StockTrade::StockTrade() : status(ORDERSTATUS::INCOMPLETE) {
	//cout << "StockTrade::StockTrade()" << endl; // [TODO]: remove this line
}

// parameterized constructor
StockTrade::StockTrade(string symbol, size_t num, TRADETYPE t_type)
	: stock_symbol(symbol), quantity(num), trade_type(t_type), status(ORDERSTATUS::INCOMPLETE)
{
	//cout << "StockTrade::StockTrade(string symbol, size_t num, TRADETYPE t_type)" << endl; // [TODO]: remove this line
}

// parameterized constructor with full input
StockTrade::StockTrade(string t_id, string sym, size_t num, double p, TRADETYPE tt, ORDERSTATUS os)
	: trade_id(t_id), stock_symbol(sym), quantity(num), price(p), trade_type(tt), status(os)
{
	//cout << "StockTrade::StockTrade(string t_id, string sym, size_t num, double p, TRADETYPE tt, ORDERSTATUS os)" << endl; // [TODO]: remove this line
}

// destructor
StockTrade::~StockTrade() {
	//cout << "StockTrade::~StockTrade()" << endl; // [TODO]: remove this line
}


//// Public interfaces
// set current stock price to trade - called by `StockExchange`
bool StockTrade::setPrice(const double p) {
	try {
		if (p >= MINIMUM_PRICE) // the trade price shall not below a minimum price
		{
			this->price = p;
		}
		else {
			throw std::invalid_argument("Value below minimum trade price.");
		}
	}
	catch (const std::exception& e) {
		cerr << "Failed to set price to a `StockTrade` object: "
			 << e.what()
			 << endl;
		return false;
	}
	return true;
}

// set unique trade Id of the current trade - called by `StockExchange`
bool StockTrade::setTradeId(const string t_id) {
	try {
		/* optional add-on: add verification for valid trade ID */
		this->trade_id = t_id;
	}
	catch (const std::exception& e) {
		cerr << "Failed to set trade ID to a `StockTrade` object: "
			<< e.what()
			<< endl;
		return false;
	}
	return true;
}

// get unique trade Id of the current trade - called by `Portfolio`
string StockTrade::getTradeId() const {
	return this->trade_id;
}

// set trade status
bool StockTrade::setStatus(const ORDERSTATUS s_) {
	try {
		/* optional add-on: add other verification for valid action */
		if (this->status == ORDERSTATUS::FINISHED || this->status == ORDERSTATUS::CANCELLED) 
		{
			// trade status can only be changed if the status is `INCOMPLETE` or `PENDING`
			throw std::invalid_argument("Attempted to change the status of a finalized trade.");
		}
		else
		{
			this->status = s_;
		}
	}
	catch (const std::exception& e) {
		cerr << "Failed to set status of a `StockTrade` object: "
			<< e.what()
			<< endl;
		return false;
	}
	return true;
}