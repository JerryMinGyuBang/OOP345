/* ----------------------------------------------------------------------------
 *
 * Author: M. Tang
 * Maintainer: M. Tang
 * Creation Date: 2024-March-02
 * Previous Edit: 2024-March-06
 * -------------------------------------------------------------------------- */

#pragma once
#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <memory>
#include <vector>
#include <string>
#include <map>
#include <set>
using namespace std;

#include "Common.h"
#include "Member.h"
#include "Account.h"
#include "StockExchange.h"

// forward declerations
class Member;
//class StockExchange;

// class `Portfolio`
class Portfolio {
friend Member;

public:
	//// Constructors and copy-control members
	// default constructor 
	Portfolio();
	// parameterized constructor - args: user_name: string
	Portfolio(const string, shared_ptr<StockExchange> &);
	// copy constructor
	Portfolio(const Portfolio &rhs);
	// copy-assignment operator
	Portfolio &operator=(const Portfolio &rhs);
	// destructor
	~Portfolio();

	//// Public interfaces
	// create an `StockTrade` object and call `StockExchange::placeOrder` interface
	bool createOrder(const string, const size_t, const TRADETYPE);
	// show portfolio positions - also updates `earning`
	void showPositions();
	// show trade records for a single stock based on stock symbol
	void showTradeRecord(const string) const;
	// show all trading record for the current portfolio
	void showAllTradeRecords() const;
	// get earning (i.e., profit/loss) of the portfolio - also updates `earning`
	double getEarning();
	// overloaded - get earning of the portfolio - also updates `earning`
	double getEarning(const map<string, double> &);
	// get available fund for stock trading
	double getAvailableFund() const;
	// display fund information: available fund and total invested amount
	void displayFundInfo() const;
	// overloaded - display stock infromation: stock symbol, quantity, price, subtotal
	void displayStockInfo();
	// write current portfolio information to file
	void writePortfolioToFile() const;


private:
	//// Private utilities
	// load portfolio information from file
	void loadPortfolio(const string &);
	// get updated porfolio positions - interacts with `StockExchange` object
	map<string, double> getUpdatedPositions();
	// display stock infromation: stock symbol, quantity, price, subtotal
	void displayStockInfo(const map<string, double> &);
	// compute average prices
	void computeAvgPrices();


	//// Data members
	// user name of the portfolio
	string u_name;
	// available fund to invest
	double available_fund;
	// total withdrawal
	double total_withdrawal;
	// total cash deposited since account creation
	double total_invest;
	// trade records - a set of `trade_id` string
	set<string> trade_record;
	// owned stocks by current portfolio: {symbol: quantity}
	map<string, size_t> owned_stocks;
	// average purchase price of owned stocks, weighted average method
	map<string, double> avg_prices;
	// portfolio profit or loss - over account history since creation
	double earning;
	// shared_ptr to the `StockExchange` object
	std::shared_ptr<StockExchange> exchange_ptr;

}; // end of class `Portfolio`


#endif /* PORTFOLIO_H */
